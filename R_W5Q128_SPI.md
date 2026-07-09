# W25Q128 SPI NOR Flash — Reference Notes

## 1. Device Overview

| Parameter | Value |
|---|---|
| Capacity | 128 Mbit = 16 MByte |
| JEDEC ID | `EF 40 18` (Manufacturer: Winbond `0xEF`, Memory Type: `0x40`, Capacity: `0x18`) |
| Page size | 256 bytes |
| Sector size | 4 KB (4096 bytes) — smallest erasable unit |
| Block size | 32 KB and 64 KB (erase granularity options) |
| Total sectors | 4096 |
| Total 64KB blocks | 256 |
| Addressing | 24-bit (3-byte address), max `0xFFFFFF` = exactly 16MB − 1 |
| Voltage | 2.7V–3.6V typical |
| Max SPI clock | Up to 104 MHz (standard SPI mode, part-dependent) |
| Interface modes | Standard SPI, Dual SPI, Quad SPI (QE bit required) |

**Why 24-bit addressing still works:** W25Q128 capacity (16MB) exactly equals `2^24` bytes, so the standard 3-byte address command set covers the whole chip. Parts larger than this (e.g. W25Q256 = 32MB) need 4-byte addressing or an extended address register — a common gotcha when porting a driver upward in the family.

---

## 2. Command Set Used in the Driver

| Operation | Opcode | Notes |
|---|---|---|
| Write Enable | `0x06` | Must precede every program/erase operation |
| Write Disable | `0x04` | Clears WEL bit |
| Read Status Register 1 | `0x05` | Bit0 = BUSY, Bit1 = WEL |
| Read Data | `0x03` | Standard speed, no dummy cycles |
| Fast Read | `0x0B` | Needs 1 dummy byte, higher clock capable |
| Page Program | `0x02` | Max 256 bytes, must not cross page boundary |
| Sector Erase (4KB) | `0x20` | ~400ms typical erase time |
| Block Erase (64KB) | `0xD8` | Much faster per-byte than looping sector erase |
| Chip Erase | `0xC7` | Full 16MB — takes **minutes**, not seconds |
| JEDEC ID | `0x9F` | Returns 3 bytes: mfg, type, capacity |

**BUSY bit polling pattern** used throughout:
```
Write Enable → Send Command (+ addr + data) → CS High → Poll SR1.BUSY until 0
```
This is the same "check-busy-before-next-op" discipline as AUTOSAR MCAL flash drivers — the SPI transaction completing doesn't mean the flash's internal write/erase cycle is done.

---

## 3. Why Page Program Is Capped at 256 Bytes

The flash's internal write pointer wraps within a page — if you send more than 256 bytes in one Page Program command, or start mid-page and cross into the next page, address bits silently wrap back to the start of the *same* page instead of rolling into the next one. This is a classic corruption bug if the driver doesn't enforce page alignment. The `w25q_page_program()` guard (`len > W25Q_PAGE_SIZE` → return) only checks length — **it's still the caller's job** to ensure `addr` doesn't cross a page boundary when `addr` isn't page-aligned.

---

## 4. Erase Granularity Trade-off (relevant for 16MB parts)

| Erase type | Time (typical) | Use case |
|---|---|---|
| Sector (4KB) | ~400ms | Fine-grained, e.g. wear-leveled log storage |
| Block (32KB) | ~1.6s | Medium regions |
| Block (64KB) | ~2s | Bulk region clear — much more efficient per-byte than looping 16x sector erase |
| Chip erase | Minutes | Full reflash / factory reset only |

On a 16MB part with 4096 sectors, clearing a large region via looped 4KB sector erase is far slower than using 64KB block erase — worth choosing deliberately based on how the storage layout above the driver is structured (e.g. wear-leveling algorithm block size).

---

## 5. SPI Peripheral Config (STM32G070, SPI1)

| Setting | Value | Reason |
|---|---|---|
| Mode | Master | MCU drives the clock |
| CPOL/CPHA | 0/0 (SPI Mode 0) | W25Q family samples on rising edge, idle clock low |
| NSS management | Software (`SSM=1`, `SSI=1`) | /CS is a plain GPIO (PA4), not hardware NSS |
| Data size | 8-bit | `DS = 0b0111` in CR2 |
| FIFO threshold | `FRXTH=1` | RXNE fires on 8-bit (not default 16-bit) threshold — required for byte-wise polling reads |
| Baud rate | fPCLK/8 | Conservative; can be raised if signal integrity on the Nucleo jumper wires allows |

---

## 6. Quad SPI — Not Used Here, But Available on This Part

W25Q128 supports Quad SPI (opcodes `0x6B` Quad Output, `0xEB` Quad I/O), gated behind the **QE bit** in Status Register 2 (repurposes `/WP` and `/HOLD` pins as IO2/IO3).

**STM32G070 limitation:** it has no dedicated QUADSPI/OCTOSPI peripheral — only standard SPI1/SPI2. True quad-mode throughput on this chip would require:
- Bit-banging 4 GPIO lines (defeats the speed purpose), or
- Moving to silicon with a hardware QUADSPI block (STM32L4+, F7, H7, etc.)

This driver stays in standard 1-1-1 SPI mode for that reason — functionally complete, just not exploiting the chip's quad capability on this particular MCU.

---

## 7. Wiring Summary (Nucleo-G070RB)

| W25Q128 pin | STM32G070 pin | Function |
|---|---|---|
| CS# | PA4 | Software GPIO, active low |
| CLK | PA5 | SPI1_SCK (AF0) |
| DO (MISO) | PA6 | SPI1_MISO (AF0) |
| DI (MOSI) | PA7 | SPI1_MOSI (AF0) |
| WP# | 3.3V (pull-up) | Tie high if not using quad mode |
| HOLD#/IO3 | 3.3V (pull-up) | Tie high if not using quad mode |
| VCC | 3.3V | |
| GND | GND | |

**Note:** WP# and HOLD# must be pulled high in standard SPI mode, or the chip can misbehave (WP# low blocks writes to protected status bits; HOLD# low pauses the SPI transaction mid-byte).

---

## 8. Known Gaps / Next Steps

- No DMA variant yet (current driver is blocking/polling only — fine for bring-up, not ideal for large transfers holding up the CPU).
- No 4-byte address mode support (not needed for W25Q128, but relevant if you later port this to W25Q256 or larger).
- No dual/quad SPI support on this MCU (see §6).
- No AUTOSAR-style Channel/Job/Sequence abstraction layer — current API is a flat function set, not layered like your ADC/SPI MCAL reference docs.
