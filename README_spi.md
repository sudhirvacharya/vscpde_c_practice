# AUTOSAR SPI MCAL — Major Configuration Parameters Reference

---

## 1. SPI DRIVER OVERVIEW

SPI (Serial Peripheral Interface) in AUTOSAR is a **synchronous, full-duplex** serial communication driver.
It is part of the **MCAL layer** and sits under the **Communication Drivers** cluster.

```
Application / SWC
      |
   RTE / COM
      |
  SPI Handler/Driver  (Spi.c / Spi_Cfg.c)
      |
  HW Abstraction (QSPI / DSPI Module)
      |
  MCU Hardware (e.g., AURIX QSPI0..4)
```

### Three-Level Configuration Model

```
SpiDriver
  └── SpiSequence[0..N]       ← Unit of transmission (API level)
        └── SpiJob[0..N]      ← One CS assertion cycle
              └── SpiChannel[0..N]  ← Buffer of data elements
```

---

## 2. DRIVER LEVEL PARAMETERS (`SpiGeneral`)

| Parameter | Values | Description |
|---|---|---|
| `SpiLevelDelivered` | `0` | Only synchronous API (`Spi_SyncTransmit`) |
| | `1` | Only asynchronous API (`Spi_AsyncTransmit`) |
| | `2` | Both sync and async |
| `SpiChannelBuffersAllowed` | `0` | Internal buffers (IB) only |
| | `1` | External buffers (EB) only |
| | `2` | Both IB and EB |
| `SpiMainFunctionPeriod` | Time in seconds | Period of `Spi_MainFunction()` for async polling |
| `SpiInterruptibleSeqAllowed` | `TRUE` / `FALSE` | Allow higher-priority sequence to interrupt lower |
| `SpiSupportConcurrentSyncTransmit` | `TRUE` / `FALSE` | Allow concurrent sync transmissions on different HW units |

---

## 3. CHANNEL PARAMETERS (`SpiChannel`)

Channel = smallest data unit; holds a buffer of data elements.

| Parameter | Values | Description |
|---|---|---|
| `SpiChannelId` | `0`–`N` | Unique channel identifier |
| `SpiChannelType` | `IB` | Internal Buffer — fixed size, managed by driver |
| | `EB` | External Buffer — user-provided pointer at runtime |
| `SpiDataWidth` | `1`–`32` bits | Width of one data element (e.g., `8`, `16`, `32`) |
| `SpiDefaultData` | Hex value | Dummy data transmitted when Tx buffer is NULL |
| `SpiEbMaxLength` | `1`–`N` | Max elements for EB channel |
| `SpiIbNBuffers` | `1`–`N` | Number of elements in IB channel |
| `SpiTransferStart` | `MSB` | MSB transmitted first |
| | `LSB` | LSB transmitted first |

---

## 4. JOB PARAMETERS (`SpiJob`)

Job = one complete CS assertion + data transfer + CS de-assertion cycle.

| Parameter | Values | Description |
|---|---|---|
| `SpiJobId` | `0`–`N` | Unique job identifier |
| `SpiJobPriority` | `0`–`3` | `3` = highest priority |
| `SpiJobEndNotification` | Function pointer | Callback on job completion |
| `SpiHwUnit` | `CSIB0`..`CSIB4` | Which HW SPI unit handles this job (e.g., QSPI0) |
| `SpiCsIdentifier` | `CS0`..`CSN` | Chip select pin used |
| `SpiCsPolarity` | `HIGH` | CS active high |
| | `LOW` | CS active low (most common) |
| `SpiCsSelection` | `CS_VIA_PERIPHERAL_ENGINE` | CS controlled by HW peripheral |
| | `CS_VIA_GPIO` | CS controlled manually via GPIO |
| `SpiBaudrate` | Hz (e.g., `1000000`) | SPI clock frequency for this job |
| `SpiTimeClk2Cs` | ns | Delay between clock and CS assertion |
| `SpiTimeCs2Clk` | ns | Delay between CS assertion and first clock |
| `SpiTimeCs2Cs` | ns | Idle time between two consecutive jobs |

---

## 5. SPI CLOCK MODE — CPOL & CPHA

