# ISO 26262 — Functional Safety (FuSa) Interview Notes
*Focus: embedded / AUTOSAR MCAL / NXP MPC575x (Power Architecture) — verify part-specific details against your derivative's Reference Manual and Safety Manual.*

---

## 1. What It Is

ISO 26262 is the functional safety standard for **road vehicle E/E systems**. It defines how to avoid or control **systematic failures** and **random hardware failures** that could cause harm, across the whole lifecycle: concept → development (system/HW/SW) → production → operation → decommissioning.

> **One-liner:** "ISO 26262 defines how to systematically manage the risk of failures in automotive E/E systems, using ASIL levels to scale rigor based on severity, exposure and controllability."

**Key vocabulary**
| Term | Meaning |
|---|---|
| Functional safety | Absence of unreasonable risk due to hazards from E/E malfunction |
| Hazard | Potential source of harm caused by malfunctioning behavior |
| Safety goal (SG) | Top-level safety requirement derived from HARA |
| FSR / TSR | Functional / Technical Safety Requirement (derived from SG) |
| Safe state | Operating mode without unreasonable risk (e.g. torque off, limp-home) |
| FTTI | Fault Tolerant Time Interval — time from fault to hazard if no reaction |
| Systematic fault | Deterministic cause (spec/design/process error) → fixed by process rigor |
| Random HW fault | Stochastic (bit flip, stuck-at, aging) → handled by diagnostics + metrics |
| Latent fault | Not detected, not perceived by driver — stays hidden until a 2nd fault |

---

## 2. ASIL — Automotive Safety Integrity Level

Levels: **QM → ASIL A → B → C → D** (D = most rigorous).

Determined in **HARA** (Hazard Analysis & Risk Assessment) from:

| Factor | Scale |
|---|---|
| Severity (S) | S0–S3 |
| Exposure (E) | E0–E4 |
| Controllability (C) | C0–C3 |

- Examples: brake-by-wire / steering loss → ASIL D; airbag unintended deployment → ASIL D; wiper failure → ASIL A/QM; infotainment → QM.
- **ASIL decomposition** (Part 9): split a requirement into redundant, *independent* elements, e.g. ASIL D → ASIL B(D) + ASIL B(D), or C(D)+A(D). Independence must be proven (no common cause / dependent failures).
- **ASIL is inherited** by all elements implementing the safety goal unless decomposed.
- Rule of thumb: ASIL ≠ SIL (IEC 61508). Different standards, different scales.

---

## 3. V-Model

```
Concept / HARA  ─────────────────────────────►  Vehicle validation
   System design  ────────────────────────►  System integration & test
      HW design / SW architecture  ───►  HW / SW integration & test
         SW unit design  ──────────►  Unit verification
                 Implementation
```
Each left-side artifact has a matching right-side verification, with **bidirectional traceability**.

---

## 4. Parts of ISO 26262 (2nd edition, 2018)

| Part | Topic | Why you care |
|---|---|---|
| 1 | Vocabulary | |
| 2 | Management of functional safety | Safety plan, safety case, confirmation measures |
| 3 | Concept phase | Item definition, HARA, safety goals |
| 4 | System-level development | Technical safety concept, HSI, integration |
| 5 | Hardware-level development | FMEDA, SPFM/LFM/PMHF metrics |
| **6** | **Software-level development** | **Your daily work** — architecture, unit design, verification |
| 7 | Production, operation, service, decommissioning | |
| 8 | Supporting processes | Config mgmt, change mgmt, tool qualification, SW component qualification |
| 9 | ASIL-oriented & safety-oriented analyses | Decomposition, DFA, FMEA, FTA |
| 10 | Guidelines | Explanatory |
| 11 | Semiconductors | Guidance for chips/IP (relevant to MCU vendors) |
| 12 | Motorcycles | |

---

## 5. Hardware Architectural Metrics (Part 5) — frequently asked

| Metric | Meaning |
|---|---|
| **SPFM** | Single-Point Fault Metric — robustness against single-point & residual faults |
| **LFM** | Latent Fault Metric — robustness against latent multiple-point faults |
| **PMHF** | Probabilistic Metric for random HW Failures (failure rate, in FIT) |

| ASIL | SPFM | LFM | PMHF |
|---|---|---|---|
| B | ≥ 90% | ≥ 60% | < 100 FIT |
| C | ≥ 97% | ≥ 80% | < 100 FIT |
| D | ≥ 99% | ≥ 90% | < 10 FIT |

