# STM32 Peripheral Init — Common Pattern Cheatsheet (ADC / UART / SPI)

Every peripheral driver you wrote follows the **same 7-step skeleton**. Once you see this, you stop memorizing per-peripheral code and just plug in the register names.

## The universal init sequence

1. Enable peripheral bus clock (RCC)
2. Enable GPIO port clock + set pin mode (Analog / AF / Output)
3. Select Alternate Function number (if AF pin)
4. Configure peripheral-specific settings (baud/sample-time/CPOL etc.)
5. Enable interrupt bit(s), if used
6. Enable the peripheral itself (last step, always)
7. Poll status flag → read/write data register

## Same sequence, with generic register names slotted in

1. **Enable peripheral bus clock (RCC)** — e.g. `RCC->APBENR1`, `RCC->APBENR2` (bit per peripheral: USART, SPI, ADC, I2C...)
2. **Enable GPIO port clock + set pin mode** — e.g. `RCC->IOPENR` (port clock), then `GPIOx->MODER` (`00`=input, `01`=output, `10`=AF, `11`=analog)
3. **Select Alternate Function number** (only if MODER=AF) — e.g. `GPIOx->AFR[0]` for pins 0–7, `GPIOx->AFR[1]` for pins 8–15
4. **Configure peripheral-specific settings** — e.g. `USART2->BRR` (baud), `ADC1->SMPR` (sample time), `SPI1->CR1` (CPOL/CPHA/MSTR)
5. **Enable interrupt bit(s), if used** — e.g. `USART2->CR1` (`RXNEIE`), `SPI1->CR2` (`RXNEIE`/`TXEIE`), plus `NVIC->ISER[]` to unmask at core level
6. **Enable the peripheral itself (always last)** — e.g. `ADC1->CR` (`ADEN`), `USART2->CR1` (`UE`), `SPI1->CR1` (`SPE`)
7. **Poll status flag → read/write data register** — e.g. `ADC1->ISR`(`EOC`) → `ADC1->DR`; `USART2->ISR`(`RXNE`/`TXE`) → `USART2->RDR`/`TDR`; `SPI1->SR`(`TXE`/`BSY`) → `SPI1->DR`

**Mnemonic:** `RCC → MODER → AFR → CR/config → IE → EN → ISR/DR`

## Side-by-side from your own code

| Step | ADC1 | USART2 | SPI1 |
|---|---|---|---|
| **1. Peripheral clock** | `RCC->APBENR2 \|= (1<<20)` | `RCC->APBENR1 \|= (1<<17)` | `RCC->APBENR2 \|= (1<<12)` |
| **2. GPIO port clock** | `RCC->IOPENR \|= (1<<0)` (A) | `RCC->IOPENR \|= (1<<0)` (A) | `RCC->IOPENR \|= (1<<0)/(1<<2)` (A/C) |
| **2b. GPIO pin mode** | `MODER` = `11` (Analog) — ADC pin isn't AF, it's pure analog | `MODER` = `10` (AF) on TX/RX pins | `MODER` = `10` (AF) on SCK/MISO/MOSI; CS pin = `01` (plain output, bit-banged) |
| **3. AF select** | — (analog mode has no AF number) | `GPIOA->AFR[0] \|= (AF<<pos)` | `GPIOA->AFR[0] \|= (AF<<pos)` |
| **4. Peripheral config** | `CHSELR` (pick channel), `SMPR` (sample time) | `BRR` (baud rate divider), `CR1` (word length M0/M1, parity) | `CR1` (CPOL/CPHA, `MSTR`, `SSM`/`SSI` for software NSS) |
| **5. Interrupt enable** | `CR1` EOCIE-style bit (not used in your code) | `CR1 \|= (1<<5)` → `RXNEIE` | `CR2 \|= (1<<6)/(1<<7)` → `RXNEIE`/`TXEIE` |
| **6. Peripheral enable** | `ADC1->CR \|= (1<<0)` → `ADEN` | `USART2->CR1 \|= (1<<0)` → `UE` | `SPI1->CR1 \|= (1<<6)` → `SPE` |
| **7a. "Ready" flag** | `ISR` bit0 → `ADRDY` | n/a (UE going high is enough) | n/a |
| **7b. Trigger transfer** | `CR \|= (1<<2)` → `ADSTART` | write to `TDR` starts TX automatically | write to `DR` starts the clock automatically |
| **7c. "Done/flag" bit** | `ISR` bit2 → `EOC` | `ISR` bit5 `RXNE` (rx) / bit7 `TXE` (tx) | `SR` bit1 `TXE` / bit0 `RXNE` / bit7 `BSY` |
| **Data register** | `ADC1->DR` | `USART2->RDR` (rx) / `TDR` (tx) | `SPI1->DR` |
| **Peripheral-only extra** | Regulator enable (`CR<<28`) + calibration (`CR<<31`, poll until clear) | — | — |

## The mnemonic for interviews

> **"Clock → Pin → AF → Config → IRQ → Enable → Poll → Data"**

Say this out loud for any peripheral (ADC/UART/SPI/I2C/CAN/DMA) and you can reconstruct the driver skeleton without remembering exact bit numbers — which is exactly what an interviewer wants to hear (they rarely care if you recall bit 20 vs bit 17, they care that you know the *order and why*).

## Why the order matters (good interview talking point)
- **Clock before touching registers** — writing to a peripheral register before its clock is enabled either faults (bus fault) or silently does nothing, depending on the core.
- **GPIO mode before peripheral enable** — you want the pin electrically in the right state before the peripheral starts driving/sampling it.
- **Peripheral enable is *last*** — enabling too early can latch a bad initial config (e.g., ADC calibration must finish *before* `ADEN`, SPI `CPOL/CPHA` must be set *before* `SPE`).
- **Poll status flags rather than trust timing** — `ADRDY`, `TXE`, `RXNE`, `EOC`, `BSY` all exist because peripheral clocks are usually much slower than the core, so a fixed delay is fragile.

## One gotcha worth mentioning in interviews
Your ADC code sets `ADSTART` and polls `EOC` — that's a **single-conversion, polled** model. If asked "how would you make this interrupt-driven or continuous," the answer is: enable `EOCIE` (step 5) + set `CONT` bit in `CFGR1`, then read `DR` inside `ADC1_IRQHandler` instead of polling — same skeleton, just steps 5 and 7 change roles.
