/*
 * w25qxx_nor_flash_spi_stm32g0.c
 *
 * Target MCU : STM32G071xx (STM32G0 family)
 * NOR Flash  : W25Q32 (4MB) / W25Q64 / W25Q128 - Winbond Serial NOR Flash
 * SPI        : SPI1 - Bare-metal, register-level, no HAL
 * SPI Pins   : PA5=SCK, PA6=MISO, PA7=MOSI, PC7=CS (active LOW)
 * Clock      : 64 MHz SYSCLK (via PLL from HSI16)
 *
 * ============================================================================
 * INTERVIEW NOTES - W25Qxx NOR FLASH KEY FACTS
 * ============================================================================
 *
 * 1. NOR Flash vs NAND Flash:
 *    - NOR  : Byte-addressable (XIP capable), slower erase, random read fast
 *    - NAND : Page-addressable, faster write/erase, higher density, cheaper
 *    - NOR is used for code storage; NAND for data storage (eMMC, SSDs)
 *
 * 2. W25Q32 Organization:
 *    - Total  : 32 Mbit = 4 MB
 *    - Sector : 4KB  (smallest erasable unit - 4096 bytes)
 *    - Block  : 64KB (16 sectors per block)
 *    - Page   : 256 bytes (max bytes per single Page Program command)
 *    - Total Sectors : 1024,  Total Blocks : 64
 *
 * 3. Critical Rule: MUST ERASE BEFORE WRITE
 *    - Flash can only change bits from 1->0 (write)
 *    - To change 0->1, you MUST erase first
 *    - Erase sets all bits in sector to 0xFF
 *    - Writing changes selected bits from 0xFF to desired value
 *
 * 4. Important Commands (SPI instruction bytes):
 *    - 0x06 : Write Enable (WREN)  - must precede every write/erase
 *    - 0x04 : Write Disable (WRDI)
 *    - 0x05 : Read Status Register-1 (RDSR1) - bit0=BUSY, bit1=WEL
 *    - 0x03 : Read Data (normal read, up to 50MHz)
 *    - 0x0B : Fast Read (requires 1 dummy byte, up to 133MHz)
 *    - 0x02 : Page Program (write up to 256 bytes)
 *    - 0x20 : Sector Erase 4KB
 *    - 0xD8 : Block Erase 64KB
 *    - 0xC7 : Chip Erase (erases entire flash - takes seconds!)
 *    - 0x9F : JEDEC ID (Manufacturer + Device ID)
 *    - 0xAB : Release Power-down / Read Device ID
 *    - 0xB9 : Power-down mode
 *
 * 5. Status Register-1 Bits:
 *    - Bit 0 (BUSY) : 1=device busy with write/erase, poll until 0
 *    - Bit 1 (WEL)  : 1=write enabled (set by WREN cmd), clears after write
 *    - Bits 2-4 (BP0-BP2) : Block protect bits
 *    - Bit 7 (SRP)  : Status register protect
 *
 * 6. Address: 24-bit address (3 bytes) for W25Q32:
 *    Byte1=MSB, Byte2=Middle, Byte3=LSB
 *    e.g., address 0x001A2B -> send 0x00, 0x1A, 0x2B
 *
 * 7. SPI Protocol for W25Qxx:
 *    - Mode 0 (CPOL=0, CPHA=0) or Mode 3 (CPOL=1, CPHA=1)
 *    - MSB first
 *    - CS LOW  = select device
 *    - CS HIGH = deselect / end transaction
 *
 * ============================================================================
 */

#include <stdint.h>
#include <stdbool.h>
#include "stm32g0xx.h"

/* ==========================================================================
 * W25Qxx COMMAND DEFINITIONS
 * All commands are 1-byte SPI instruction sent first after CS LOW
 * ========================================================================== */