| Parameter | Values | Description |
|---|---|---|
| `SpiShiftClockIdleLevel` | `LOW` | CPOL = 0 — clock idle low |
| | `HIGH` | CPOL = 1 — clock idle high |
| `SpiDataShiftEdge` | `LEADING` | CPHA = 0 — data captured on leading edge |
| | `TRAILING` | CPHA = 1 — data captured on trailing edge |

### SPI Modes Summary

| Mode | CPOL | CPHA | `SpiShiftClockIdleLevel` | `SpiDataShiftEdge` |
|---|---|---|---|---|
| Mode 0 | 0 | 0 | `LOW` | `LEADING` |
| Mode 1 | 0 | 1 | `LOW` | `TRAILING` |
| Mode 2 | 1 | 0 | `HIGH` | `LEADING` |
| Mode 3 | 1 | 1 | `HIGH` | `TRAILING` |

---

## 6. SEQUENCE PARAMETERS (`SpiSequence`)

Sequence = ordered list of jobs transmitted as one logical unit.

| Parameter | Values | Description |
|---|---|---|
| `SpiSequenceId` | `0`–`N` | Unique sequence identifier |
| `SpiSeqEndNotification` | Function pointer | Callback on sequence completion |
| `SpiInterruptibleSequence` | `TRUE` | Can be interrupted by higher-priority sequence |
| | `FALSE` | Runs to completion without interruption |
| Job list | List of `SpiJobRef` | Ordered job references in this sequence |

---

## 7. ASYNC MODE — INTERRUPT vs POLLING

| Parameter | Values | Description |
|---|---|---|
| `SpiAsyncMode` (runtime) | `SPI_INTERRUPT_MODE` | ISR drives job completion, no polling needed |
| | `SPI_POLLING_MODE` | `Spi_MainFunction()` must be called periodically |

> Set at runtime via `Spi_SetAsyncMode(SPI_INTERRUPT_MODE)`.
> Polling mode is safer for timing-critical OSEK/AUTOSAR OS tasks.

---

## 8. BUFFER TYPES — IB vs EB

### Internal Buffer (IB)
- Buffer allocated **inside the driver** (static memory).
- Size fixed at config time via `SpiIbNBuffers`.
- Write data: `Spi_WriteIB(ChannelId, *DataBufferPtr)`
- Read data: `Spi_ReadIB(ChannelId, *DataBufferPtr)`

### External Buffer (EB)
- Buffer provided by the **caller at runtime**.
- No static allocation in driver.
- Set buffer: `Spi_SetupEB(ChannelId, *SrcDataPtr, *DesDataPtr, Length)`
- Useful for large/variable-length transfers.

---

## 9. SPI SEQUENCE STATE MACHINE

```
                    Spi_AsyncTransmit(SeqId)
                           |
         +-----------------v-----------------+
         |              PENDING              |
         |    (queued, waiting for HW)       |
         +-----------------+-----------------+
                           |
                   HW becomes free
                           |
         +-----------------v-----------------+
         |              ACTIVE               |
         |    (transmission in progress)     |
         +-----------------+-----------------+
                           |
               (all jobs in sequence done)
                           |
         +-----------------v-----------------+
         |               OK                  |
         |     (sequence completed OK)       |
         +-----------------------------------+

         On error:
         +-----------------v-----------------+
         |              FAILED               |
         +-----------------------------------+
```

---

## 10. KEY API CALLS

| API | Purpose |
|---|---|
| `Spi_Init(*ConfigPtr)` | Initialize SPI driver |
| `Spi_DeInit()` | De-initialize SPI driver |
| `Spi_WriteIB(Channel, *DataPtr)` | Write to internal buffer |
| `Spi_ReadIB(Channel, *DataPtr)` | Read from internal buffer |
| `Spi_SetupEB(Channel, *Src, *Dst, Length)` | Setup external buffer |
| `Spi_SyncTransmit(Sequence)` | Blocking synchronous transmit |
| `Spi_AsyncTransmit(Sequence)` | Non-blocking asynchronous transmit |
| `Spi_GetSequenceResult(Sequence)` | Poll sequence result (`OK/PENDING/FAILED`) |
| `Spi_GetJobResult(Job)` | Poll job result |
| `Spi_GetStatus()` | Overall driver status (`IDLE/BUSY/UNINIT`) |
| `Spi_SetAsyncMode(Mode)` | Switch between INTERRUPT / POLLING mode |
| `Spi_Cancel(Sequence)` | Cancel a pending sequence |
| `Spi_MainFunction()` | Polling handler — call from SchM task |

