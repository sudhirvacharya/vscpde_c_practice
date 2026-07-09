/*
 * main.c
 * Bare-metal W25Q128 SPI NOR Flash driver + demo, STM32G070 (Nucleo-G070RB)
 * Cortex-M0+, register-level SPI1, polling mode, software /CS on PA4
 *
 * Device: W25Q128 (128 Mbit = 16 MByte), JEDEC ID EF 40 18
 *   - 24-bit addressing still valid (max addr 0xFFFFFF = 16MB-1, exact fit)
 *   - 4096 sectors x 4KB, 256 blocks x 64KB, 256-byte page program (same as W25Q32)
 *
 * Pin mapping (SPI1):
 *   PA5 - SCK
 *   PA6 - MISO
 *   PA7 - MOSI
 *   PA4 - /CS (software controlled GPIO)
 *
 * Requires CMSIS device header from your STM32CubeIDE project
 * (adjust the include below if your project uses stm32g070xx.h directly).
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32g0xx.h"

/* ======================= W25Q Command Set ======================= */
#define W25Q_CMD_WRITE_ENABLE       0x06U
#define W25Q_CMD_WRITE_DISABLE      0x04U
#define W25Q_CMD_READ_STATUS_REG1   0x05U
#define W25Q_CMD_READ_STATUS_REG2   0x35U
#define W25Q_CMD_WRITE_STATUS_REG1  0x01U
#define W25Q_CMD_READ_DATA          0x03U
#define W25Q_CMD_FAST_READ          0x0BU
#define W25Q_CMD_PAGE_PROGRAM       0x02U
#define W25Q_CMD_SECTOR_ERASE_4K    0x20U
#define W25Q_CMD_BLOCK_ERASE_32K    0x52U
#define W25Q_CMD_BLOCK_ERASE_64K    0xD8U
#define W25Q_CMD_CHIP_ERASE         0xC7U
#define W25Q_CMD_POWER_DOWN         0xB9U
#define W25Q_CMD_RELEASE_POWERDOWN  0xABU
#define W25Q_CMD_JEDEC_ID           0x9FU
#define W25Q_CMD_ENABLE_RESET       0x66U
#define W25Q_CMD_RESET_DEVICE       0x99U

/* Status Register 1 bits */
#define W25Q_SR1_BUSY   (1U << 0)
#define W25Q_SR1_WEL    (1U << 1)

#define W25Q_PAGE_SIZE          256U
#define W25Q_SECTOR_SIZE        4096U
#define W25Q_BLOCK_SIZE_64K     65536U
#define W25Q128_TOTAL_SIZE      0x1000000U   /* 16 MB */
#define W25Q128_SECTOR_COUNT    (W25Q128_TOTAL_SIZE / W25Q_SECTOR_SIZE)   /* 4096 sectors */
#define W25Q128_EXPECTED_MFG_ID 0xEFU
#define W25Q128_EXPECTED_MEM_TYPE 0x40U
#define W25Q128_EXPECTED_CAPACITY 0x18U

typedef struct {
    uint8_t manufacturer_id;
    uint8_t memory_type;
    uint8_t capacity;
} w25q_id_t;

/* ======================= CS control (PA4) ======================= */
#define CS_LOW()   (GPIOA->BSRR = (1U << (4U + 16U)))   /* reset PA4 */
#define CS_HIGH()  (GPIOA->BSRR = (1U << 4U))            /* set PA4 */

/* ======================= Low level SPI1 byte transfer ======================= */
static uint8_t spi1_transfer(uint8_t data)
{
    while (!(SPI1->SR & SPI_SR_TXE)) { }
    *(volatile uint8_t *)&SPI1->DR = data;   /* 8-bit write to DR */

    while (!(SPI1->SR & SPI_SR_RXNE)) { }
    return *(volatile uint8_t *)&SPI1->DR;   /* 8-bit read from DR */
}