*(ASIL A has no mandatory targets.)*  1 FIT = 1 failure per 10⁹ device-hours.

**Diagnostic Coverage (DC):** Low ≈ 60%, Medium ≈ 90%, High ≈ 99%.
**FMEDA** = FMEA + Diagnostic coverage + failure rates → yields the metrics above.

---

## 6. Software Development (Part 6) — what to say as an embedded engineer

- **Coding standard:** MISRA C (2012/2023). Deviations documented & justified.
- **Language subset / restrictions:** no dynamic memory, limited recursion, no unbounded loops, defensive programming, single entry/exit encouraged, no implicit type conversion.
- **Architecture principles:** hierarchical structure, restricted component size/interface size, high cohesion, low coupling, restricted use of interrupts, appropriate scheduling.
- **Architectural safety mechanisms:** range checks, plausibility checks, program-flow monitoring (watchdog – logical + temporal), data-flow monitoring, E2E protection, redundancy, graceful degradation.
- **Verification methods** (scaled by ASIL): requirements-based testing, interface testing, fault-injection testing, resource usage tests, back-to-back model/code testing, static analysis, code review/walkthrough, formal verification (higher ASIL).
- **Structural coverage:**
  | ASIL | Statement | Branch | MC/DC |
  |---|---|---|---|
  | A | ++ | + | + |
  | B | ++ | ++ | + |
  | C | ++ | ++ | ++ |
  | D | ++ | ++ | ++ |
  (++ highly recommended, + recommended)
- **Traceability:** SG → FSR → TSR → SW requirements → design → code → tests (DOORS / Polarion).

---

## 7. Freedom From Interference (FFI)

Mixed-ASIL software (e.g. QM + ASIL-B on one core) is allowed only with proof of no interference:

| Domain | Example mechanism |
|---|---|
| **Spatial** (memory) | MPU / memory protection, separate memory partitions, stack guards |
| **Temporal** (timing) | Watchdog, deadline/execution-time monitoring, OS timing protection, priority design |
| **Information exchange** | E2E protection, CRC, message counters, sequence checks, timeout |

In AUTOSAR: OS-Application + MPU + Timing Protection + Watchdog Manager + E2E library.

---

## 8. Tool Qualification (Part 8)

- **TI** (Tool Impact): can the tool introduce/fail to detect an error? (TI1 / TI2)
- **TD** (Tool error Detection): probability of detecting tool errors (TD1–TD3)
- **TCL** (Tool Confidence Level) = TCL1 (no qualification) … TCL3 (highest effort)
- Qualification methods: increased confidence from use, development per safety standard, evaluation of development process, validation of the tool.
- Examples: compiler (e.g. certified GHS/HighTec/Tasking), static analyzers, test tools (VectorCAST), configuration tools (EB Tresos, DaVinci).

---

## 9. SEooC — Safety Element out of Context

Developed **without a specific item** (e.g. MCAL, MCU, BSW stack). Supplier **assumes** a safety context (assumed ASIL, assumed safety goals, FTTI) and documents **Assumptions of Use**. Integrator must verify the actual system matches those assumptions and consult the **Safety Manual**.

---

## 10. NXP MPC575x — Safety Mechanisms (from your notes, expanded)

### 10.1 STCU2 — Self-Test Control Unit
- Hardware block that **orchestrates built-in self-tests** at startup (**offline BIST**) and sometimes in runtime (**online/periodic BIST**) depending on device.
- It does not test by itself — it **controls and sequences** the BIST engines and collects pass/fail results.
- Faults are reported to the **FCCU** (Fault Collection and Control Unit) → reaction (interrupt, reset, fault pin signalling).

**BIST types**
| BIST | Tests | Detects |
|---|---|---|
| **LBIST** (Logic BIST) | Digital logic via scan chains + pseudo-random patterns (PRPG) + signature (MISR) | Stuck-at & transition faults in logic → **latent fault detection** |
| **MBIST** (Memory BIST) | SRAM / cache / flash-buffer arrays using March-type algorithms | Memory cell, decoder, coupling faults |

> Interview point: LBIST/MBIST at power-up reveals **latent faults** that runtime mechanisms can't see, which improves **LFM**.

### 10.2 Memory fault models (what MBIST targets)
Your notes listed these — here's the terminology:

| Your note | Standard term |
|---|---|
| Single bit error | Single-bit upset / stuck-at fault (SAF) |
| Multi bit error | Multiple-cell fault |
| Read destructive fault | Read Destructive Fault (RDF) |
| Write destructive fault | Write Destructive Fault (WDF) |
| Data retention fault | Data Retention Fault (DRF) |
| "IO coupling" fault | **Coupling fault (CF)** — a cell's value is affected by neighboring cell transitions |
| (other) | Transition fault (TF), Address decoder fault (AF), Stuck-open fault |

> Note: these are **memory fault models** that MBIST algorithms (e.g. March C−) are designed to catch — not "10 test cases of STCU". Say it that way in an interview.

### 10.3 ECC — Error Correcting Code
- Typically **SECDED**: Single-Error **C**orrect, Double-Error **D**etect (e.g. 8 ECC bits per 64 data bits, Hamming-based).
- Single-bit error → corrected on the fly, may be counted/logged (via **MEMU** — Memory Error Management Unit — on MPC57xx).
- Double-bit error → detected, uncorrectable → raise fault to FCCU / exception (machine check) → safe state.
- Covers: flash, SRAM, caches, DMA TCDs, some peripheral RAMs.
- **ECC address coverage:** many devices also include the address in the ECC → detects *wrong-address* accesses.
- Firmware responsibilities: **initialize SRAM** (so ECC bits are valid) before first read; periodic **scrubbing** to avoid accumulating soft errors; ECC error-injection tests.

### 10.4 CRC
- Used for **data integrity** (not security): Flash/NVM integrity (ROM check at boot), configuration verification, communication payload.
- Mechanisms: HW CRC unit (CRC module / DMA-driven) vs SW CRC (table-based).
- Polynomials: CRC-8 SAE-J1850 (E2E P1 uses 0x1D), CRC-16 CCITT, CRC-32 / CRC-32P4 (E2E P4).
- Know the limit: CRC detects burst errors well, **not** masquerade/repetition/sequence errors → combine with **counter + Data ID**.

### 10.5 E2E (End-to-End) Protection — AUTOSAR
Protects data exchanged between SW components / ECUs against communication & memory faults on the path (RTE, COM, CAN, FlexRay, Ethernet, SPI…).

**Fault types addressed:** corruption, repetition, loss, insertion, incorrect sequence, wrong addressing (masquerading), delay, blocking.

**Mechanisms**
| Mechanism | Detects |
|---|---|
| **CRC** | Data corruption |
| **Alive / Sequence counter** | Repetition, loss, wrong sequence, stuck sender |
| **Data ID** | Masquerade / wrong addressing / insertion |
| **Timeout** (receiver) | Delay, loss, blocking |

**Profiles:** P01 (CRC8 + 4-bit counter + Data ID nibble), P02 (CRC8 + 4-bit counter + Data ID list), P04/P05/P06/P07 (bigger CRCs, 16/32-bit counters), P11/P22 (CAN-optimized), etc.

**Receiver-side status (`E2E_PCheckStatusType`)**
`E2E_P_OK`, `E2E_P_WRONGCRC`, `E2E_P_REPEATED`, `E2E_P_WRONGSEQUENCE`, `E2E_P_NONEWDATA`, `E2E_P_ERROR`, `E2E_P_OKSOMELOST`
→ state-machine (`E2E_SMCheck`) maps to VALID / INVALID / NODATA / INIT for application decision.

### 10.6 Other typical MPC57xx safety blocks (good to mention)
| Block | Role |
|---|---|
| **FCCU** | Collects HW fault signals, configurable reactions (IRQ, reset, FCCU_F pins), fault recovery |
| **MEMU** | Logs ECC errors from memories |
| **Lockstep (LSM / Delayed lockstep)** | Two e200z cores executing same instructions, comparator checks outputs (**CPU fault detection**) |
| **SWT** | Software Watchdog Timer |
| **CMU** | Clock Monitoring Unit (frequency out-of-range, loss of clock) |
| **PMC / voltage monitors (LVD/HVD)** | Supply monitoring |
| **MPU / SMPU** | Memory protection → FFI |
| **CRC unit, ADC self-test, Temp sensor** | Diagnostic helpers |
| **ECC on DMA/XBAR/peripheral bridges** | Data-path protection |

**Typical safe-start sequence:** Reset → BAM/boot → STCU2 runs LBIST + MBIST → check STCU2 status → FCCU init → clock/voltage monitor config → SRAM init → CRC check of flash → start OS / application.

