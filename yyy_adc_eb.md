# AUTOSAR MCAL ADC Driver Configuration in EB TRESOS

A step-by-step guide to configuring the AUTOSAR MCAL ADC driver in the EB TRESOS environment

---

## Prerequisites

- EB TRESOS Studio installed with your AUTOSAR platform loaded
- A project with the MCAL ADC module added
- Basic familiarity with AUTOSAR layering (MCAL, ECU Abstraction, RTE)
- Knowledge of the target MCU's ADC hardware (resolution, reference voltage, clock)

---
## Step 1: Open the ADC Module Configuration
## Step 2: Set Global ADC Parameters (`AdcGeneral`)
## Step 3: Configure the ADC Hardware Unit (`AdcHwUnit`)
## Step 4: Define ADC Channels (`AdcChannel`)
## Step 5: Configure Channel Groups (`AdcChannelGroup`)
## Step 6: Configure Notifications

## Step 7: Result Buffer Setup
## Step 8: Validate & Generate

## Step 9: Integrate & Test
## Step 10: Common Pitfalls
## Step 1: Open the ADC Module Configuration

1. In TRESOS Studio's **Project Explorer**, expand your ECU Configuration.
2. Under **BSW Modules**, find and double-click **Adc**.
3. The Module Configuration Editor opens with the following hierarchy:

```
AdcGeneral (Global Config)
└── AdcHwUnit (Hardware Unit)
    ├── AdcChannel (Channels)
    └── AdcChannelGroup (Channel Groups)
AdcNotifications
```

---

## Step 2: Set Global ADC Parameters (`AdcGeneral`)

| Parameter | Description |
|---|---|
| `AdcDevErrorDetect` | Enable/disable development-time DET error checks (e.g., invalid group IDs) |
| `AdcVersionInfoApi` | Include `Adc_GetVersionInfo()` API for SW version retrieval |
| `AdcAddCodeFileRef` | Reference to additional vendor-specific configuration files |
| `AdcResultAlignment` | Result bit alignment: `ADC_ALIGN_LEFT` or `ADC_ALIGN_RIGHT` |
| `AdcLowPowerStatesSupport` | Enable low-power mode transitions during idle periods |
| `AdcEnableStartStopGroupApi` | Expose `Adc_StartGroupConversion()` / `Adc_StopGroupConversion()` APIs |
| `AdcEnableReadGroupApi` | Expose `Adc_ReadGroup()` API for software result reads |
| `AdcPriorityImplementation` | `ADC_PRIORITY_NONE`, `ADC_PRIORITY_HW`, or `ADC_PRIORITY_HW_SW` |
| `AdcEnableQueuing` | Allow queuing of group conversion requests |
| `AdcGrpNotifCapability` | Enable group notification callbacks |

> **Tip:** Set `AdcDevErrorDetect = TRUE` during integration and testing. Disable for production builds to reduce overhead.

---

## Step 3: Configure the ADC Hardware Unit (`AdcHwUnit`)

Each physical ADC controller on the MCU is represented as a **Hardware Unit**.

1. Right-click **AdcHwUnit → Add AdcHwUnit**.
2. Configure the Hardware Unit settings:

| Parameter | Description |
|---|---|
| `AdcHwUnitId` | Unique numeric ID for this ADC controller (e.g., `0` for ADC0) |
| `AdcClockSource` | Clock source selection: `PCLK`, `PLL`, or MCU-specific source |
| `AdcPrescale` | Clock prescaler divider to derive the ADC sample clock |
| `AdcResolution` | ADC resolution: `8-bit`, `10-bit`, `12-bit`, `16-bit` (MCU-dependent) |
| `AdcReferenceVoltageSource` | Voltage reference: `VDDA`, `VREF+`, `Internal`, or `External` |
| `AdcConversionMode` | `ADC_CONV_MODE_ONESHOT` or `ADC_CONV_MODE_CONTINUOUS` |
| `AdcHwTriggerSource` | Hardware trigger source (timer, PWM, external pin) if used |
| `AdcTransferType` | `ADC_INTERRUPT` for ISR-driven or `ADC_DMA` for DMA transfers |
| `AdcDmaChannelId` | DMA channel number if `AdcTransferType = ADC_DMA` |
| `AdcInterruptPriority` | NVIC priority for ADC end-of-conversion interrupt |

