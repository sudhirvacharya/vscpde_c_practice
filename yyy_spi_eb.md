# AUTOSAR MCAL SPI Driver Configuration in EB TRESOS

A step-by-step guide covering every key parameter — from global settings down to channels, jobs, and sequences.

---

## Prerequisites

- EB TRESOS Studio installed with your AUTOSAR platform loaded
- A project with the MCAL SPI module added
- Basic familiarity with AUTOSAR layering (MCAL, ECU Abstraction, RTE)

---

## Step 1: Open the SPI Module Configuration

1. In TRESOS Studio's **Project Explorer**, expand your ECU Configuration.
2. Under **BSW Modules**, find and double-click **Spi**.
3. The Module Configuration Editor opens with the following hierarchy:

```
Global Config
└── Hardware Units
    ├── Channels
    ├── Jobs
    └── Sequences
Notifications
```

---

## Step 2: Set Global SPI Parameters

| Parameter | Description |
|---|---|
| `SpiDevErrorDetect` | Enable/disable development-time error checks (e.g., null pointers) |
| `SpiVersionInfoApi` | Include `Spi_GetVersionInfo()` API for SW version retrieval |
| `SpiTimeoutDuration` | Max wait time for sync transmissions (in OS ticks or μs) |
| `SpiMaxJobCount` | Maximum jobs defined — used for internal array sizing |
| `SpiMaxSequenceCount` | Maximum sequences defined |
| `SpiDisableToIdle` | Gate clocks when idle to save power |

> **Tip:** Set `SpiDevErrorDetect = TRUE` during integration, then disable for production to minimize overhead.

---

## Step 3: Configure Hardware Units

Each physical SPI controller is represented as a **Hardware Unit**.

1. Add a Hardware Unit (e.g., `SPI0`, `SPI1`).
2. Expand it to configure Controller Settings:

| Parameter | Description |
|---|---|
| `HwUnitId` | Unique numeric ID matching RTE-generated IDs |
| `SpiHwChannelId` | MCU-specific channel index (maps to register block) |
| `Spi_CPOL` / `CPHA` | Clock polarity & phase (Mode 0–3) |
| `SpiBaudRatePrescaler` | Divider from peripheral clock to generate SCLK |
| `SpiClkSource` | Select PCLK, PLL, or external clock source |
| `SpiDataWidth` | 8-bit, 16-bit, etc. — defines FIFO width |
| `SpiUseDma` | `TRUE` to offload to DMA; `FALSE` for interrupt/polling |
| `SpiDmaChannelTx/Rx` | DMA channel numbers if `SpiUseDma = TRUE` |
| `SpiInterruptPriority` | NVIC priority level for SPI interrupts |

> **Best Practice:** Use DMA for large or frequent transfers; use interrupts for small bursts.

---

## Step 4: Define Channels

A **Channel** represents one element (byte/word) in a transfer.

1. Under your Hardware Unit, right-click **Channels → Add Channel**.
2. Fill in the parameters:

| Parameter | Description |
|---|---|
| `ChannelId` | Unique ID used in Jobs/Sequences and generated code |
| `ChannelType` | `SPI_CHANNEL_MODE_NORMAL` or `SPI_CHANNEL_MODE_ULTRASPEED` |
| `DefaultData` | Value sent when no TX buffer is provided (`0x00`–`0xFF`) |
| `BufferType` | `INTERNAL` (MCAL-managed) or `EXTERNAL` (app-provided) |
| `BufferAddressAlignment` | Alignment constraint for external buffers (e.g., 4-byte) |
| `ShiftClockEdge` | Edge at which data is shifted out/in (rising/falling) |
| `DataWidth` | Matches HwUnit's `SpiDataWidth`; can be overridden per channel |
| `SdoEnable` | `TRUE` if the channel participates in receiving data (MISO) |

> **Note:** Channels inherit defaults from their parent Hardware Unit — override only as needed.

---

## Step 5: Group Channels into Jobs

A **Job** bundles one or more channels into an atomic hardware transaction.

1. Right-click **Jobs → Add Job**.
2. Configure the following:

| Parameter | Description |
|---|---|
| `JobId` | Unique numeric ID |
| `HwUnitId` | The SPI controller this job uses |
| `JobPriority` | Relative priority — higher number = higher precedence |
| `DataIntegrityCheck` | Enable CRC or parity check if supported |
| `EnableNotification` | `TRUE` to invoke a `JobEndNotification` on completion |
| `StartMode` | `IMMEDIATE` (starts on submit) or `QUEUED` (waits in queue) |
| `ChannelList` | Ordered list of Channels this Job will transmit/receive |

> **Tip:** Assign higher priority to time-critical SPI operations (e.g., sensor reads).

---

## Step 6: Build Sequences of Jobs

A **Sequence** defines the end-to-end transaction requested by a SWC.

1. Right-click **Sequences → Add Sequence**.
2. Fill out:

| Parameter | Description |
|---|---|
| `SequenceId` | Unique ID used in `Spi_SyncTransceive()` / `Spi_AsyncTransceive()` |
| `JobList` | Ordered list of Jobs to execute |
| `RepeatCount` | Number of times to loop the sequence before returning to idle |
| `EnableEndNotification` | `TRUE` to call a `SequenceEndNotification` when all Jobs complete |
| `ErrorBehavior` | On Job failure: `ABORT_SEQUENCE` or `CONTINUE_WITH_NEXT` |

> **Use Case:** Group a "command + address + data" read operation for an SPI flash device.

---

## Step 7: Configure Notifications

Notifications allow upper layers to react when transfers finish.

1. Under **Notifications**, link to an AUTOSAR Task or ISR.
2. For each Job/Sequence with `EnableNotification = TRUE`, assign the appropriate callback.

| Notification Type | Use Case |
|---|---|
| `JobEndNotification` | Signal partial completion (e.g., first chunk done) |
| `SequenceEndNotification` | Wake a SWC's runnable to process the full received data |

---

## Step 8: Validate & Generate

1. Click **Validate Configuration** (green check icon) to catch missing IDs or mismatches.
2. Resolve any errors/warnings in the **Problems** view.
3. Select **Generate Code** — the following files are produced:
   - `Spi.h`
   - `Spi_Cfg.h`
   - `Spi_Cfg.c`
   - LLD source files

---

## Step 9: Integrate & Test

Include the generated files in your build, then initialize the driver at startup:

```c
Spi_Init(&SpiConfig);
```

Trigger an asynchronous transfer using:

```c
Spi_AsyncTransceive(SequenceId_ReadSensor, RxBuffer);
```

Verify correct behavior with a **logic analyzer or oscilloscope** — check SCLK, MOSI, MISO, and CS signals.

---

## Summary

By following this guide in EB TRESOS, you will:

- Understand every MCAL SPI parameter and its purpose
- Ensure deterministic, portable SPI behavior across platforms
- Leverage notifications and error handling for robust Software Components