#define W25Q_CMD_WRITE_ENABLE       0x06  /* Must send before every write/erase */
#define W25Q_CMD_WRITE_DISABLE      0x04
#define W25Q_CMD_READ_STATUS_REG1   0x05  /* Poll BUSY bit here */
#define W25Q_CMD_READ_STATUS_REG2   0x35
#define W25Q_CMD_WRITE_STATUS_REG   0x01
#define W25Q_CMD_PAGE_PROGRAM       0x02  /* Write max 256 bytes per command */
#define W25Q_CMD_SECTOR_ERASE_4KB   0x20  /* Smallest erase unit */
#define W25Q_CMD_BLOCK_ERASE_32KB   0x52
#define W25Q_CMD_BLOCK_ERASE_64KB   0xD8
#define W25Q_CMD_CHIP_ERASE         0xC7  /* Erase entire chip - slow (~30s) */
#define W25Q_CMD_READ_DATA          0x03  /* Normal read, max 50MHz */
#define W25Q_CMD_FAST_READ          0x0B  /* Fast read, requires 1 dummy byte */
#define W25Q_CMD_JEDEC_ID           0x9F  /* Returns: Manufacturer+MemType+Capacity */
#define W25Q_CMD_POWER_DOWN         0xB9
#define W25Q_CMD_RELEASE_POWER_DOWN 0xAB

/* ==========================================================================
 * STATUS REGISTER BIT MASKS
 * ========================================================================== */
#define W25Q_STATUS_BUSY            (1 << 0)  /* 1 = device busy, poll until 0 */
#define W25Q_STATUS_WEL             (1 << 1)  /* 1 = write enabled */

/* ==========================================================================
 * W25Q32 GEOMETRY
 * ========================================================================== */
#define W25Q_PAGE_SIZE              256U    /* bytes - max per Page Program */
#define W25Q_SECTOR_SIZE            4096U   /* bytes = 4KB, min erase unit */
#define W25Q_BLOCK_SIZE_64K         65536U  /* bytes = 64KB */
#define W25Q_MAX_ADDRESS            0x3FFFFFU  /* W25Q32 = 4MB = 0x400000 */

/* ==========================================================================
 * JEDEC ID for W25Q32 (for chip identification at startup)
 * ========================================================================== */
#define W25Q32_JEDEC_MANUFACTURER   0xEF  /* Winbond */
#define W25Q32_JEDEC_MEM_TYPE       0x40  /* W25Q series SPI NOR */
#define W25Q32_JEDEC_CAPACITY       0x16  /* 32Mbit */

/* ==========================================================================
 * SPI / GPIO REGISTER-LEVEL INIT
 *
 * INTERVIEW: Key SPI1 CR1 bits (STM32G0):
 *   BR[2:0] bits[5:3] : Baud rate = PCLK / 2^(BR+1)
 *   MSTR    bit[2]    : 1 = Master mode
 *   CPOL    bit[1]    : Clock polarity (0 = idle low)
 *   CPHA    bit[0]    : Clock phase    (0 = first edge sample)
 *   SSM     bit[9]    : Software slave management
 *   SSI     bit[8]    : Internal slave select (must=1 in SSM mode)
 *   SPE     bit[6]    : SPI enable
 *
 * W25Qxx uses SPI Mode 0: CPOL=0, CPHA=0 (default after reset)
 * ========================================================================== */