/* ======================= GPIO + SPI1 peripheral init ======================= */
static void w25q_init(void)
{
    /* 1. Enable clocks: GPIOA, SPI1 */
    RCC->IOPENR  |= RCC_IOPENR_GPIOAEN;
    RCC->APBENR2 |= RCC_APBENR2_SPI1EN;

    /* 2. Configure PA5(SCK), PA6(MISO), PA7(MOSI) as AF0 (SPI1) */
    GPIOA->MODER &= ~((3U << (5U * 2U)) | (3U << (6U * 2U)) | (3U << (7U * 2U)));
    GPIOA->MODER |=  ((2U << (5U * 2U)) | (2U << (6U * 2U)) | (2U << (7U * 2U))); /* AF mode */

    GPIOA->AFR[0] &= ~((0xFU << (5U * 4U)) | (0xFU << (6U * 4U)) | (0xFU << (7U * 4U)));
    /* AF0 = SPI1 on PA5/PA6/PA7 for STM32G070 - verify against datasheet AF table */

    GPIOA->OSPEEDR |= (3U << (5U * 2U)) | (3U << (6U * 2U)) | (3U << (7U * 2U)); /* high speed */

    /* 3. Configure PA4 as GPIO output for /CS, default high (deselected) */
    GPIOA->MODER &= ~(3U << (4U * 2U));
    GPIOA->MODER |=  (1U << (4U * 2U));      /* output mode */
    GPIOA->OTYPER &= ~(1U << 4U);            /* push-pull */
    CS_HIGH();

    /* 4. Configure SPI1: Master, CPOL=0, CPHA=0, 8-bit, software NSS, baud/8 */
    SPI1->CR1 = 0;
    SPI1->CR1 |= SPI_CR1_MSTR;               /* master mode */
    SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;  /* software slave management, internal NSS high */
    SPI1->CR1 |= (2U << SPI_CR1_BR_Pos);     /* baud = fPCLK/8, tune per your clock config */
    /* CPOL=0, CPHA=0 -> mode 0 (default bits already 0) */

    SPI1->CR2 = 0;
    SPI1->CR2 |= (7U << SPI_CR2_DS_Pos);     /* 8-bit data size */
    SPI1->CR2 |= SPI_CR2_FRXTH;              /* RXNE event on 8-bit threshold */

    SPI1->CR1 |= SPI_CR1_SPE;                /* enable SPI */
}

/* ======================= JEDEC ID ======================= */
static w25q_id_t w25q_read_id(void)
{
    w25q_id_t id;

    CS_LOW();
    spi1_transfer(W25Q_CMD_JEDEC_ID);
    id.manufacturer_id = spi1_transfer(0xFF);
    id.memory_type      = spi1_transfer(0xFF);
    id.capacity          = spi1_transfer(0xFF);
    CS_HIGH();

    return id;
}

/* ======================= Status register ======================= */
static uint8_t w25q_read_status_reg1(void)
{
    uint8_t status;

    CS_LOW();
    spi1_transfer(W25Q_CMD_READ_STATUS_REG1);
    status = spi1_transfer(0xFF);
    CS_HIGH();

    return status;
}

static bool w25q_is_busy(void)
{
    return (w25q_read_status_reg1() & W25Q_SR1_BUSY) != 0U;
}

static void w25q_wait_busy(void)
{
    while (w25q_is_busy()) { }
}

/* ======================= Write enable / disable ======================= */
static void w25q_write_enable(void)
{
    CS_LOW();
    spi1_transfer(W25Q_CMD_WRITE_ENABLE);
    CS_HIGH();
}

static void w25q_write_disable(void)
{
    CS_LOW();
    spi1_transfer(W25Q_CMD_WRITE_DISABLE);
    CS_HIGH();
}

/* ======================= Read data (any length, 0x03 command) ======================= */
static void w25q_read_data(uint32_t addr, uint8_t *buf, uint32_t len)
{
    CS_LOW();
    spi1_transfer(W25Q_CMD_READ_DATA);
    spi1_transfer((uint8_t)(addr >> 16));
    spi1_transfer((uint8_t)(addr >> 8));
    spi1_transfer((uint8_t)(addr));

    for (uint32_t i = 0U; i < len; i++) {
        buf[i] = spi1_transfer(0xFF);
    }
    CS_HIGH();
}

