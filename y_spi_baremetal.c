#include "stm32g0xx.h"
#include <stdint.h>
#include <stdbool.h>

/* ─────────────────────────────────────────────
 * SPI1_Init
 * Configures PLL clock, GPIO alternate functions,
 * and SPI1 control registers for master mode.
 * ───────────────────────────────────────────── */
void SPI1_Init(void)
{
    /* 1. Configure PLL clock source
     * PLLCFGR: set PLLM divider = 1 (bits [5:0])
     * << 0 means writing to bit position 0 */
    RCC->PLLCFGR = (2 << 0);

    /* 2. Enable GPIOA and SPI1 peripheral clocks */
    RCC->IOPENR  |= RCC_IOPENR_GPIOAEN;
    RCC->APBENR2 |= RCC_APBENR2_SPI1EN;

    /* 3. Set PA5 (SCK), PA6 (MISO), PA7 (MOSI) to Alternate Function mode
     * MODER bits: 10 = Alternate Function
     * Clear 2 bits per pin first, then set to 0b10 */
    GPIOA->MODER &= ~((3 << 10) | (3 << 12) | (3 << 14));
    GPIOA->MODER |=  ((2 << 10) | (2 << 12) | (2 << 14));

    /* 4. Assign AF0 to PA5, PA6, PA7 (SPI1 on STM32G0)
     * AFR[0] controls pins 0-7, each pin uses 4 bits
     * PA5 = bits[23:20], PA6 = bits[27:24], PA7 = bits[31:28] */
    GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 24) | (0xF << 28));
    GPIOA->AFR[0] |=  ((0x0 << 20) | (0x0 << 24) | (0x0 << 28)); /* AF0 */

    /* 5. Configure SPI1 Control Register 1 (CR1)
     * Bit 2 (MSTR) = 1 → Master mode
     * CPOL = 0 → Clock idle LOW  (Mode 0)
     * CPHA = 0 → Sample on first edge (Mode 0)
     * BR[2:0] = 0b000 → fPCLK/2 (fastest clock speed)
     * SSM = 1, SSI = 1 → Software slave management */
    SPI1->CR1 = (1 << 2)   /* MSTR  */
              | (0 << 1)   /* CPOL=0 */
              | (0 << 0)   /* CPHA=0 */
              | (0 << 3)   /* BR: fPCLK/2 */
              | (1 << 9)   /* SSM: software NSS */
              | (1 << 8);  /* SSI: internal slave select high */

    /* 6. Enable SPI1 (SPE bit 6) */
    SPI1->CR1 |= (1 << 6);
}

/* ─────────────────────────────────────────────
 * SPI1_TransceiveByte
 * Sends 1 byte and returns the received byte.
 * INTERVIEW: SPI is full-duplex — every transmit
 * also clocks in a byte from the slave.
 * ───────────────────────────────────────────── */
static uint8_t SPI1_TransceiveByte(uint8_t data)
{
    /* Wait until TX buffer is empty (TXE flag) */
    while (!(SPI1->SR & SPI_SR_TXE));
    *(volatile uint8_t *)&SPI1->DR = data;

    /* Wait until RX buffer has data (RXNE flag) */
    while (!(SPI1->SR & SPI_SR_RXNE));
    return (uint8_t)SPI1->DR;
}

/* ─────────────────────────────────────────────
 * SPI1_Receive
 * Reads 'size' bytes from slave.
 * INTERVIEW: Master must send dummy bytes (0xFF)
 * to generate SCK pulses — slave has no clock of its own.
 * ───────────────────────────────────────────── */
static void SPI1_Receive(uint8_t *pBuf, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        /* Dummy 0xFF clocks out SCK so slave can shift data in */
        pBuf[i] = SPI1_TransceiveByte(0xFF);
    }
}

/* ─────────────────────────────────────────────
 * main
 * Write data to W25Q flash, read it back, verify.
 * ───────────────────────────────────────────── */
int main(void)
{
    SPI1_Init();

    uint32_t testAddr   = 0x000000;
    uint8_t  txBuf[16]  = "HelloFlash123456";

    /* Step 1-4: Write data to W25Q flash memory */
    W25Q_WriteData(testAddr, txBuf, sizeof(txBuf));

    /* Step 5: Read back from same address */
    uint8_t rxBuf[16] = {0};
    W25Q_ReadData(testAddr, rxBuf, sizeof(rxBuf));

    /* Step 6: Verify write == read
     * INTERVIEW: ok=true means write→read→verify passed */
    bool ok = true;
    for (int i = 0; i < 16; i++) {
        if (txBuf[i] != rxBuf[i]) { ok = false; break; }
    }
    (void)ok; /* Inspect in debugger or set breakpoint here */

    while (1)
    {
        /* Application loop */
    }
}