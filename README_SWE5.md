# SWE.5 — Software Integration and Integration Test
### Automotive SPICE (ASPICE) Process Reference

---

## 1. What SWE.5 Is

SWE.5 is one of the six Software Engineering processes in the Automotive SPICE Process Reference Model (SWE.1–SWE.6). It sits between **SWE.4 (Software Unit Verification)** and **SWE.6 (Software Qualification Test)** in the V-model.

**Purpose:** Take individually verified software units, integrate them step by step into software items and ultimately into the fully integrated software, and verify at each step that the integration is consistent with the software architectural design (SWE.2) — both structurally (static) and behaviorally (dynamic), including interfaces.

**Position in the V-model:**
```
SWE.1 Requirements → SWE.2 Architecture → SWE.3 Detailed Design/Unit Impl
                                              ↓
                                        SWE.4 Unit Verification
                                              ↓
                                   >>> SWE.5 Integration & Integration Test <<<
                                              ↓
                                        SWE.6 Qualification Test
```

---

## 2. Why It Matters (Practical View)

Unit testing (SWE.4) proves each module works in isolation. SWE.5 proves the modules work **together** — that interfaces are correctly implemented, data flows as designed, and no integration-level defects (timing, memory conflicts, wrong call sequence, buffer/interface mismatches) exist before the software goes to full qualification testing (SWE.6).

In an AUTOSAR MCAL context, this is where you'd verify, for example, that an ADC driver correctly hands off converted data to the calling application layer via the configured interface, that DMA-based transfers complete and trigger the right notification callback, or that SPI job/channel sequencing behaves as the architecture specifies under real hardware timing — not just in a unit-level mock.

---

## 3. Base Practices (BP1–BP9)

| BP | Name | What It Covers |
|----|------|-----------------|
| **BP1** | Develop software integration strategy | Define the order/levels in which units → items → full software are integrated (e.g., bottom-up, incremental, critical-interface-first). Aligned with the architecture and release plan. |
| **BP2** | Develop integration test strategy (incl. regression) | Define how integration will be tested, and how re-testing will be handled when a changed item is re-integrated. |
| **BP3** | Develop integration test specification | Write test cases per integrated item, sufficient to prove interfaces and behavior match the architectural design. |
| **BP4** | Integrate software units and items | Actually perform the integration — units → items → fully integrated software — per the strategy. |
| **BP5** | Select test cases | Pick test cases from the specification with coverage appropriate to the strategy and release plan. |
| **BP6** | Perform integration test | Execute selected tests (often on target HW, via debug interfaces, or in SIL/HIL environments), and log results. |
| **BP7** | Establish bidirectional traceability | Link architecture elements ↔ test cases ↔ test results, both directions. |
| **BP8** | Ensure consistency | Confirm test cases actually and correctly cover the architecture elements they claim to (supported by traceability + review records). |
| **BP9** | Summarize and communicate results | Report integration test outcomes to all stakeholders (dev, safety, project management) so issues are visible and actionable. |

---

## 4. Key Outcomes (What "Done" Looks Like)

A project doing SWE.5 well can demonstrate:

1. An integration strategy consistent with the architecture and release plan.
2. A test strategy (including regression) for integration testing.
3. Integration test specifications that trace to architecture.
4. Software items actually integrated per the strategy.
5. Integration tests executed with adequate coverage.
6. Results recorded, and non-conformances routed to problem resolution (SUP.9).
7. Bidirectional traceability between architecture, test specs, and results.
8. Test results communicated to affected parties.

---

## 5. Related Processes

- **SWE.2** — Software Architectural Design (SWE.5 verifies compliance *against* this)
- **SWE.4** — Software Unit Verification (feeds verified units into SWE.5)
- **SWE.6** — Software Qualification Test (next step after integration is complete)
- **SUP.8** — Configuration Management (baseline control of integrated builds)
- **SUP.9** — Problem Resolution Management (handling integration test failures/non-conformances)

---

## 6. How This Maps to Your Experience

Useful framing for interviews, given your background in MCAL driver integration and validation at Continental/Tech Mahindra:

- **Integration strategy** → You integrated MCAL drivers (ADC, SPI) into the broader AUTOSAR BSW/application stack in a defined sequence, often peripheral-by-peripheral, validated on TRACE32/target hardware.
- **Integration testing** → Validating driver behavior post-integration using TRACE32 (JTAG), Logic Analyzer, and Oscilloscope — confirming real interface behavior, not just unit-level mocks.
- **Traceability** → Your DOORS-based requirement traceability work is directly BP7/BP8 — linking requirements/architecture to test evidence.
- **SW-E5 process compliance** (as referenced on your resume) → This is the internal/OEM-facing term for adherence to this exact ASPICE SWE.5 discipline: strategy, test spec, execution, traceability, and reporting, gated at project milestones.
- **Problem resolution** → Any defects found during integration testing routed through change/defect tracking (SUP.9 equivalent) before re-integration.

---

## 7. Likely Interview Questions

- *"Walk me through your integration testing approach for the ADC/SPI drivers."*
  → Strategy (order of integration) → test spec derivation from architecture → execution on target using TRACE32/Logic Analyzer → traceability to DOORS requirements → defect handling → summary reporting.

- *"How do you ensure your integration tests actually cover the architecture, not just the requirements?"*
  → Reference BP8: consistency is demonstrated through bidirectional traceability and review records tying test cases directly to architectural elements (interfaces, static/dynamic behavior), not only to functional requirements.

- *"What's the difference between unit testing and integration testing in your process?"*
  → Unit test (SWE.4) verifies a single module against its detailed design in isolation; integration test (SWE.5) verifies that multiple units/items work together correctly per the *architecture* — interfaces, data flow, timing, and interaction behavior on real or near-real hardware.
