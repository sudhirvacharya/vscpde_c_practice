

# AUTOSAR ADC MCAL — Major Configuration Parameters Reference

---

## 1. CONVERSION MODE

| Parameter | Values | Description |
|---|---|---|
| `AdcGroupConversionMode` | `ADC_CONV_MODE_ONESHOT` | Single conversion per trigger |
| | `ADC_CONV_MODE_CONTINUOUS` | Repeats continuously after trigger |

---

## 2. TRIGGER SOURCE

| Parameter | Values | Description |
|---|---|---|
| `AdcGroupTriggSrc` | `ADC_TRIGG_SRC_SW` | Software trigger via `Adc_StartGroupConversion()` |
| | `ADC_TRIGG_SRC_HW` | Hardware trigger (GTM/ERU/PWM signal) |
| `AdcHwTrigSignal` | `ADC_HW_TRIG_RISING_EDGE` | Trigger on rising edge |
| | `ADC_HW_TRIG_FALLING_EDGE` | Trigger on falling edge |
| | `ADC_HW_TRIG_BOTH_EDGES` | Both edges |
| `AdcHwTrigTimer` | GTM channel ref | Which HW source drives the trigger |

---

## 3. SCAN MODE (Channel Sequencing)

| Parameter | Values | Description |
|---|---|---|
| `AdcGroupAccessMode` | `ADC_ACCESS_MODE_SINGLE` | One result per read |
| | `ADC_ACCESS_MODE_STREAMING` | Streaming buffer (circular/linear) |
| `AdcStreamingNumSamples` | `1`, `N` | Number of samples per channel in streaming |
| `AdcStreamingBufferMode` | `ADC_STREAM_BUFFER_LINEAR` | Stops after buffer full |
| | `ADC_STREAM_BUFFER_CIRCULAR` | Overwrites oldest sample |
| Channel sequence | List of `AdcChannel` refs | Defines scan order within group |

---

## 4. RESOLUTION

| Parameter | Values | Description |
|---|---|---|
| `AdcChannelResolution` | `ADC_RESOLUTION_8BIT` | 8-bit |
| | `ADC_RESOLUTION_10BIT` | 10-bit |
| | `ADC_RESOLUTION_12BIT` | **12-bit — most common automotive** |
| | `ADC_RESOLUTION_14BIT` | 14-bit |
| | `ADC_RESOLUTION_16BIT` | 16-bit |
| | `ADC_RESOLUTION_24BIT` | 24-bit (DSADC / sigma-delta, e.g. AURIX) |

> **AURIX TC2xx/TC3xx note:**
> - **VADC (SAR ADC)** → up to **12-bit** resolution
> - **DSADC (Delta-Sigma ADC)** → up to **24-bit** resolution, used for current/torque sensing

---

## 5. PRIORITY & QUEUE

| Parameter | Values | Description |
|---|---|---|
| `AdcGroupPriority` | `0` – `N` | Higher number = higher priority |
| `AdcPriorityImplementation` | `ADC_PRIORITY_NONE` | No priority mechanism |
| | `ADC_PRIORITY_HW` | HW arbitration |
| | `ADC_PRIORITY_HW_SW` | HW + SW arbitration |
| `AdcGroupReplacementPriority` | `ADC_GROUP_REPL_ABORT_RESTART` | Abort lower-priority group |
| | `ADC_GROUP_REPL_SUSPEND_RESUME` | Suspend and resume lower-priority group |

---

## 6. NOTIFICATION (ISR / Callback)

| Parameter | Values | Description |
|---|---|---|
| `AdcNotification` | Function pointer | Called on group conversion complete |
| `AdcGroupConversionMode` | — | Determines when notification fires |

> Enable via `Adc_EnableGroupNotification()` at runtime.

---

## 7. CHANNEL-LEVEL PARAMETERS

| Parameter | Values | Description |
|---|---|---|
| `AdcChannelId` | `0`–`N` | Physical channel number |
| `AdcChannelSampTime` | Cycles | Sample-and-hold time |
| `AdcChannelLimitCheck` | `TRUE` / `FALSE` | Enable limit monitoring |
| `AdcChannelHighLimit` | Raw ADC value | Upper threshold |
| `AdcChannelLowLimit` | Raw ADC value | Lower threshold |
| `AdcChannelRangeSelect` | `ADC_RANGE_BETWEEN` etc. | Limit check range mode |

---

## 8. CLOCK & TIMING

| Parameter | Description |
|---|---|
| `AdcClockSourceSelect` | Peripheral clock source selection |
| `AdcPrescale` | Clock divider for ADC module |
| `AdcConversionTime` | Total = sample time + conversion cycles |

---

## 9. GROUP STATE MACHINE

```
                    Adc_StartGroupConversion()
                            |
         +------------------v------------------+
         |               BUSY                  |
         |     (conversion in progress)        |
         +------------------+------------------+
                            |
               (one scan done)
                            |
         +------------------v------------------+
         |            COMPLETED                |
         |   (single / first stream done)      |
         +------------------+------------------+
                            |
           (all streaming samples done)
                            |
         +------------------v------------------+
         |        STREAM_COMPLETED             |
         +-------------------------------------+
                            |
           CONTINUOUS mode: loops back to BUSY
```

### Key API Calls

| API | Purpose |
|---|---|
| `Adc_Init()` | Initialize ADC driver |
| `Adc_StartGroupConversion(GroupId)` | SW trigger — start conversion |
| `Adc_StopGroupConversion(GroupId)` | Stop continuous group |
| `Adc_ReadGroup(GroupId, *DataBufferPtr)` | Read conversion results |
| `Adc_GetGroupStatus(GroupId)` | Poll group state |
| `Adc_EnableGroupNotification(GroupId)` | Enable callback/ISR |
| `Adc_DisableGroupNotification(GroupId)` | Disable callback/ISR |
| `Adc_GetStreamLastPointer(GroupId, **PtrToSamplePtr)` | Get last valid streaming sample |

---

## 10. QUICK CHEAT SHEET — MODE COMBINATIONS

```
Single-shot  + SW trigger  →  ONESHOT    + TRIGG_SRC_SW
                               Call Adc_StartGroupConversion() each time

Continuous   + SW trigger  →  CONTINUOUS + TRIGG_SRC_SW
                               Runs until Adc_StopGroupConversion()

Single-shot  + HW trigger  →  ONESHOT    + TRIGG_SRC_HW
                               PWM-sync sampling, no SW call needed

Scan/Stream  + HW trigger  →  STREAMING  + TRIGG_SRC_HW + N samples
                               Buffer fills on each HW trigger cycle
```

---

## 11. EB TRESOS PATH (AURIX Reference)

```
AdcGeneral
  └── AdcHwUnit[0..N]          ← Maps to VADC Group 0,1,2...
        └── AdcGroup[0..N]
              ├── AdcGroupConversionMode
              ├── AdcGroupTriggSrc
              ├── AdcGroupPriority
              ├── AdcGroupAccessMode
              ├── AdcStreamingNumSamples
              ├── AdcStreamingBufferMode
              ├── AdcNotification
              └── AdcGroupDefinition
                    └── AdcChannelRef[0..N]
                          ├── AdcChannelId
                          ├── AdcChannelResolution
                          ├── AdcChannelSampTime
                          └── AdcChannelLimitCheck
```

---

*Reference: AUTOSAR SWS ADC Driver — `AUTOSAR_SWS_ADCDriver.pdf`*
*HW Reference: Infineon AURIX TC2xx User Manual — VADC / DSADC chapters*