static void SPI1_Init(void)
{
    /* 1. Enable SYSCLK via PLL (HSI16 -> PLL -> 64MHz) */
    /* -- PLL Config: N=8 -> VCO=128MHz, R=2 -> PLLRCLK=64MHz -- */
    RCC->CR |= (1 << 8);                    /* HSI16 ON */
    while (!(RCC->CR & (1 << 10)));         /* Wait HSI16 ready */

    FLASH->ACR |= (2 << 0);                 /* 2 wait states for 64MHz */
    while (((FLASH->ACR) & (7 << 0)) != 2);

    RCC->CR &= ~(1 << 24);                  /* Disable PLL */
    while (RCC->CR & (1 << 25));            /* Wait PLL off */

    RCC->PLLCFGR  = (2 << 0);              /* PLL source = HSI16 */
    RCC->PLLCFGR |= (8 << 8);              /* N=8  -> 128MHz VCO output */
    RCC->PLLCFGR |= (1 << 29);             /* R=2  -> PLLRCLK = 64MHz */
    RCC->PLLCFGR |= (1 << 28);             /* PLLR output enable */

    RCC->CR |= (1 << 24);                   /* Enable PLL */
    while (!(RCC->CR & (1 << 25)));         /* Wait PLL locked */

    RCC->CFGR |= (2 << 0);                 /* SYSCLK = PLLRCLK (64MHz) */

    /* 2. Enable GPIO clocks */
    RCC->IOPENR |= (1 << 0);               /* GPIOA clock (SCK, MISO, MOSI) */
    RCC->IOPENR |= (1 << 2);               /* GPIOC clock (CS) */

    /* 3. Configure PA5=SCK, PA6=MISO, PA7=MOSI as Alternate Function (AF0) */
    /*    MODER: 10 = Alternate function mode */
    GPIOA->MODER &= ~((3 << 10) | (3 << 12) | (3 << 14));
    GPIOA->MODER |=  ((2 << 10) | (2 << 12) | (2 << 14));

    /* PA5,PA6,PA7 -> AF0 (SPI1) on STM32G0 */
    GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 24) | (0xF << 28));
    /* AF0 = 0x0, already cleared above */

    /* Set output speed to very high for SPI pins */
    GPIOA->OSPEEDR |= (3 << 10) | (3 << 12) | (3 << 14);

    /* 4. Configure PC7 as General Purpose Output (CS) */
    /*    MODER: 01 = General purpose output */
    GPIOC->MODER &= ~(3 << 14);
    GPIOC->MODER |=  (1 << 14);

    /* CS idle = HIGH (deselected) */
    GPIOC->BSRR = (1 << 7);

    /* 5. Enable SPI1 peripheral clock */
    RCC->APBENR2 |= (1 << 12);

    /* 6. Configure SPI1 CR1
     *    INTERVIEW: Configure before SPE=1, SPE must be last bit set
     */
    SPI1->CR1 = 0;                          /* Reset CR1 */
    SPI1->CR1 |= (1 << 9);                 /* SSM=1: Software CS management */
    SPI1->CR1 |= (1 << 8);                 /* SSI=1: Internal CS high (master) */
    SPI1->CR1 |= (1 << 2);                 /* MSTR=1: Master mode */
    /* CPOL=0, CPHA=0 -> SPI Mode 0 (default, W25Qxx compatible) */
    /* BR[2:0] = 000 -> Baud = PCLK/2 = 32MHz  (within W25Q32 spec) */
    /* For slower speed: (1<<3) = PCLK/4 = 16MHz, (2<<3) = PCLK/8 = 8MHz */
    SPI1->CR1 |= (1 << 3);                 /* BR = 001 -> 64/4 = 16MHz */
    SPI1->CR2 |= (7 << 8);                 /* DS[3:0]=0111 -> 8-bit data size */
    SPI1->CR2 |= (1 << 12);               /* FRXTH=1: RXNE on 8-bit (not 16) */
    SPI1->CR1 |= (1 << 6);                 /* SPE=1: Enable SPI */
}

/* ==========================================================================
 * CS (CHIP SELECT) CONTROL
 *
 * INTERVIEW: CS (also called NSS or CS in W25Qxx datasheet = Chip Select)
 *   - Active LOW: CS=0 selects the device, CS=1 deselects
 *   - BSRR: Bit Set/Reset Register
 *     - Writing bit N sets   GPIO pin N HIGH
 *     - Writing bit N+16 sets GPIO pin N LOW
 * ========================================================================== */
static void W25Q_CS_LOW(void)
{
    GPIOC->BSRR = (1 << (7 + 16));     /* PC7 = LOW (select) */
}

static void W25Q_CS_HIGH(void)
{
    GPIOC->BSRR = (1 << 7);            /* PC7 = HIGH (deselect) */
}

/* ==========================================================================
 * LOW-LEVEL SPI BYTE TRANSMIT & RECEIVE
 *
 * INTERVIEW: STM32 SPI SR (Status Register) key flags:
 *   - TXE  (bit1) : Transmit buffer empty - safe to write DR
 *   - RXNE (bit0) : Receive buffer not empty - data ready to read
 *   - BSY  (bit7) : SPI busy (do NOT deassert CS while BSY=1)
 *   - OVR  (bit6) : Overrun error (rx data lost)
 *
 * INTERVIEW: Clearing OVR: Read DR then read SR (dummy reads)
 * ========================================================================== */
