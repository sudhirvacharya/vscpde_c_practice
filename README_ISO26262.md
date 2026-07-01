# ISO 26262 — Automotive Functional Safety Notes

## What It Is
ISO 26262 is the international standard for **functional safety in road vehicle
electrical/electronic (E/E) systems**. It defines processes to prevent or control
failures (systematic and random hardware) that could cause harm to people —
covering the full lifecycle: concept → hardware/software development →
production → operation → decommissioning.

**One-liner for interviews:**
> "ISO 26262 is the standard that defines how to systematically manage the risk
> of failures in automotive E/E systems, using ASIL levels to scale rigor based
> on how severe and likely a hazard is, and how much control the driver has
> over it."

---

## ASIL — Automotive Safety Integrity Level
Core concept, almost always asked about directly.

Levels: **QM** (Quality Managed, no special safety req) → **ASIL A** → **ASIL B**
→ **ASIL C** → **ASIL D** (highest rigor).

Derived from hazard analysis using three factors:

| Factor | Meaning | Scale |
|---|---|---|
| **Severity (S)** | How bad if it happens | S0–S3 |
| **Exposure (E)** | How often the situation occurs | E0–E4 |
| **Controllability (C)** | Can the driver do something about it | C0–C3 |

**Examples:**
- Brake-by-wire failure → high severity, frequent exposure, low controllability
  → likely **ASIL D**
- Dashboard cosmetic light glitch → **QM** or **ASIL A**

---

## V-Model Development
ISO 26262 is structured around the V-model:

```
Requirements flow DOWN:
Concept → System Design → HW/SW Design → Implementation

Verification flows back UP:
Unit Test ↔ Implementation
Integration Test ↔ Design
System Test ↔ System Design
Validation ↔ Concept
```

Each design level has a corresponding test/verification level that traces
back to it.

---

## Part Structure (high-level awareness)
Don't need to memorize all 12 parts — know the relevant ones:

| Part | Covers |
|---|---|
| Part 3 | Concept phase (hazard analysis, risk assessment) |
| Part 4 | System-level development |
| Part 5 | Hardware-level development |
| **Part 6** | **Software-level development** ← most relevant to firmware/embedded work |
| Part 8 | Supporting processes (config management, tool qualification, etc.) |

---

## Why It Matters for Embedded/AUTOSAR Work
Connective tissue interviewers want to hear — ties the standard to practical
day-to-day dev work:

- **MISRA C** coding guidelines → avoid undefined behavior
- **Requirements traceability** between requirements and code
- **Unit/integration test coverage targets** scaled to ASIL level
- **Qualified/certified tools** required in the toolchain
- **AUTOSAR** itself was designed with ISO 26262 compliance in mind — this is
  part of why MCAL drivers have such rigid configuration and diagnostic
  requirements (e.g. ADC/SPI driver config in EB Tresos)

---

## Interview Answer Template
> "ISO 26262 is the automotive functional safety standard. It covers the
> entire lifecycle of an E/E system — from concept and hazard analysis through
> hardware/software development, production, and decommissioning — with the
> goal of preventing or controlling systematic and random hardware failures
> that could cause harm. Risk is classified using ASIL levels (A–D, plus QM),
> derived from severity, exposure, and controllability. In practice, for
> someone working in embedded/AUTOSAR, this shows up in things like MISRA C
> compliance, requirements traceability, ASIL-scaled test coverage, and using
> qualified tools in the toolchain."
