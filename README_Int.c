

---



# CAT2 Reset (Controlled Reset)

```
Error / SMU trigger
    → OS calls ShutdownHook()     ← user code runs here (< 10ms budget)
        → flush NvM pending writes
        → set safe outputs (actuators OFF)
        → log DTC to NvM
    → Mcu_PerformReset()
    → MCU resets
```

> CAT2 is mandatory for ASIL B/C/D — abrupt reset (CAT1) not acceptable for safety systems

---

### NVIC — Nested Vector Interrupt Controller

| Register        | Bit Used   | What it does                                      |
|-----------------|------------|---------------------------------------------------|
| NVIC->ISER[0]   | Bit 28     | Enable USART2 interrupt in CPU                    |
```