> **Best Practice:** Use DMA transfer mode for groups with many channels or high-frequency sampling to reduce CPU load.

---

## Step 4: Define ADC Channels (`AdcChannel`)

An **ADC Channel** maps a logical channel ID to a physical MCU analog input pin.

1. Under your Hardware Unit, right-click **AdcChannel → Add AdcChannel**.
2. Fill in the channel parameters:

| Parameter | Description |
|---|---|
| `AdcChannelId` | Logical channel identifier (referenced in Channel Groups) |
| `AdcChannelAnalogInputId` | Physical MCU analog pin/mux number (e.g., `AN0`, `AN5`) |
| `AdcChannelSamplingTime` | Sampling time in ADC clock cycles — longer = more accurate for high-impedance sources |
| `AdcChannelGain` | Amplifier gain setting if the MCU supports a PGA (programmable gain amplifier) |
| `AdcChannelLowLimit` | Lower threshold for limit-check monitoring |
| `AdcChannelHighLimit` | Upper threshold for limit-check monitoring |
| `AdcChannelLimitCheck` | `TRUE` to enable out-of-range interrupt/notification |
| `AdcChannelRangeSelect` | Defines which range triggers a notification: `ADC_RANGE_BETWEEN`, `ADC_RANGE_NOT_BETWEEN`, etc. |

> **Note:** `AdcChannelSamplingTime` is critical for accuracy — always check the datasheet for minimum sampling time based on source impedance.

---

## Step 5: Configure Channel Groups (`AdcChannelGroup`)

A **Channel Group** bundles one or more ADC channels that are converted together as a single unit. This is the entity SWCs interact with via the ADC API.

1. Right-click **AdcChannelGroup → Add AdcChannelGroup**.
2. Configure the group:

| Parameter | Description |
|---|---|
| `AdcGroupId` | Unique ID used in API calls like `Adc_StartGroupConversion()` |
| `AdcGroupConversionMode` | `ADC_CONV_MODE_ONESHOT` (converts once) or `ADC_CONV_MODE_CONTINUOUS` (loops) |
| `AdcGroupTriggSource` | `ADC_TRIGG_SRC_SW` (software) or `ADC_TRIGG_SRC_HW` (hardware trigger) |
| `AdcHwTriggerSignal` | Trigger edge: `ADC_HW_TRIG_RISING_EDGE`, `FALLING_EDGE`, or `BOTH_EDGES` |
| `AdcHwTriggerTimer` | Timer resource used for periodic hardware triggering |
| `AdcGroupPriority` | Priority level — relevant when `AdcPriorityImplementation` is enabled |
| `AdcGroupReplacement` | Behavior when a higher-priority group preempts: `ADC_GROUP_REPL_ABORT_RESTART` or `ADC_GROUP_REPL_SUSPEND_RESUME` |
| `AdcGroupAccessMode` | `ADC_ACCESS_MODE_SINGLE` (one result) or `ADC_ACCESS_MODE_STREAMING` (buffer of results) |
| `AdcStreamingBufferMode` | `ADC_STREAM_BUFFER_LINEAR` (stop at end) or `ADC_STREAM_BUFFER_CIRCULAR` (wrap around) |
| `AdcStreamingNumSamples` | Number of samples to collect in streaming mode before notification |
| `AdcChannelList` | Ordered list of `AdcChannel` references belonging to this group |

> **Use Case:** Configure a group with `ADC_TRIGG_SRC_HW` and a timer for periodic sensor sampling (e.g., temperature every 10 ms) without CPU intervention.

---

## Step 6: Configure Notifications

Notifications enable upper layers to react when a group conversion completes.

1. In each `AdcChannelGroup`, set `AdcNotification` to the name of your callback function.
2. Implement the callback in your application code.