---

## 11. AUTOSAR Safety-Related Modules

| Module | Safety role |
|---|---|
| **WdgM / WdgIf / Wdg driver** | Alive, deadline, logical supervision |
| **E2E Library / E2E Transformer** | Data protection |
| **OS** (SC3/SC4) | Memory protection, timing protection, trusted/non-trusted apps |
| **SafeTimer / SafeCom** (vendor) | Timing and comms safety |
| **Dem / Dcm** | Diagnostic event handling, DTC storage |
| **MCAL** | Safety-qualified drivers + safety manual; e.g. ADC, SPI, CAN with plausibility checks, DMA, RAM test (**RamTst**), Flash test (**FlsTst**), Core test (**CorTst**), **MCU self-test** |
| **Safety Extensions in MCAL** | Register readback / write-verify, lock mechanisms (e.g. protected registers), config CRC |

Mention **MCAL safety measures** from your experience: register read-back verification after write, ADC group redundancy / plausibility, SPI/CAN with E2E/CRC, timeout protections, DMA integrity checks.

---

## 12. Safety Analysis Techniques

| Technique | Type | Used for |
|---|---|---|
| **HARA** | Top-down | Hazards → ASIL → safety goals |
| **FTA** (Fault Tree Analysis) | Top-down, deductive | Root causes of a hazard, PMHF |
| **FMEA** | Bottom-up, inductive | Failure modes of components |
| **FMEDA** | Bottom-up + DC | Quantitative HW metrics |
| **DFA** (Dependent Failure Analysis) | Cascading / common cause failures | Proves independence for decomposition / FFI |
| **Safety Case** | Argument | Evidence that safety goals are met |

**Dependent failures:** *Common cause failures* (same root: power, clock, temperature) and *cascading failures* (one fault propagates).

---

## 13. Safety Mechanisms Cheat Sheet (by fault type)

| Fault source | Mechanism |
|---|---|
| CPU | Lockstep, SW core test, LBIST |
| Flash | ECC, CRC, FlsTst, MBIST (for buffers) |
| RAM | ECC, MBIST, RamTst (March), parity |
| Registers | Read-back, redundant config, write-protect/lock |
| Clock | CMU, dual clock source, watchdog on independent clock |
| Power | Voltage monitors, brown-out reset |
| Program flow | WdgM (alive, deadline, logical), control-flow signatures |
| Communication | E2E (CRC + counter + Data ID), timeout, redundant channels |
| Sensor input | Plausibility, redundant sensors, range checks, ADC self-test |
| Output / actuator | Feedback monitoring, redundant paths, safe-state drive |
| Software crash | Watchdog + reset, MPU exception handler |

---

## 14. Interview Q&A (practice)

**Q1. What is ISO 26262 and why is it needed?**
Standard for functional safety of automotive E/E systems; ensures systematic process + technical measures so failures don't cause unreasonable risk to people.

**Q2. How is ASIL determined?**
HARA: Severity × Exposure × Controllability → QM/A/B/C/D, assigned per hazard → safety goal inherits ASIL.

**Q3. Difference between systematic and random hardware faults?**
Systematic — deterministic cause in specification/design/process, mitigated by process rigor (reviews, coverage, traceability). Random HW — stochastic, handled by diagnostics and quantified with SPFM/LFM/PMHF.

**Q4. What is FTTI and why does it matter?**
Time between fault occurrence and hazardous event if unmitigated. Detection + reaction time of any safety mechanism must be shorter than FTTI.

**Q5. What are SPFM, LFM, PMHF?**
(See section 5.) SPFM = single-point/residual coverage, LFM = latent coverage, PMHF = absolute failure rate.

**Q6. What is ASIL decomposition?**
Splitting a high-ASIL requirement into redundant independent elements with lower ASIL each (e.g. D → B(D)+B(D)), contingent on proven independence (DFA).

**Q7. What is Freedom From Interference?**
Guarantee that a lower-ASIL/QM element can't corrupt a higher-ASIL one — spatial (MPU), temporal (timing protection/watchdog), information exchange (E2E).

**Q8. What does STCU do on the MPC57xx?**
Controls and sequences BIST (LBIST for logic, MBIST for memories) at startup, reports pass/fail to the FCCU/system. Detects latent faults before the application starts.