/* ======================= Page program (max 256 bytes, must not cross page) ======================= */
static void w25q_page_program(uint32_t addr, const uint8_t *buf, uint32_t len)
{
    if (len == 0U || len > W25Q_PAGE_SIZE) {
        return; /* invalid length for a single page program */
    }

    w25q_write_enable();

    CS_LOW();
    spi1_transfer(W25Q_CMD_PAGE_PROGRAM);
    spi1_transfer((uint8_t)(addr >> 16));
    spi1_transfer((uint8_t)(addr >> 8));
    spi1_transfer((uint8_t)(addr));

    for (uint32_t i = 0U; i < len; i++) {
        spi1_transfer(buf[i]);
    }
    CS_HIGH();

    w25q_wait_busy();
}

/* ======================= Sector erase (4KB) ======================= */
static void w25q_sector_erase(uint32_t addr)
{
    w25q_write_enable();

    CS_LOW();
    spi1_transfer(W25Q_CMD_SECTOR_ERASE_4K);
    spi1_transfer((uint8_t)(addr >> 16));
    spi1_transfer((uint8_t)(addr >> 8));
    spi1_transfer((uint8_t)(addr));
    CS_HIGH();

    w25q_wait_busy();
}

/* ======================= Block erase (32KB / 64KB) ======================= */
static void w25q_block_erase_64k(uint32_t addr)
{
    w25q_write_enable();

    CS_LOW();
    spi1_transfer(W25Q_CMD_BLOCK_ERASE_64K);
    spi1_transfer((uint8_t)(addr >> 16));
    spi1_transfer((uint8_t)(addr >> 8));
    spi1_transfer((uint8_t)(addr));
    CS_HIGH();

    w25q_wait_busy();
}

/* ======================= Chip erase ======================= */
static void w25q_chip_erase(void)
{
    w25q_write_enable();

    CS_LOW();
    spi1_transfer(W25Q_CMD_CHIP_ERASE);
    CS_HIGH();

    w25q_wait_busy();   /* note: full-chip erase on 16MB can take minutes, not seconds */
}

/* ======================= Demo ======================= */
static uint8_t tx_buf[W25Q_PAGE_SIZE];
static uint8_t rx_buf[W25Q_PAGE_SIZE];

int main(void)
{
    w25q_init();

    /* --- Step 1: Read JEDEC ID (sanity check chip is alive) --- */
    w25q_id_t id = w25q_read_id();
    /* Expected for W25Q128: manufacturer 0xEF, memory_type 0x40, capacity 0x18 */
    if (id.manufacturer_id != W25Q128_EXPECTED_MFG_ID ||
        id.memory_type      != W25Q128_EXPECTED_MEM_TYPE ||
        id.capacity          != W25Q128_EXPECTED_CAPACITY) {
        while (1) { /* trap: unexpected/no device detected, or wrong part - check wiring */ }
    }

    /* --- Step 2: Erase sector at address 0x000000 ---
     * (use w25q_block_erase_64k() instead when clearing larger regions
     *  on the 16MB W25Q128 - much faster than looping sector erase) */
    w25q_sector_erase(0x000000U);

    /* --- Step 3: Prepare test pattern and program one page --- */
    for (uint32_t i = 0U; i < W25Q_PAGE_SIZE; i++) {
        tx_buf[i] = (uint8_t)i;
    }
    w25q_page_program(0x000000U, tx_buf, W25Q_PAGE_SIZE);

    /* --- Step 4: Read back and verify --- */
    w25q_read_data(0x000000U, rx_buf, W25Q_PAGE_SIZE);

    bool ok = (memcmp(tx_buf, rx_buf, W25Q_PAGE_SIZE) == 0);

    while (1) {
        /* ok == true  -> program/erase/read cycle verified
         * ok == false -> mismatch, check SPI wiring/timing/CS
         * (breakpoint here in debugger to check 'ok')
         */
        (void)ok;
    }
}