static uint8_t SPI1_TransceiveByte(uint8_t txData)
{
    /* Wait until TX buffer empty */
    while (!(SPI1->SR & SPI_SR_TXE));

    /* Write 8-bit data (cast to uint8_t* to avoid 16-bit write) */
    *(volatile uint8_t *)&SPI1->DR = txData;

    /* Wait until RX buffer has data (transfer complete) */
    while (!(SPI1->SR & SPI_SR_RXNE));

    /* Read received byte */
    return *(volatile uint8_t *)&SPI1->DR;
}

/* Transmit only - discard received byte */
static void SPI1_Transmit(uint8_t *pData, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        SPI1_TransceiveByte(pData[i]);
    }

    /* INTERVIEW: After last byte, wait for BSY=0 before CS HIGH
     * BSY stays high until shift register is fully clocked out */
    while (SPI1->SR & SPI_SR_BSY);

    /* Clear OVR flag: dummy read DR and SR
     * OVR happens because master always receives while transmitting */
    (void)SPI1->DR;
    (void)SPI1->SR;
}

/* Receive only - send dummy 0xFF bytes to clock in data */
static void SPI1_Receive(uint8_t *pBuf, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        /* Send 0xFF as dummy to generate clock pulses for slave to send data */
        pBuf[i] = SPI1_TransceiveByte(0xFF);
    }
}

/* ==========================================================================
 * SEND 24-BIT ADDRESS (MSB FIRST)
 *
 * INTERVIEW: W25Q32 address space = 22 bits (4MB = 2^22)
 *   Always send 3 bytes (24 bits): addr[23:16], addr[15:8], addr[7:0]
 *   Even though only 22 bits are used, upper 2 bits are ignored by device
 * ========================================================================== */
static void W25Q_SendAddress(uint32_t addr)
{
    uint8_t addrBytes[3];
    addrBytes[0] = (uint8_t)((addr >> 16) & 0xFF);  /* MSB */
    addrBytes[1] = (uint8_t)((addr >>  8) & 0xFF);
    addrBytes[2] = (uint8_t)( addr        & 0xFF);  /* LSB */
    SPI1_Transmit(addrBytes, 3);
}

/* ==========================================================================
 * READ STATUS REGISTER 1
 *
 * INTERVIEW: Poll BUSY bit before any read/write/erase
 *   Frame: CS_LOW | 0x05 | [receive 1 byte SR1] | CS_HIGH
 *   Bit0=BUSY : 1=internal operation in progress
 *   Bit1=WEL  : 1=write enable latch set (after WREN cmd)
 * ========================================================================== */
static uint8_t W25Q_ReadStatusReg1(void)
{
    uint8_t status;
    uint8_t cmd = W25Q_CMD_READ_STATUS_REG1;

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    SPI1_Receive(&status, 1);
    W25Q_CS_HIGH();

    return status;
}

/* ==========================================================================
 * WAIT UNTIL DEVICE NOT BUSY
 *
 * INTERVIEW: All write and erase operations set BUSY=1 internally.
 *   Typical times:
 *     Page Program  : typ 0.4ms, max 3ms
 *     Sector Erase  : typ 45ms,  max 400ms
 *     Block Erase   : typ 120ms, max 2000ms
 *     Chip Erase    : typ 15s,   max 200s
 *   You MUST poll BUSY=0 before next operation
 * ========================================================================== */
static void W25Q_WaitBusy(void)
{
    while (W25Q_ReadStatusReg1() & W25Q_STATUS_BUSY);
}

/* ==========================================================================
 * WRITE ENABLE
 *
 * INTERVIEW: WREN must be sent before EVERY write or erase command.
 *   After power-on or after each write/erase, WEL bit resets to 0.
 *   Frame: CS_LOW | 0x06 | CS_HIGH
 *   This is a standalone transaction (CS must toggle between WREN and write)
 * ========================================================================== */
static void W25Q_WriteEnable(void)
{
    uint8_t cmd = W25Q_CMD_WRITE_ENABLE;

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_CS_HIGH();
    /* CS HIGH after WREN is what actually latches WEL=1 */
}