**Q9. LBIST vs MBIST?**
LBIST: logic via scan + PRPG + MISR signature. MBIST: memory arrays with March algorithms for cell, decoder, coupling, retention faults.

**Q10. How does ECC work, and what happens on single vs double errors?**
SECDED Hamming-type code: single-bit corrected transparently and logged; double-bit detected and reported as a fault (FCCU/exception) → safe state.

**Q11. Why can't CRC alone protect communication? What does E2E add?**
CRC catches corruption only. Counter catches repetition/loss/sequence; Data ID catches masquerade/insertion; timeout catches delay/loss. Together they cover the E2E fault model.

**Q12. What is a latent fault and how do you cover it?**
A fault that is neither detected nor perceived — dangerous when combined with a second fault. Covered by periodic/startup tests (BIST, RamTst, FlsTst, ADC self-test), improving LFM.

**Q13. What is SEooC / safety manual?**
SEooC = element developed without a specific item based on assumed context. Safety manual documents assumptions of use, safety mechanisms, and integrator obligations.

**Q14. How does ISO 26262 affect your MCAL work?**
MISRA C compliance, traceable requirements, configuration review (EB Tresos), register-level protections, ASIL-scaled test coverage (MC/DC for ASIL D), fault-injection and robustness tests, tool qualification, following the MCAL safety manual.

**Q15. What is the safe state? Give an example.**
Defined system condition with no unreasonable risk — e.g. disable torque request / transition to limp-home, disable actuator output, controlled stop.

**Q16. What are confirmation measures?**
Confirmation review, functional safety audit, functional safety assessment — independence required increases with ASIL.

**Q17. ASIL B vs ASIL D software testing — what changes?**
More rigorous methods are "highly recommended": MC/DC coverage, fault injection, formal methods, stronger independence of reviewers/testers, tighter metrics.

**Q18. How do you protect an ADC reading in a safety context?**
Range + plausibility checks, redundant channel/sensor, reference-voltage self-test channel, conversion timeout, DMA result integrity (ECC/CRC), diagnostics via DEM on failure.

**Q19. How do you detect a stuck CAN signal at application level?**
E2E alive-counter (stuck counter → `REPEATED`), timeout monitoring (`NONEWDATA`), CRC check, plus signal-level plausibility.

**Q20. Difference between ISO 26262 and ASPICE?**
ASPICE = process maturity model (quality). ISO 26262 = safety lifecycle & technical safety. Complementary: SWE.5 integration test work contributes to the Part 6 evidence.

---

## 15. One-Minute Answer Templates

**ISO 26262 summary**
"ISO 26262 is the automotive functional safety standard covering the full lifecycle of E/E systems. Hazards are analysed in HARA and classified into ASIL A–D by severity, exposure and controllability, which scales the rigor of development and verification. For hardware, we show diagnostic coverage through SPFM, LFM and PMHF; for software, we apply MISRA C, traceability, ASIL-scaled testing and freedom-from-interference measures."

**MPC575x safety mechanisms**
"On the MPC575x, at startup the STCU2 runs LBIST and MBIST to uncover latent faults in logic and memories and reports to the FCCU. At runtime, memories are protected by SECDED ECC with MEMU logging, cores run in lockstep, clocks and voltages are monitored, and data between software components is protected with CRC, counters and Data ID via AUTOSAR E2E. Faults are collected in the FCCU, which drives the configured reaction — interrupt, reset or safe-state signalling."

---

## 16. Quick-Revision Checklist

- [ ] ASIL = S × E × C, A–D, QM
- [ ] SPFM / LFM / PMHF targets (B 90/60, C 97/80, D 99/90; PMHF <100/<100/<10 FIT)
- [ ] DC levels 60 / 90 / 99 %
- [ ] FTTI, safe state, latent vs single-point vs multiple-point faults
- [ ] ASIL decomposition + DFA
- [ ] FFI: spatial, temporal, information exchange
- [ ] STCU2 → LBIST + MBIST → FCCU
- [ ] ECC = SECDED; MEMU logging; SRAM init + scrubbing
- [ ] E2E = CRC + counter + Data ID + timeout; profiles P01/P02/P04/P05/P06/P07
- [ ] Tool qualification TI/TD/TCL
- [ ] SEooC + safety manual
- [ ] MC/DC for ASIL C/D
- [ ] Your MCAL examples ready (ADC/SPI/CAN safety checks, register read-back)
