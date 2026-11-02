# ISO 26262 / AUTOSAR Functional Safety — Interview Notes (Merged & De-duplicated)
*Focus: embedded / AUTOSAR MCAL / NXP MPC575x. Verify part-specific details against your derivative's Reference Manual, the MCAL/BSW Safety Manual and the standard itself.*
*Sources: own notes + ISO 26262-6 software infographic (Khader Basha, LinkedIn: https://www.linkedin.com/feed/update/urn:li:activity:7488924890750918656/).*

---

## 1. What It Is

ISO 26262 is the functional safety standard for **road-vehicle E/E systems**. It defines how to avoid or control **systematic failures** and **random hardware failures** that could cause harm, across the full lifecycle: concept → system / HW / SW development → production → operation → decommissioning.

> **One-liner:** "ISO 26262 defines how to systematically manage the risk of failures in automotive E/E systems, using ASIL levels to scale rigor based on severity, exposure and controllability."

| Term | Meaning |
|---|---|
| Functional safety | Absence of unreasonable risk due to hazards from E/E malfunction |
| Hazard | Potential source of harm from malfunctioning behavior |
| Safety goal (SG) | Top-level safety requirement derived from HARA |
| FSR / TSR / SSR | Functional / Technical / Software Safety Requirement (SG → FSR → TSR → SSR) |
| Safe state | Operating mode without unreasonable risk (torque off, limp-home, fail-silent) |
| FTTI | Fault Tolerant Time Interval — fault to hazard if no reaction; detection + reaction must be shorter |
| Systematic fault | Deterministic cause (spec/design/process) → mitigated by process rigor |
| Random HW fault | Stochastic (bit flip, stuck-at, aging) → mitigated by diagnostics + metrics |
| Latent fault | Neither detected nor perceived; hidden until a second fault |
| Black channel | Transport path (e.g. COM stack) treated as untrusted; integrity ensured end-to-end by E2E |

---

## 2. ASIL — Automotive Safety Integrity Level

Levels: **QM → A → B → C → D** (D most rigorous). Determined in **HARA** from:

| Factor | Scale |
|---|---|
| Severity (S) | S0–S3 |
| Exposure (E) | E0–E4 |
| Controllability (C) | C0–C3 |

- Examples: brake-by-wire / steering loss → D; unintended airbag deployment → D; wiper failure → A/QM; infotainment → QM.
- **ASIL is inherited** by every element implementing the safety goal, unless decomposed.
- **ASIL decomposition** (Part 9): split a requirement into redundant, *independent* elements (D → B(D)+B(D), or C(D)+A(D)); independence proven via DFA.
- ASIL ≠ SIL (IEC 61508).

### 2.1 Exposure (E) scale
E = how often / how long the vehicle is in the situation where the hazard can occur.

| Level | Meaning | Approx. duration / frequency | Example |
|---|---|---|---|
| E0 | Incredibly unlikely | Not rated | Exotic situations |
| E1 | Very low probability | Very rare | Towing, unusual road conditions |
| E2 | Low probability | < 1% of operating time | Reversing out of a steep driveway |
| E3 | Medium probability | 1–10% of operating time | Overtaking, heavy rain |
| E4 | High probability | > 10% of operating time / almost every drive | Normal driving, braking, turning |

(Percentages are approximate guidance from ISO 26262-3; check the standard for exact wording.)

### 2.2 ASIL lookup table (S × E × C)
| | | E1 | E2 | E3 | E4 |
|---|---|---|---|---|---|
| **S1** | C1 | QM | QM | QM | QM |
| | C2 | QM | QM | QM | A |
| | C3 | QM | QM | A | B |
| **S2** | C1 | QM | QM | QM | A |
| | C2 | QM | QM | A | B |
| | C3 | QM | A | B | C |
| **S3** | C1 | QM | QM | A | B |
| | C2 | QM | A | B | C |
| | C3 | A | B | C | D |

**Shortcut:** S + E + C = 10 → D, 9 → C, 8 → B, 7 → A, ≤ 6 → QM. Example: S3 + E4 + C3 = 10 → ASIL D (brake-by-wire: severe, always exposed, driver can't control).

### 2.3 HARA vs TARA
**HARA** (ISO 26262-3, safety): define item → identify malfunctions/hazards → define operating situations → rate S/E/C → ASIL → safety goals with safe state and FTTI.
**TARA** (ISO/SAE 21434 clause 15, security): identify assets and security properties (C/I/A) → damage scenarios → threat scenarios (e.g. STRIDE) → attack paths and feasibility → risk value → treatment (avoid, reduce, share, retain) → cybersecurity goals/claims.

| | HARA | TARA |
|---|---|---|
| Standard | ISO 26262-3 | ISO/SAE 21434 |
| Concern | Safety (random / systematic faults) | Security (intentional attacks) |
| Cause | Malfunction | Malicious actor |
| Rating | S × E × C | Impact × attack feasibility |
| Result | ASIL A–D | Risk value / CAL |
| Output | Safety goals | Cybersecurity goals |

**Link:** an attack can cause a hazard, so the two are coordinated. **E2E** protects against random faults/corruption (safety); **SecOC** (MAC + freshness) protects against tampering (security). E2E alone doesn't stop an attacker who can recompute the CRC.
> "Safety asks what if it fails; security asks what if someone attacks it."

---

## 3. V-Model and Software Lifecycle

```
Concept / HARA ──────────────────────────────►  Vehicle validation
  System design ─────────────────────────►  System integration & test
    HW design / SW architecture ──────►  HW / SW integration & test
      SW unit design ───────────────►  Unit verification
              Implementation
```
**SW lifecycle (Part 6):** SSR → architectural design → unit design/implementation → unit test → integration test → software safety validation (verification of embedded software on target).
SSRs are derived from the Technical Safety Concept and the HW-SW interface (HSI), allocated to SW components, with **bidirectional traceability**: SSR ↔ architecture ↔ code ↔ test case (DOORS / Polarion).

---

## 4. Parts of ISO 26262 (2nd edition, 2018)

| Part | Topic | Why you care |
|---|---|---|
| 1 | Vocabulary | |
| 2 | Management of functional safety | Safety plan, safety case, confirmation measures |
| 3 | Concept phase | Item definition, HARA, safety goals |
| 4 | System-level development | TSC, HSI, integration |
| 5 | Hardware-level development | FMEDA, SPFM/LFM/PMHF |
| **6** | **Software-level development** | **Your daily work** |
| 7 | Production, operation, service, decommissioning | |
| 8 | Supporting processes | Config/change mgmt, tool qualification, SW component qualification |
| 9 | ASIL- and safety-oriented analyses | Decomposition, DFA, FMEA, FTA |
| 10 | Guidelines | Explanatory |
| 11 | Semiconductors | Guidance for MCU/IP vendors |
| 12 | Motorcycles | |

---

## 5. Hardware Architectural Metrics (Part 5)

| Metric | Meaning |
|---|---|
| **SPFM** | Single-Point Fault Metric — coverage of single-point & residual faults |
| **LFM** | Latent Fault Metric — coverage of latent multiple-point faults |
| **PMHF** | Probabilistic Metric for random HW Failures (FIT) |

| ASIL | SPFM | LFM | PMHF |
|---|---|---|---|
| B | ≥ 90% | ≥ 60% | < 100 FIT |
| C | ≥ 97% | ≥ 80% | < 100 FIT |
| D | ≥ 99% | ≥ 90% | < 10 FIT |

ASIL A: no mandatory targets. 1 FIT = 1 failure per 10⁹ device-hours.
**Diagnostic Coverage:** Low ≈ 60%, Medium ≈ 90%, High ≈ 99%. **FMEDA** = FMEA + diagnostic coverage + failure rates.

---

## 6. Software Development (Part 6)

### 6.1 Coding and design principles
- **MISRA C** (2012/2023): restricts unsafe/undefined constructs, consistent analyzable style, checked by static analysis; deviations documented and justified.
- Restrictions: no dynamic memory, limited recursion, no unbounded loops, no implicit type conversion, defensive programming.
- Architecture principles: hierarchical structure, restricted component/interface size, high cohesion, low coupling, restricted interrupt use, appropriate scheduling.

### 6.2 Structural coverage at unit level
| Metric | ASIL A | ASIL B | ASIL C | ASIL D |
|---|---|---|---|---|
| Statement | ++ | ++ | + | + |
| Branch | + | ++ | ++ | ++ |
| MC/DC | + | + | + | ++ |

(++ highly recommended, + recommended.) **Takeaway:** MC/DC becomes *highly recommended* only at ASIL D; branch coverage is highly recommended from ASIL B.
> ⚠ Correction: an earlier version of these notes (and the LinkedIn infographic) listed different values. Confirm against ISO 26262-6, unit-verification coverage table, before quoting exact symbols in an interview.

### 6.3 Verification and testing methods
Requirements-based testing, interface testing, fault-injection testing, resource-usage evaluation (stack, CPU, memory), back-to-back testing (model vs code), static analysis, code review/walkthrough, formal verification (higher ASIL). **Static analysis + testing together close the gap.**

### 6.4 Software safety analyses
**SW FMEA** (bottom-up failure modes), **SW FTA** (top-down, hazard → SW causes), **control-flow analysis**, **data-flow analysis**, **DFA**.

### 6.5 Key work products
SSR, software architectural design spec, unit design spec, software safety analysis report, verification reports (unit / integration / safety), software safety case.

---

## 7. Software Safety Mechanisms (with AUTOSAR module mapping)

### 7.1 Program flow / timing monitoring
| Mechanism | Detects | Notes |
|---|---|---|
| **Window / logical watchdog (WDT)** | CPU lock-up, lost program flow | Refresh gated on liveness of *all* critical tasks (supervisor/bitmask), never kicked blindly from idle |
| **Alive supervision** | Specific task stalled | Task increments counter; **WdgM** checks it within an expected window |
| **Logical program-flow monitoring** | Wrong branch, skipped step | Checkpoints compared to an expected graph |
| **Deadline / timeout supervision** | Late completion, starvation, priority inversion | |
| **CPU load / scheduling checks** | Overload, time-budget overrun | OS timers or monitor task; can raise DEM event |

### 7.2 Data integrity
| Mechanism | Detects | Notes |
|---|---|---|
| **CRC / checksum** (comms, NVM, RAM/ROM) | Corruption | Periodic verification of memory contents |
| **E2E library** (P01/02/04/05/06/07/11/22) | Corruption, loss, delay, repetition, masquerade | CRC + counter + Data ID (+ timeout) |
| **Redundant storage** (value + inverse) | Bit flips in stored values | Compare on read |
| **Plausibility / range / rate checks** | Out-of-range or implausible values | Simplest defensive check |

### 7.3 Memory & execution protection
MPU (hardware-enforced), **OS-Application partitioning** (trusted / non-trusted), **stack monitoring** (canary, SP checks), **ECC** (HW; SW handles fault flags).

### 7.4 Control flow / redundancy
Program-counter monitoring, control-flow monitoring, data-flow monitoring, **diverse redundancy / diverse design** (for higher ASIL; avoids common-mode bugs), redundant computation, comparator/voting, assertions, defensive programming, error/exception handling, software watchdog trigger.

### 7.5 Communication, startup, shutdown
- **E2E protection**, bus-off recovery, comm timeout monitoring (Com/PduR/CanSM).
- **POST** (power-on self-test of RAM/ROM/registers) before the application starts.
- **Safe-state transition logic** (fail-silent / fail-operational).

### 7.6 AUTOSAR module mapping
| Mechanism | Module |
|---|---|
| WDT / alive / logical / deadline | **WdgM** + **WdgIf** + **Wdg** driver |
| E2E | **E2E library** / E2E transformer (used with Rte/Com) |
| CPU load | **Os** + custom SWC, optional DEM report |
| Memory protection | **Os** (OS-Application, SC3/SC4) + MPU |
| Fault storage / reporting | **Dem**, escalation via **Dcm** |
| Mode / safe-state management | **EcuM / BswM**; **FiM** for function inhibition |
| Memory / core tests | **RamTst, FlsTst, CorTst**, MCU self-test |

---

## 8. Freedom From Interference (FFI) — ISO 26262-6 Annex D

A lower-ASIL/QM element must not corrupt a higher-ASIL one (needed even without HW redundancy).

| Domain | Example mechanisms |
|---|---|
| **Spatial** (memory) | MPU, OS-Application partitions, stack guards |
| **Temporal** (timing) | Watchdog, deadline / execution-time monitoring, OS timing protection, priority design |
| **Information exchange** | E2E, CRC, counters, sequence checks, timeout |

---

## 9. ASIL Relevance per AUTOSAR Layer

AUTOSAR doesn't hard-assign ASIL to layers: ASIL comes from the item's safety goals, and each element is developed/qualified for an ASIL (often as an SEooC) or is QM. Vendors ship safety variants with a **Safety Manual** (typically up to ASIL B–D).

| Layer | Typically ASIL-relevant | Typically QM |
|---|---|---|
| **MCAL** | Wdg, Mcu (clock/reset), Port (register lock), Adc/Spi/Dio/Pwm/Gpt in safety paths, Fls ECC handling, RamTst/FlsTst/CorTst | Drivers used only for non-safety functions |
| **ECU abstraction** | WdgIf, IoHwAb (plausibility, redundancy, actuator feedback), MemIf for safety data | CanIf/LinIf/EthIf (black channel) |
| **Service layer** | Safety OS, WdgM, E2E/Crc libraries, EcuM, FiM, NvM (safety data), Dem when feeding safety reactions | Dcm, Det, most comm-management |
| **RTE** | Generated; ASIL depends on **generator tool qualification**; enforces partitioning, hosts E2E transformer | |
| **SWC** | Per component, from the safety goal | Non-safety functions |

**COM stack is QM, yet carries ASIL signals:** black-channel principle — the stack is untrusted; **E2E at both ends** (CRC, counter, Data ID, timeout) detects any corruption. Safety responsibility sits in the E2E library and the SWC handling the E2E status.
**Mixed ASIL:** separate OS-Applications + MPU + timing protection; BSW running trusted must be at least as high ASIL as the highest-ASIL SWC depending on it.

---

## 10. Tool Qualification (Part 8) and SEooC

- **TI** (Tool Impact: TI1/TI2), **TD** (Tool error Detection: TD1–TD3) → **TCL1–TCL3**.
- Methods: increased confidence from use, development per safety standard, process evaluation, tool validation.
- Examples: compilers (GHS, HighTec, Tasking), static analyzers, VectorCAST, EB Tresos, DaVinci, RTE generator.
- **SEooC:** developed without a specific item; supplier assumes ASIL, safety goals, FTTI and documents **Assumptions of Use**; integrator validates them against the real item using the Safety Manual.

---

## 11. NXP MPC575x — Hardware Safety Mechanisms

### 11.1 STCU2 — Self-Test Control Unit
- **Controls and sequences** built-in self-tests at startup (offline) and, on some devices, runtime; collects pass/fail. It doesn't test by itself.
- Faults go to the **FCCU** → reaction (interrupt, reset, fault pin).

| BIST | Tests | Detects |
|---|---|---|
| **LBIST** | Digital logic via scan chains, PRPG patterns, MISR signature | Stuck-at / transition faults → **latent faults** |
| **MBIST** | SRAM / cache / buffers with March algorithms | Cell, decoder, coupling faults |

LBIST/MBIST at power-up finds latent faults runtime mechanisms can't see → improves **LFM**.

### 11.2 Memory fault models MBIST targets
| Your note | Standard term |
|---|---|
| Single bit error | Single-bit / stuck-at fault (SAF) |
| Multi bit error | Multiple-cell fault |
| Read destructive | Read Destructive Fault (RDF) |
| Write destructive | Write Destructive Fault (WDF) |
| Data retention | Data Retention Fault (DRF) |
| "IO coupling" | **Coupling fault (CF)** |
| (other) | Transition (TF), Address decoder (AF), Stuck-open |

These are memory **fault models** that MBIST (e.g. March C−) catches, not "10 STCU test cases".

### 11.3 ECC
- **SECDED** (e.g. 8 ECC bits / 64 data bits). Single-bit: corrected, logged via **MEMU**. Double-bit: detected → FCCU / machine check → safe state.
- Covers flash, SRAM, caches, DMA TCDs, some peripheral RAMs; often includes the address (detects wrong-address access).
- Firmware: **initialize SRAM** before first read, periodic **scrubbing**, ECC error-injection tests.

### 11.4 CRC
- Integrity (not security): boot ROM check, NVM/config, comms payload; HW CRC unit (DMA-driven) or SW table-based.
- Polynomials: CRC-8 SAE-J1850 (0x1D, E2E P1), CRC-16 CCITT, CRC-32/CRC-32P4 (E2E P4).
- Limit: strong against bursts, **not** masquerade/repetition/sequence errors → add counter + Data ID.

### 11.5 E2E protection (AUTOSAR)
Fault types: corruption, repetition, loss, insertion, wrong sequence, masquerade, delay, blocking.

| Mechanism | Detects |
|---|---|
| CRC | Data corruption |
| Alive / sequence counter | Repetition, loss, wrong sequence, stuck sender |
| Data ID | Masquerade, wrong addressing, insertion |
| Receiver timeout | Delay, loss, blocking |

Profiles: P01 (CRC8 + 4-bit counter + Data ID nibble), P02 (CRC8 + 4-bit counter + Data ID list), P04/05/06/07 (larger CRC, 16/32-bit counters), P11/P22 (CAN-optimized).
Receiver status: `E2E_P_OK`, `WRONGCRC`, `REPEATED`, `WRONGSEQUENCE`, `NONEWDATA`, `ERROR`, `OKSOMELOST`; `E2E_SMCheck` maps to VALID / INVALID / NODATA / INIT.

### 11.6 Other safety blocks and HW mechanisms by fault source
| Fault source | Block / mechanism |
|---|---|
| CPU | **Lockstep** (delayed lockstep e200z cores), SW core test (CorTst), LBIST |
| Flash | ECC, CRC, FlsTst |
| RAM | ECC, MBIST, RamTst (March), **MEMU** logging |
| Registers | Read-back, redundant config, write-protect/lock |
| Clock | **CMU**, independent-clock watchdog |
| Power | Voltage monitors (LVD/HVD), brown-out reset |
| Fault handling | **FCCU** (collects HW faults; IRQ / reset / FCCU_F pins) |
| Isolation | **MPU / SMPU**, ECC on DMA/XBAR/bridges |
| Sensor input | Plausibility, redundant sensors, ADC self-test |
| Actuator output | Feedback monitoring, redundant paths, safe-state drive |

**Safe-start sequence:** Reset → boot → STCU2 LBIST + MBIST → check STCU2 status → FCCU init → clock/voltage monitor config → SRAM init → CRC check of flash → start OS / application.

### 11.7 Your MCAL safety measures
Register read-back after write, ADC group redundancy/plausibility, SPI/CAN with E2E/CRC, timeout protection, DMA integrity checks.

---

## 12. Safety Analysis Techniques
| Technique | Type | Used for |
|---|---|---|
| HARA | Top-down | Hazards → ASIL → safety goals |
| FTA | Top-down, deductive | Root causes, PMHF |
| FMEA | Bottom-up, inductive | Component failure modes |
| FMEDA | Bottom-up + DC | Quantitative HW metrics |
| DFA | Common-cause / cascading failures | Independence for decomposition / FFI |
| Safety case | Argument | Evidence safety goals are met |

---

## 13. Interview Q&A

**Q1. What is ISO 26262 and why is it needed?**
Functional safety standard for automotive E/E; systematic process plus technical measures so failures don't cause unreasonable risk.

**Q2. How is ASIL determined?**
HARA: Severity × Exposure × Controllability → QM/A/B/C/D per hazard; the safety goal inherits it.

**Q3. Systematic vs random hardware faults?**
Systematic: deterministic cause, handled by process rigor. Random: stochastic, handled by diagnostics and quantified with SPFM/LFM/PMHF.

**Q4. What is FTTI?**
Time from fault to hazard if unmitigated; detection + reaction must be shorter.

**Q5. SPFM, LFM, PMHF?**
Single-point/residual coverage, latent-fault coverage, absolute failure rate (see §5).

**Q6. What is ASIL decomposition?**
Splitting a requirement into independent redundant elements with lower ASILs (D → B(D)+B(D)), proven via DFA.

**Q7. Three dimensions of FFI? How do you stop a QM SWC corrupting an ASIL-D SWC?**
Spatial, temporal, information exchange. Use OS-Applications (trusted/non-trusted) with MPU, OS timing protection, and E2E — an ISO 26262-6 Annex D mechanism.

**Q8. What does STCU do on MPC57xx? LBIST vs MBIST?**
Sequences BIST at startup and reports to FCCU. LBIST: logic via scan + PRPG + MISR. MBIST: memory arrays with March algorithms (cell, decoder, coupling, retention).

**Q9. ECC single vs double error?**
SECDED: single-bit corrected and logged; double-bit detected and reported (FCCU/exception) → safe state.

**Q10. Why isn't CRC alone enough? What does E2E add?**
CRC covers corruption only. Counter covers repetition/loss/sequence, Data ID covers masquerade/insertion, timeout covers delay/loss.

**Q11. Latent fault and how to cover it?**
Undetected, unperceived fault, dangerous with a second fault; covered by startup/periodic tests (BIST, RamTst, FlsTst, ADC self-test), improving LFM.

**Q12. Which AUTOSAR module does watchdog supervision? Why alive counters on top of a watchdog?**
**WdgM** over the Wdg driver (alive, deadline, logical). A blind WDT refresh can't tell if a specific task stalled; alive supervision checks each monitored task individually.

**Q13. Coverage across ASILs?**
Statement: highly recommended for A/B, recommended C/D. Branch: highly recommended from B. MC/DC: recommended A–C, highly recommended D (confirm in the standard).

**Q14. SEooC and Safety Manual?**
SEooC = element developed against assumed context; the Safety Manual lists assumptions of use, mechanisms and integrator obligations.

**Q15. Safe state example?**
Disable torque request / limp-home / disable actuator output / controlled stop.

**Q16. Confirmation measures?**
Confirmation review, functional safety audit, functional safety assessment; independence rises with ASIL.

**Q17. ASIL B vs D software testing?**
More methods highly recommended: MC/DC, fault injection, formal methods, stronger independence, tighter metrics.

**Q18. Protecting an ADC reading?**
Range + plausibility, redundant channel/sensor, reference self-test channel, conversion timeout, DMA result integrity, DEM reporting.

**Q19. Detecting a stuck CAN signal?**
E2E alive counter (`REPEATED`), timeout (`NONEWDATA`), CRC, signal plausibility.

**Q20. ISO 26262 vs ASPICE?**
ASPICE = process maturity; ISO 26262 = safety lifecycle and technical safety. SWE.5 integration testing contributes Part 6 evidence.

**Q21. How does ISO 26262 affect your MCAL work?**
MISRA C, traceable requirements, config review (EB Tresos), register protection, ASIL-scaled coverage, fault-injection tests, tool qualification, following the MCAL Safety Manual.

**Q22. Is COM stack QM? How does it carry ASIL data?**
Yes, treated as QM (black channel); ASIL data is protected end-to-end with E2E in sender and receiver.

**Q23. Which AUTOSAR layers are ASIL-relevant?**
No fixed assignment; safety MCAL (Wdg, Mcu, test modules), IoHwAb, safety OS, WdgM, E2E, EcuM, and the SWC for the safety goal. See §9.

**Q24. What must every safety requirement / mechanism specify?**
ASIL, safe state, reaction time within the FTTI, diagnostic coverage, verification method (review, unit test, fault injection, HIL), and traceability up to the safety goal and down to design and tests (see §14).

**Q25. Give an example of a safety goal → FSR → TSR chain.**
SG-01 "prevent unintended torque output" → FSR-01 "detect incorrect sensor input and reach safe state within FTTI 50 ms" → TSR-ADC-01 "ADC driver plausibility-checks each result against min/max and reports to DET/DEM".

---

## 14. Requirement Hierarchy Example (as seen in DOORS)

**Chain:** Safety Goal (SG) → Functional Safety Requirement (FSR) → Technical Safety Requirement (TSR) → design → code → test.

- **SG-01 (system level, ASIL C):** The system shall prevent unintended torque output.
- **FSR-01:** The ECU shall detect incorrect sensor input values and transition to a safe state within the FTTI of 50 ms.

### TSRs allocated to software / BSW
| ID | Requirement | ASIL | Component |
|---|---|---|---|
| TSR-ADC-01 | ADC driver plausibility-checks each conversion result against configured min/max and reports a DET/DEM error on violation | C | MCAL ADC |
| TSR-ADC-02 | ADC driver detects conversion timeout and reports `ADC_E_TIMEOUT` to DEM within 1 ms | B | MCAL ADC |
| TSR-SPI-01 | SPI handler verifies each transmitted frame with CRC-8 (SAE J1850) and discards frames on mismatch | C | MCAL SPI / complex driver |
| TSR-CAN-01 | COM stack protects safety-relevant signals with E2E Profile 1 (CRC + alive counter + Data ID) | D | E2E library |
| TSR-CAN-02 | If E2E check returns `E2E_P01STATUS_WRONGCRC` or `WRONGSEQUENCE` for 3 consecutive cycles, receiver substitutes the signal with its safe default | D | E2E / RTE |
| TSR-WDG-01 | WdgM performs alive, deadline and logical supervision of safety runnables and triggers reset on failure | D | WdgM |
| TSR-MEM-01 | Memory driver performs ECC/CRC check on NVM blocks at startup and reports failure to DEM | B | MemIf / NvM |
| TSR-MPU-01 | Safety-related and QM software separated via MPU so QM code cannot write to ASIL memory regions (FFI) | D | OS / MPU config |
| TSR-CLK-01 | Clock monitor detects system clock deviation beyond ±10% and triggers safe state | C | MCAL MCU |
| TSR-DIAG-01 | RAM/Flash start-up self-test (e.g. SMU/MTU MBIST on AURIX) before enabling safety functions | C | Safety library (SafeTlib) |

> Interview note: this is an illustrative set. In practice a TSR inherits the ASIL of the safety goal it implements (here ASIL C) unless the requirement is decomposed, so TSRs rated ASIL D under an ASIL C goal would need justification. Also, `E2E_P01STATUS_*` are the Profile 1 specific status values; `E2E_P_*` (§11.5) are the generic ones.

### Typical attributes of each safety requirement
- **ASIL** (A/B/C/D or QM)
- **Safe state** (what the system does on failure)
- **FTTI / reaction time** (timing constraint)
- **Diagnostic coverage** (e.g. 90% / 99%)
- **Verification method** (review, unit test, fault injection, HIL)
- **Traceability** (up to the safety goal, down to design and test cases)

### Typical MCAL safety mechanisms (recap)
Plausibility check (ADC), timeout detection, CRC (SPI), E2E (CAN), alive/deadline/logical supervision (WdgM), ECC/CRC (NvM), MPU, clock monitor, start-up self-test.

### Related work products
HSI (Hardware-Software Interface), FMEA/DFA, safety case, tool qualification (Part 8), and the vendor **Safety Manual** (assumptions of use and measures the integrator must implement).

---

## 15. Infineon AURIX (TC2xx / TC3xx) — Equivalent Safety Blocks

Your platform counterpart to the NXP MPC575x section (§11). Names differ by vendor; confirm in the device Safety Manual. SMU details and startup flow: see §18.

| Function | NXP MPC57xx | Infineon AURIX |
|---|---|---|
| Fault collection / reaction | FCCU | **SMU** (Safety Management Unit) |
| Memory self-test | STCU2 + MBIST | **MTU** (Memory Test Unit) MBIST, startup/online tests |
| Logic self-test | LBIST via STCU2 | LBIST (device dependent) |
| CPU checking | Lockstep e200z | Lockstep TriCore (checker cores) |
| Memory protection | MPU / SMPU | Memory protection (CPU MPU, bus-level protection) |
| ECC logging | MEMU | SMU alarms from ECC events |
| Safety software | Vendor test libraries | **SafeTlib** (self-test library), **SafeTpack** safety manager (Hitex) for TC3xx |

---

## 16. How to Frame MCAL Experience for FuSa Roles

If you implemented timeout detection, DEM/DET error reporting, E2E integration or watchdog integration on ADC, SPI, CAN or DMA, describe them **as safety mechanisms and state the ASIL level** — that is the language FuSa job descriptions use.

Example phrasing:
> "Implemented ADC plausibility checks and conversion-timeout detection (ASIL C/B) with DEM reporting, integrated E2E Profile 1 on safety CAN signals with safe-default substitution after consecutive failures, and configured WdgM alive/deadline/logical supervision, per the MCAL Safety Manual on AURIX TC2xx."

---

## 17. Resources

*(Links as supplied; I haven't verified they still resolve — AUTOSAR/Infineon sites reorganize often.)*

**AUTOSAR specifications (official, free)**
- E2E requirements (R20-11): https://www.autosar.org/fileadmin/standards/R20-11/FO/AUTOSAR_RS_E2E.pdf
- E2E requirements (R19-11): https://www.autosar.org/fileadmin/standards/R19-11/FO/AUTOSAR_RS_E2E.pdf
- E2E communication protection SRS (up to ASIL D): https://www.autosar.org/fileadmin/standards/R4.2.2/CP/AUTOSAR_SRS_E2E.pdf
- Watchdog Manager SWS: R23-11 https://www.autosar.org/fileadmin/standards/R23-11/CP/AUTOSAR_CP_SWS_WatchdogManager.pdf · R21-11 https://www.autosar.org/fileadmin/standards/R21-11/CP/AUTOSAR_SWS_WatchdogManager.pdf · R20-11 https://www.autosar.org/fileadmin/standards/R20-11/CP/AUTOSAR_SWS_WatchdogManager.pdf · R19-11 https://www.autosar.org/fileadmin/standards/R19-11/CP/AUTOSAR_SWS_WatchdogManager.pdf · R4.3.1 https://www.autosar.org/fileadmin/standards/R4.3.1/CP/AUTOSAR_SWS_WatchdogManager.pdf
- Mode Management SRS (includes WdgM requirements, R4.2.2): https://www.autosar.org/fileadmin/standards/R4.2.2/CP/AUTOSAR_SRS_ModeManagement.pdf
- *Still to find by module name on autosar.org:* Os (protection) and Dem/Det SWS.

**ISO 26262 (paid)**
- ISO 26262-6:2018 (software level; sample available): https://www.iso.org/standard/68388.html

**Infineon AURIX safety**
- PRO-SIL / ISO 26262 safety products (safety manuals, SafeTlib/SafeTpack briefs after registration): https://infineon.com/cms/en/product/microcontroller/microcontroller-safety-products-pro-sil-iso26262
- AURIX Safety Software (SafeTlib, evaluation license request): https://infineon.com/cms/en/tools/aurix-embedded-sw/Safety/infineon
- AURIX TC3xx functional safety application note (intro): https://documentation.infineon.com/aurixtc3xx/docs/owq1745576218449
- Hitex SafeTpack (TC3xx): https://www.hitex.com/focus/key-products/safetpack-safety-manager
- Hitex PRO-SIL SafeTlib (TC2xx): https://www.hitex.com/products/software-components/selftest-libraries/pro-sil-safetlib

**Webinar**
- Siemens, "Methodologies for obtaining Functional Safety using AUTOSAR" (ISO 26262:2011 vs 2018, FFI, E2E): https://webinars.sw.siemens.com/de-DE/ee-systems-functional-safety/

**Articles and papers**
- Introduction to Functional Safety (DEV Community, beginner): https://dev.to/rajeshm1/introduction-to-functional-safety-3hg2
- Evolution of functional safety & security in AUTOSAR (Schmerler, 2012): https://dl.gi.de/handle/20.500.12116/17562

---

## 18. AURIX Startup, SMU, OS Protection and Watchdog — Interview Q&A

*Written for AURIX TC2xx/TC3xx + AUTOSAR. Register, state and alarm names vary by device — confirm in the User Manual and Safety Manual.*

### 18.1 SMU driver initialization
SMU (Safety Management Unit) collects alarms from hardware safety mechanisms and drives the reaction. Typical `Smu_Init(config)`:
1. Check state: after reset the SMU is in **START**, where configuration is allowed.
2. **Unlock** config registers (key sequence: config lock / peripheral lock).
3. **Configure each alarm group**: reaction = none / interrupt / NMI / reset (system or application), and whether it activates the **FSP**.
4. Configure the **Fault Signaling Protocol** (error pin mode, e.g. bi-stable, dual-rail, time-switching) and recovery timers.
5. Log, then clear stale alarm status from the previous run.
6. **Lock** the configuration against accidental change.
7. Issue the **RUN** command (START → RUN).
Do it early, before safety functions are enabled, usually after MBIST / startup self-test.

### 18.2 Startup and NVM
**How do you initialize startup?** Reset → SSW/boot firmware → startup code (CRT0) → `main`:
1. Set stack pointers, CSA (context save areas), small-data base registers.
2. Init caches and **RAM ECC** (write RAM once so ECC bits are valid).
3. Copy `.data` flash → RAM, zero `.bss`.
4. Configure PLL/clocks and watchdogs (ENDINIT-protected).
5. Startup self-tests (LBIST/MBIST, SafeTlib), then **SMU init**.
6. `Mcu_Init`, `Port_Init`, drivers, `EcuM_Init` → start OS.

**Is NVM initialized at startup? When?** Yes, after drivers, typically in EcuM startup phase two: `Fls_Init` (and `Fee_Init`/`Eep_Init`) → `NvM_Init()` → `NvM_ReadAll()` (triggered by BswM/EcuM; restores RAM mirrors, checks block CRC) → on CRC/ECC failure load ROM defaults and report to DEM. Safety functions must not use NvM data before `ReadAll` completes.

### 18.3 Memory partitioning and linker sections
**Memory partitioning:** splitting memory into regions with defined access rights per OS-Application / task / core, enforced by the MPU; the linker places each partition's code, data and stack in its own region (spatial FFI).

| Section | Content | Startup handling |
|---|---|---|
| `.text` | Code | Executes from flash |
| `.rodata` | `const` data, strings | Stays in flash |
| `.data` | Initialized globals | Copied flash → RAM |
| `.bss` | Zero-initialized globals | Zeroed in RAM (also initializes ECC) |
| `.sdata` / `.sbss` | Small data via base register (TriCore) | Like `.data` / `.bss` |
| `.stack` / `.heap` | Stacks, heap (avoid heap in safety code) | Initialized or guarded |
| `.csa` | Context save areas (TriCore) | Linked list built at startup |
| `.noinit` | Survives reset (e.g. fault log) | Not cleared |

### 18.4 OS protection
AUTOSAR OS (SC3/SC4) protection mechanisms: **memory protection** (illegal data/code access), **timing protection** (exceeded budgets/arrival rates), **service protection** (invalid OS calls), **privilege separation** (trusted vs non-trusted).

| | Trusted OS-Application | Non-trusted OS-Application |
|---|---|---|
| CPU mode | Privileged (supervisor) | User mode |
| Memory | Everything allowed by config | Own MPU regions only |
| Service protection | Limited | Full |
| Use | Safety / BSW code | QM / lower-trust code |

A non-trusted app can call **trusted functions** (controlled entry points into privileged code). "Trusted" means privileged, not "proven correct".

**Protection hook:** `ProtectionHook(StatusType)` is called on a protection violation (`E_OS_PROTECTION_MEMORY / _TIME / _ARRIVAL / _LOCKED / _EXCEPTION`). Return value selects the reaction: ignore (where allowed), terminate task/ISR, terminate OS-Application, terminate and restart OS-Application, or shut down the OS.
**Error hook:** `ErrorHook(StatusType)` is called when an OS *service* returns an error (e.g. `E_OS_LIMIT`, `E_OS_ID`) — for service errors and logging; protection hook is for protection violations. Per-application `ErrorHook_<App>` also exists.
**Timing violation:** breach of timing protection — execution budget exceeded, inter-arrival time violated (activated too often), or lock time exceeded (resource/interrupt lock held too long) → protection hook. Different from a WdgM deadline miss, which is caught by supervision.
**Deadlock:** tasks wait on each other forever (A holds R1 wants R2; B holds R2 wants R1). Single core: OSEK/AUTOSAR resources use the **priority ceiling protocol**, which prevents it. Multicore spinlocks can deadlock. Prevention: lock ordering, short bounded lock times, no blocking calls while holding a lock. Detection: lock-time protection, WdgM alive/deadline.
**Memory violation:** access outside permitted range/permission (write to code or `const`, another partition, stack overflow) → MPU trap → `E_OS_PROTECTION_MEMORY` → protection hook.
**Why memory protection, and how to detect violations?** So a bug in QM/low-ASIL code can't corrupt safety data (spatial FFI). Detection: MPU trap → trap handler/ProtectionHook; stack guards/canaries; ECC + SMU alarms for HW corruption; CRC on critical data for silent corruption.

### 18.5 SMU Core vs Standby, and state transitions
- **SMU Core:** main SMU in the core power domain; monitors alarms from ECC, lockstep, clock/voltage monitors, MBIST, buses etc.; configures reactions (interrupt, NMI, reset); drives the **FSP error pin** to tell external hardware the MCU is faulty.
- **SMU Standby:** (TC3xx) separate SMU in the standby domain; keeps monitoring standby-domain alarms (standby supply, standby controller) while the core domain is off/low-power, and can signal faults or wake-up. Confirm scope in the device manual.

| Transition | Trigger |
|---|---|
| **Start → Run** | After reset SMU is in START; software unlocks, configures, locks, issues RUN |
| **Run → Fault** | Alarm configured to activate FSP occurs (or software trigger); error pin signals fault, configured reaction runs (interrupt / NMI / reset) |
| **Fault → Run** | Cause handled, alarm status cleared, software issues release-FSP; if an alarm is still active the SMU stays in FAULT; some alarms are configured to reset instead |

**Handler flow:** alarm → read alarm group status → identify source → store to DEM → take reaction → clear alarm → release FSP.

### 18.6 Fail-safe, limp-home, graceful shutdown
- **Fail-safe:** on a fault the system goes to a safe state (torque off, outputs de-energized) even if functionality is lost. **Fail-operational** keeps running (steering/braking redundancy); **fail-silent** just stops sending.
- **Limp-home:** degraded operation with reduced functionality (limited torque/speed, fixed gear) so the driver can reach a workshop; sits between full operation and fail-safe shutdown.
- **Graceful shutdown:** controlled move to the safe state within the FTTI: drive outputs safe, store fault data (`NvM_WriteAll` / DEM), notify other ECUs, then `EcuM_GoDown` / `ShutdownOS`. Differs from an abrupt reset where nothing is saved.

### 18.7 Watchdog
- **Functionality:** detects a hung CPU or lost program flow; software must service it within a set time, else it resets or raises an alarm. AURIX: per-core watchdogs + **Safety Watchdog** (SCU). AUTOSAR: **WdgM** (supervision) → **WdgIf** → **Wdg** driver → hardware.
- **Window watchdog:** refresh must fall *inside* a time window; too early or too late is a failure — catches a runaway loop refreshing too fast, which a plain timeout watchdog misses.
- **Servicing:** AURIX access is **password-protected** (password access, then modify access, with ENDINIT protection). In AUTOSAR a periodic `WdgM_MainFunction` checks all supervised entities and only then calls `Wdg_SetTriggerCondition`. Never refresh blindly from idle task or ISR.

### 18.8 Fault storage and fault classification
**How do you store a fault?** DEM: `Dem_SetEventStatus(FAILED)` records event, DTC and freeze frame, persisted via NvM. Also: SMU alarm status registers (read in the handler); a `.noinit` RAM log for faults that trigger immediate reset. DET is development-only, not for production storage.

| | Hardware fault | Software fault |
|---|---|---|
| Detected by | SMU alarms: ECC, lockstep mismatch, clock/voltage monitor, MBIST fail, bus error | E2E, plausibility, WdgM failure, assertion, OS protection violation |
| Nature | Random: transient, intermittent or permanent | Systematic: reproducible |

Gray cases (e.g. a memory violation) can be either; use alarm source, recurrence, ECC error counts and fault pattern to decide.

---

## 19. One-Minute Answer Templates

**ISO 26262 summary**
"ISO 26262 is the automotive functional safety standard covering the full lifecycle of E/E systems. Hazards are analysed in HARA and classified into ASIL A–D by severity, exposure and controllability, which scales development and verification rigor. For hardware we show coverage through SPFM, LFM and PMHF; for software we apply MISRA C, traceability, ASIL-scaled testing and freedom-from-interference measures."

**MPC575x safety mechanisms**
"At startup STCU2 runs LBIST and MBIST to uncover latent faults and reports to the FCCU. At runtime memories are protected by SECDED ECC with MEMU logging, cores run in lockstep, clocks and voltages are monitored, and data between components is protected with CRC, counters and Data ID via AUTOSAR E2E. The FCCU drives the configured reaction: interrupt, reset or safe-state signalling."

**AUTOSAR layers**
"AUTOSAR doesn't hard-assign ASIL to layers. Safety MCAL provides drivers and tests, the ECU abstraction has IoHwAb for plausibility, the service layer has safety OS, WdgM and E2E, and RTE enforces partitioning. COM stays QM and carries ASIL data via E2E under the black-channel principle. Mixed-ASIL SWCs are separated by OS-Applications and MPU."

---

## 20. Quick-Revision Checklist
- [ ] ASIL = S × E × C; QM, A–D; decomposition + DFA
- [ ] SPFM/LFM/PMHF targets; DC 60/90/99%
- [ ] FTTI, safe state, latent vs single-point vs multiple-point
- [ ] SW lifecycle SSR → arch → unit → tests; bidirectional traceability
- [ ] Coverage: statement / branch / MC/DC by ASIL (verify against standard)
- [ ] FFI: spatial, temporal, information exchange (Annex D)
- [ ] WdgM: alive, deadline, logical; WDT refresh gated on task liveness
- [ ] E2E = CRC + counter + Data ID + timeout; profiles; black channel
- [ ] STCU2 → LBIST + MBIST → FCCU; ECC SECDED + MEMU; SRAM init + scrubbing
- [ ] Layer-wise ASIL mapping; COM = QM
- [ ] Tool qualification TI/TD/TCL; SEooC + Safety Manual
- [ ] MCAL examples ready (ADC/SPI/CAN checks, register read-back), phrased as safety mechanisms with ASIL
- [ ] Every mechanism: ASIL, safe state, reaction time within FTTI, verification method
- [ ] SG → FSR → TSR example ready (§14); AURIX equivalents SMU / MTU / SafeTlib (§15)
- [ ] Exposure scale E1–E4, ASIL lookup (sum shortcut), HARA vs TARA (§2)
- [ ] SMU init sequence and START → RUN → FAULT → RUN (§18)
- [ ] Startup order, NvM_ReadAll timing, linker sections (§18)
- [ ] OS protection: trusted vs non-trusted, protection hook vs error hook, timing/memory violation (§18)
- [ ] Window watchdog, WdgM servicing, fail-safe vs limp-home vs graceful shutdown (§18)