/* ==========================================================================
 * READ JEDEC ID
 *
 * INTERVIEW: Used to verify correct device is connected at startup.
 *   Frame: CS_LOW | 0x9F | [MFR ID] [Mem Type] [Capacity] | CS_HIGH
 *   W25Q32: 0xEF, 0x40, 0x16
 *   Useful for self-test / board bringup
 * ========================================================================== */
uint32_t W25Q_ReadJEDEC_ID(void)
{
    uint8_t cmd = W25Q_CMD_JEDEC_ID;
    uint8_t rxBuf[3] = {0};

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    SPI1_Receive(rxBuf, 3);
    W25Q_CS_HIGH();

    /* Return as 24-bit value: [Manufacturer][MemType][Capacity] */
    return ((uint32_t)rxBuf[0] << 16) |
           ((uint32_t)rxBuf[1] <<  8) |
           ((uint32_t)rxBuf[2]);
}

/* ==========================================================================
 * SECTOR ERASE (4KB)
 *
 * INTERVIEW: Erase sets ALL bytes in sector to 0xFF.
 *   Address must be sector-aligned (lower 12 bits = 0).
 *   Sequence:
 *     1. WaitBusy()         <- ensure device idle
 *     2. WriteEnable()      <- set WEL=1
 *     3. CS_LOW
 *     4. Send 0x20 (cmd)
 *     5. Send 24-bit address
 *     6. CS_HIGH            <- this triggers the erase internally
 *     7. WaitBusy()         <- wait until erase done
 * ========================================================================== */
void W25Q_SectorErase(uint32_t addr)
{
    /* Align address to sector boundary (4KB = 0x1000) */
    addr &= ~(W25Q_SECTOR_SIZE - 1);

    W25Q_WaitBusy();
    W25Q_WriteEnable();

    uint8_t cmd = W25Q_CMD_SECTOR_ERASE_4KB;

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_SendAddress(addr);
    W25Q_CS_HIGH();             /* Erase starts on CS rising edge */

    W25Q_WaitBusy();            /* Wait up to 400ms for erase completion */
}

/* ==========================================================================
 * CHIP ERASE
 *
 * INTERVIEW: Erases entire flash. No address needed.
 *   Takes 15-200 seconds. Avoid unless absolutely necessary.
 *   Frame: CS_LOW | 0xC7 | CS_HIGH | WaitBusy()
 * ========================================================================== */
void W25Q_ChipErase(void)
{
    uint8_t cmd = W25Q_CMD_CHIP_ERASE;

    W25Q_WaitBusy();
    W25Q_WriteEnable();

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_CS_HIGH();

    W25Q_WaitBusy();            /* This can take up to 200 seconds! */
}

/* ==========================================================================
 * PAGE PROGRAM (WRITE UP TO 256 BYTES)
 *
 * INTERVIEW: Critical rules for Page Program:
 *   1. Max 256 bytes per Page Program command
 *   2. If (startAddr % 256) + dataLen > 256, data WRAPS to start of same page
 *      (not next page!) - this is a common bug
 *   3. Can only write 1->0, never 0->1 (must erase first)
 *   4. Address must be within a previously erased sector
 *
 *   Frame: CS_LOW | 0x02 | ADDR[23:16] | ADDR[15:8] | ADDR[7:0]
 *          | data[0] | data[1] | ... | data[n] | CS_HIGH
 *   Write starts on CS rising edge (internally).
 * ========================================================================== */
void W25Q_PageProgram(uint32_t addr, uint8_t *pData, uint16_t size)
{
    /* Clamp to page boundary - max 256 bytes */
    if (size > W25Q_PAGE_SIZE)
    {
        size = W25Q_PAGE_SIZE;
    }

    uint8_t cmd = W25Q_CMD_PAGE_PROGRAM;

    W25Q_WaitBusy();
    W25Q_WriteEnable();

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_SendAddress(addr);
    SPI1_Transmit(pData, size);
    W25Q_CS_HIGH();             /* Write starts internally on CS HIGH */

    W25Q_WaitBusy();            /* Wait up to 3ms for page program complete */
}