---

## 11. SYNC vs ASYNC TRANSMIT

| Aspect | `Spi_SyncTransmit` | `Spi_AsyncTransmit` |
|---|---|---|
| Blocking | YES — waits until done | NO — returns immediately |
| Notification | Not used | `SpiJobEndNotification` / `SpiSeqEndNotification` |
| Level required | `SpiLevelDelivered = 0 or 2` | `SpiLevelDelivered = 1 or 2` |
| Usage | Simple, low-frequency | High-throughput, background transfers |
| Risk | CPU stall on long transfers | Needs careful sequence/job priority |

---

## 12. QUICK CHEAT SHEET — COMMON CONFIGS

```
8-bit sensor read (e.g., TLE5012 angle sensor):
  SpiDataWidth      = 8 or 16
  SpiCsPolarity     = LOW
  SpiShiftClkIdle   = LOW   (CPOL=0)
  SpiDataShiftEdge  = TRAILING (CPHA=1)  → SPI Mode 1
  SpiBaudrate       = 5000000 (5 MHz)
  SpiChannelType    = IB

External Flash (W25Q32 / SPI NOR):
  SpiDataWidth      = 8
  SpiCsPolarity     = LOW
  SpiShiftClkIdle   = LOW   (CPOL=0)
  SpiDataShiftEdge  = LEADING (CPHA=0)  → SPI Mode 0
  SpiBaudrate       = 10000000 (10 MHz)
  SpiChannelType    = EB  (variable length commands)

High-speed DAC output (e.g., DAC8551):
  SpiDataWidth      = 16 or 32
  SpiCsPolarity     = LOW
  SpiShiftClkIdle   = LOW
  SpiDataShiftEdge  = LEADING → SPI Mode 0
  SpiBaudrate       = 20000000 (20 MHz)
  SpiChannelType    = IB
```

---

## 13. EB TRESOS CONFIG PATH (AURIX Reference)

```
SpiDriver
  └── SpiGeneral
        ├── SpiLevelDelivered
        ├── SpiChannelBuffersAllowed
        └── SpiMainFunctionPeriod

  └── SpiChannel[0..N]
        ├── SpiChannelId
        ├── SpiChannelType (IB/EB)
        ├── SpiDataWidth
        ├── SpiDefaultData
        ├── SpiIbNBuffers / SpiEbMaxLength
        └── SpiTransferStart (MSB/LSB)

  └── SpiJob[0..N]
        ├── SpiJobId
        ├── SpiJobPriority
        ├── SpiHwUnit
        ├── SpiCsIdentifier
        ├── SpiCsPolarity
        ├── SpiCsSelection
        ├── SpiBaudrate
        ├── SpiShiftClockIdleLevel  (CPOL)
        ├── SpiDataShiftEdge        (CPHA)
        ├── SpiTimeClk2Cs / SpiTimeCs2Clk / SpiTimeCs2Cs
        ├── SpiJobEndNotification
        └── SpiChannelList → SpiChannelRef[0..N]

  └── SpiSequence[0..N]
        ├── SpiSequenceId
        ├── SpiInterruptibleSequence
        ├── SpiSeqEndNotification
        └── SpiJobList → SpiJobRef[0..N]
```

---

## 14. COMMON INTERVIEW POINTS

- **Why 3-level model?** Sequence → Job → Channel separates *scheduling* (sequence), *CS control* (job), and *data* (channel). Allows reuse of channels across jobs.
- **IB vs EB?** IB = static, simple, small data. EB = dynamic, zero-copy, large transfers.
- **Why SpiDefaultData?** When Tx buffer is NULL (receive-only), dummy data keeps the clock running so slave can respond.
- **Job Priority 0–3?** Only meaningful in async mode with `SpiInterruptibleSeqAllowed = TRUE`.
- **CPOL/CPHA confusion?** Always verify with slave device datasheet — check which edge latches data.
- **CS via GPIO vs Peripheral?** GPIO CS gives software timing control; Peripheral CS is faster and HW-managed.

---

*Reference: AUTOSAR SWS SPI Handler/Driver — `AUTOSAR_SWS_SPIHandlerDriver.pdf`*
*HW Reference: Infineon AURIX TC2xx User Manual — QSPI chapter*


