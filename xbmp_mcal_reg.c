#include <stdio.h>
#include <stdint.h>

/*
 * Control Register Bit-Field Layout (32-bit register)
 *
 * Bit  0     : enable (n)       - 1-bit  : peripheral enable flag
 * Bits 1-3   : addr             - 3-bits : target address select (0-7)
 * Bit  4     : parity (p)       - 1-bit  : parity enable flag
 * Bits 5-31  : reserved
 */
typedef struct
{
    uint32_t enable  : 1;   /* bit 0     : peripheral enable          */
    uint32_t addr    : 3;   /* bits 1-3  : address select (0 to 7)    */
    uint32_t parity  : 1;   /* bit 4     : parity enable              */
    uint32_t reserved: 27;  /* bits 5-31 : reserved, keep 0           */
} CtrlReg_Bits_t;

typedef union
{
    uint32_t       reg;     /* full 32-bit register access            */
    CtrlReg_Bits_t bit;     /* individual bit-field access            */
} CtrlReg_t;

/* Peripheral control register mapped to a fixed hardware address */
#define CTRL_REG_BASE_ADDR    0x40001000UL

volatile CtrlReg_t * const pCtrlReg = (volatile CtrlReg_t *)CTRL_REG_BASE_ADDR;

int main(void)
{
    /* --- 1. Clear the whole register first (safe init) --- */
    pCtrlReg->reg = 0x00000000UL;

    /* --- 2. Set individual bit-fields --- */
    pCtrlReg->bit.enable = 1u;   /* enable peripheral                 */
    pCtrlReg->bit.addr   = 5u;   /* select address line 5 (3-bit max) */
    pCtrlReg->bit.parity = 1u;   /* enable parity check               */

    /* --- 3. Read back and verify --- */
    printf("Full register value : 0x%08X\n", pCtrlReg->reg);
    printf("  enable  (bit 0)   : %u\n",     pCtrlReg->bit.enable);
    printf("  addr    (bits 1-3): %u\n",     pCtrlReg->bit.addr);
    printf("  parity  (bit 4)   : %u\n",     pCtrlReg->bit.parity);

    return 0;
}