/* ==========================================================================
 * READ DATA (NORMAL READ)
 *
 * INTERVIEW: No limit on read length (auto-increments address internally).
 *   Normal Read (0x03): max 50MHz clock
 *   Fast Read   (0x0B): max 133MHz, but requires 1 dummy byte after address
 *
 *   Frame (Normal): CS_LOW | 0x03 | ADDR[23:16] | ADDR[15:8] | ADDR[7:0]
 *                   | [data0] | [data1] | ... | CS_HIGH
 *
 *   Address auto-increments after each byte. No size limit per transaction.
 * ========================================================================== */
void W25Q_ReadData(uint32_t addr, uint8_t *pBuf, uint32_t size)
{
    uint8_t cmd = W25Q_CMD_READ_DATA;

    W25Q_WaitBusy();

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_SendAddress(addr);
    SPI1_Receive(pBuf, size);
    W25Q_CS_HIGH();
}

/* ==========================================================================
 * WRITE DATA - HANDLES MULTI-PAGE WRITES
 *
 * INTERVIEW: Real-world write function splits data across page boundaries.
 *   Steps:
 *     1. Calculate offset within current page
 *     2. Write partial page if start is not page-aligned
 *     3. Write full 256-byte pages for middle
 *     4. Write remaining bytes for last partial page
 *
 *   This is important in production drivers - naive drivers that ignore
 *   page boundaries cause silent data corruption (wrap-around bug).
 * ========================================================================== */
void W25Q_WriteData(uint32_t addr, uint8_t *pData, uint32_t size)
{
    uint32_t bytesWritten = 0;
    uint32_t currentAddr  = addr;
    uint32_t remaining    = size;

    while (remaining > 0)
    {
        /* Calculate bytes remaining in current page */
        uint32_t pageOffset    = currentAddr % W25Q_PAGE_SIZE;
        uint32_t bytesInPage   = W25Q_PAGE_SIZE - pageOffset;
        uint32_t bytesToWrite  = (remaining < bytesInPage) ? remaining : bytesInPage;

        W25Q_PageProgram(currentAddr, pData + bytesWritten, (uint16_t)bytesToWrite);

        currentAddr  += bytesToWrite;
        bytesWritten += bytesToWrite;
        remaining    -= bytesToWrite;
    }
}

/* ==========================================================================
 * POWER DOWN / WAKE UP
 *
 * INTERVIEW: Flash consumes ~1-2mA active, ~1uA in power-down.
 *   Use in battery-powered applications.
 *   Must send Release Power-Down (0xAB) before any operation after sleep.
 *   Min 3us delay (tRES1) after 0xAB before flash is ready.
 * ========================================================================== */
void W25Q_PowerDown(void)
{
    uint8_t cmd = W25Q_CMD_POWER_DOWN;

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_CS_HIGH();
}

void W25Q_ReleasePowerDown(void)
{
    uint8_t cmd = W25Q_CMD_RELEASE_POWER_DOWN;

    W25Q_CS_LOW();
    SPI1_Transmit(&cmd, 1);
    W25Q_CS_HIGH();
    /* Delay >= 3us (tRES1) before next command */
    for (volatile int i = 0; i < 200; i++);   /* ~3us at 64MHz */
}

/* ==========================================================================
 * VERIFY DEVICE ID AT STARTUP
 *
 * INTERVIEW: Good practice in production code:
 *   Read JEDEC ID and compare against expected value.
 *   If mismatch -> halt or assert error (wrong device / open circuit / SPI bug)
 * ========================================================================== */
bool W25Q_VerifyDevice(void)
{
    uint32_t jedecID = W25Q_ReadJEDEC_ID();

    uint8_t manufacturer = (uint8_t)((jedecID >> 16) & 0xFF);
    uint8_t memType      = (uint8_t)((jedecID >>  8) & 0xFF);
    uint8_t capacity     = (uint8_t)( jedecID        & 0xFF);

    if ((manufacturer == W25Q32_JEDEC_MANUFACTURER) &&
        (memType      == W25Q32_JEDEC_MEM_TYPE)      &&
        (capacity     == W25Q32_JEDEC_CAPACITY))
    {
        return true;    /* W25Q32 detected correctly */
    }

    return false;       /* Wrong device or SPI communication error */
}