| Notification Type | Trigger Condition | Typical Use Case |
|---|---|---|
| `AdcNotification` (Group) | All channels in the group have been converted | Trigger a SWC runnable to read and process results |
| Limit Check Notification | A channel result falls outside `LowLimit`/`HighLimit` | Fault detection, threshold alarms |

> **Note:** Notifications run in interrupt context — keep callbacks short. Use an OS event or flag to defer processing to a task.

---

## Step 7: Result Buffer Setup

Before starting any group conversion, a result buffer must be assigned.

```c
/* Declare a result buffer for the group */
Adc_ValueGroupType AdcResultBuffer[ADC_GROUP0_NUM_CHANNELS];

/* Assign the buffer — must be called before Adc_StartGroupConversion() */
Adc_SetupResultBuffer(AdcGroupId_Group0, AdcResultBuffer);
```

| API | Description |
|---|---|
| `Adc_SetupResultBuffer()` | Assign a result buffer to a channel group |
| `Adc_StartGroupConversion()` | Start SW-triggered conversion (SW trigger groups only) |
| `Adc_StopGroupConversion()` | Stop a continuous conversion group |
| `Adc_ReadGroup()` | Read the latest conversion results into the application buffer |
| `Adc_GetGroupStatus()` | Poll group state: `ADC_IDLE`, `ADC_BUSY`, `ADC_COMPLETED`, `ADC_STREAM_COMPLETED` |
| `Adc_EnableHardwareTrigger()` | Arm a HW-triggered group |
| `Adc_DisableHardwareTrigger()` | Disarm a HW-triggered group |
| `Adc_EnableGroupNotification()` | Enable the group's end-of-conversion notification |
| `Adc_DisableGroupNotification()` | Disable the group's end-of-conversion notification |

---

## Step 8: Validate & Generate

1. Click **Validate Configuration** (green check icon) to catch ID conflicts or missing references.
2. Resolve all errors and warnings in the **Problems** view.
3. Select **Generate Code** — the following files are produced:
   - `Adc.h`
   - `Adc_Cfg.h`
   - `Adc_Cfg.c`
   - LLD/HLD source files

---

## Step 9: Integrate & Test

Initialize the ADC driver at startup and use the API:

```c
/* Initialize ADC driver */
Adc_Init(&AdcConfig);

/* Set up result buffer before starting */
Adc_SetupResultBuffer(AdcGroupId_Group0, AdcResultBuffer);

/* Enable notification (optional) */
Adc_EnableGroupNotification(AdcGroupId_Group0);

/* Start conversion (SW-triggered group) */
Adc_StartGroupConversion(AdcGroupId_Group0);

/* Poll for completion (or use notification callback) */
if (Adc_GetGroupStatus(AdcGroupId_Group0) == ADC_COMPLETED) {
    Adc_ReadGroup(AdcGroupId_Group0, AdcResultBuffer);
    /* Process AdcResultBuffer[] here */
}
```

Verify with a **debugger or oscilloscope** that:
- Conversion timing matches the expected sample rate
- Result values correspond to the applied input voltage
- Notifications fire at the correct intervals

---

## Common Pitfalls

| Issue | Cause | Fix |
|---|---|---|
| Result always `0` | Buffer not set up before conversion start | Always call `Adc_SetupResultBuffer()` first |
| Noisy readings | `AdcChannelSamplingTime` too short | Increase sampling time in the channel config |
| Notification never fires | Notification not enabled | Call `Adc_EnableGroupNotification()` before start |
| Wrong conversion rate | Incorrect `AdcPrescale` value | Recalculate: `f_adc = f_clk / prescaler` |
| HW trigger group not starting | Trigger source not enabled | Call `Adc_EnableHardwareTrigger()` for HW trigger groups |

---

## Summary

By following this guide in EB TRESOS, you will:

- Understand every MCAL ADC parameter and its hardware mapping
- Correctly structure channels and channel groups for your use case
- Choose between software/hardware triggering and one-shot/continuous modes
- Use streaming buffers and notifications for efficient, non-blocking ADC operation
- Integrate and test ADC conversions reliably in an AUTOSAR-compliant project