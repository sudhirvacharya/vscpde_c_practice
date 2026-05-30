## QAC Helix Warning Levels



### MY ROLES AND RESPONSBILTY 
# ADAS SW Integration & Integration Test (SWE.5)

| Level | Severity  | Meaning                              | Action                             |
|-------|-----------|--------------------------------------|------------------------------------|
| L5    | Mandatory | MISRA required rule, safety critical | Must fix — blocks release          |
| L4    | Required  | Strong MISRA advisory                | Must fix or formal deviation       |
| L3    | Advisory  | Code quality / best practice         | Fix recommended, deviation allowed |
| L2    | Info      | Style / complexity                   | Optional                           |
| L1    | Info      | Minor suggestion                     | Usually ignored                    |

---

# JIRA Ticket Guidelines

| QAC Finding  | JIRA Type       | Priority           | Assigned To        |
|--------------|-----------------|--------------------|--------------------|
| L5 violation | Bug             | Critical / Blocker | Developer          |
| L4 violation | Bug             | Major              | Developer          |
| L3 violation | Bug / Task      | Minor              | Developer / TL     |
| False positive | Task (Deviation) | —               | You raise, TL approves |

**Ticket fields to fill:**
- `Summary` : [QAC][L5] MISRA 11.3 violation in Radar_SWC.c line 204
- `Rule`     : MISRA C:2012 Rule 11.3
- `Tool`     : QAC Helix 2.x
- `File/Line`: Radar_SWC.c, Line 204
- `Linked to`: DOORS requirement ID

---

# IBM DOORS Flow

```
DOORS (requirement + ASIL level)
    ↓
ITS  (Integration Test Spec — test cases linked to DOORS req ID)
    ↓
ITR  (Integration Test Report — pass/fail results per test run)
    ↓
JIRA (bug ticket raised if test fails or QAC violation found)
```

---

# Tools Reference

| Tool          | Purpose                                              |
|---------------|------------------------------------------------------|
| TRACE32       | Flash SW, breakpoints, register read, timing         |
| CANoe         | Inject/monitor CAN-FD frames, PDU timing, E2E check  |
| EB Tresos     | MCAL/BSW config — SPI, CAN, NvM, WDT                |
| IBM DOORS     | Requirements + ASIL traceability                     |
| Oscilloscope  | Verify SPI timing, clock freq, GPIO                  |
| vTESTstudio   | Automated L3 test scripts                            |
| QAC Helix     | MISRA static analysis, L3–L5 violation detection     |
| JIRA          | Defect tracking, QAC finding tickets                 |

# ASIL Safety Levels & Coverage

| Level  | Severity         | Coverage Required                          | Example in ADAS                |
|--------|------------------|--------------------------------------------|-------------------------------|
| QM     | No safety req    | None                                       | Infotainment radar display    |
| ASIL A | Low              | Recommended MC/DC                          | Temperature monitoring        |
| ASIL B | Moderate         | Mandatory branch coverage                  | Radar object detection, CAN-FD|
| ASIL C | High             | MC/DC + independence                       | Radar alignment calibration   |
| ASIL D | Highest          | Mandatory MC/DC + independent test team    | AEB brake command             |

---

# Testing Levels

| Level          | Environment       | MCAL    | HW Needed      | Tools              | Finds                   | ASPICE  |
|----------------|-------------------|---------|----------------|--------------------|-------------------------|---------|
| L1             | Off-target        | Stubbed | No             | VectorCAST         | Unit logic bugs         | SWE.3   |
| L2 (SIL)       | PC / Simulation   | Stubbed | No             | CANoe SIL, MATLAB  | Logic, interface bugs   | SWE.4   |
| L3 (On-target) | Real ECU          | Real    | Yes            | TRACE32, CANoe     | Timing, HW, driver bugs | SWE.4/5 |
| L4             | Vehicle / HIL     | Real    | Yes + vehicle  | CANoe, INCA        | System bugs             | SWE.5   |

> **Currently performing: L3 (On-target testing) — SWE.4/SWE.5**

---

# Integration Test Examples

| Test              | Full Name                        | What is Verified                                      |
|-------------------|----------------------------------|-------------------------------------------------------|
| RCC               | Reset & Clock Control            | Reset sources (POR/WDT/SMU), PLL lock, clock freq     |
| NvM Integrity     | Non-Volatile Memory Check        | CRC validation, ROM default on mismatch, DEM event    |
| OS Running        | AUTOSAR OS Verification          | Task scheduling, runnable timing, no overrun          |
| DTC Check         | Diagnostic Trouble Code          | DEM event logging, fault storage in NvM               |
| RTE Validation    | Runtime Environment Check        | SWC port connections, signal routing, data type match |
| Fault Injection   | Safety Mechanism Test            | FiM inhibition, safe state, DEM on sensor failure     |
| E2E Check         | End-to-End Protection            | CRC/counter on CAN-FD safety PDUs                     |
| WDT Test          | Watchdog Timer                   | Starve WDT, verify reset, check SCU_RSTSTAT           |

---