/* ==========================================================================
 * MAIN - USAGE EXAMPLE
 *
 * Typical NOR Flash access sequence:
 *   1. Init SPI
 *   2. Verify device (JEDEC ID check)
 *   3. Erase sector (mandatory before write)
 *   4. Write data (page program)
 *   5. Read back and verify
 * ========================================================================== */
int main(void)
{
    SPI1_Init();

    /* Step 1: Verify device */
    if (!W25Q_VerifyDevice())
    {
        /* INTERVIEW: In AUTOSAR, this would call Det_ReportError()
         * Here we just hang for debugging */
        while (1);
    }

    /* Step 2: Define test address (sector 0, start) */
    uint32_t testAddr = 0x000000;

    /* Step 3: Erase sector (MANDATORY before write) */
    W25Q_SectorErase(testAddr);

    /* Step 4: Write test data */
    uint8_t txBuf[16] = {
        0xDE, 0xAD, 0xBE, 0xEF,
        0xCA, 0xFE, 0xBA, 0xBE,
        0x01, 0x02, 0x03, 0x04,
        0x0A, 0x0B, 0x0C, 0x0D
    };
    W25Q_WriteData(testAddr, txBuf, sizeof(txBuf));

    /* Step 5: Read back and verify */
    uint8_t rxBuf[16] = {0};
    W25Q_ReadData(testAddr, rxBuf, sizeof(rxBuf));

    /* Step 6: Compare */
    bool ok = true;
    for (uint8_t i = 0; i < sizeof(txBuf); i++)
    {
        if (rxBuf[i] != txBuf[i])
        {
            ok = false;
            break;
        }
    }

    /* Result: ok=true means write-read-verify passed */
    (void)ok;

    while (1)
    {
        /* Application loop */
    }
}

/*
 * ============================================================================
 * INTERVIEW QUICK-REFERENCE SUMMARY
 * ============================================================================
 *
 * Q: Why must you erase before write?
 * A: Flash cells can only be programmed 1->0. Erase resets all bits to 1 (0xFF).
 *    Writing can only flip 1->0. If you write to un-erased memory, bits that are
 *    already 0 cannot be set back to 1 -> data corruption.
 *
 * Q: What is the smallest erase unit?
 * A: Sector = 4KB (0x1000 bytes). W25Q32 has 1024 sectors.
 *    Cannot erase less than one sector.
 *
 * Q: What is the max write per Page Program?
 * A: 256 bytes. Writing beyond 256 bytes wraps within the same page (not next).
 *
 * Q: How do you know when write/erase is done?
 * A: Poll Status Register 1, Bit 0 (BUSY). Wait until BUSY=0.
 *
 * Q: What happens if you forget Write Enable (WREN)?
 * A: Write or erase silently does nothing. WEL=0 means device ignores write cmds.
 *
 * Q: What SPI mode does W25Qxx use?
 * A: Mode 0 (CPOL=0, CPHA=0) or Mode 3 (CPOL=1, CPHA=1). Both sample on
 *    rising edge of SCK. Mode 0 is most common.
 *
 * Q: What is the BSY flag in STM32 SPI SR?
 * A: Indicates SPI shift register is still clocking. Must wait BSY=0 before
 *    pulling CS HIGH, otherwise last byte gets corrupted.
 *
 * Q: What is OVR in STM32 SPI?
 * A: Overrun - new data arrived in shift register before previous RX data was
 *    read from DR. Clear by reading DR then SR.
 *
 * Q: Why cast to (uint8_t*) when writing SPI DR?
 * A: STM32 SPI DR is 16-bit. Writing as uint16_t sends 16-bit frame.
 *    Cast to uint8_t* forces 8-bit access -> correct 8-bit frame size.
 *    Also requires DS[3:0]=0111 (8-bit) and FRXTH=1 in CR2.
 *
 * Q: How is JEDEC ID used?
 * A: Manufacturer(1B) + Memory Type(1B) + Capacity(1B).
 *    Read at startup to confirm correct flash IC is connected.
 *    W25Q32 = 0xEF, 0x40, 0x16.
 *
 * ============================================================================
 */