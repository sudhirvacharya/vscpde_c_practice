# baremetal ARM Cortex-M0+ MCU (STM32 Nucleo STM32G070RB)  Boot Sequence

## 1. Power ON / Reset

When STM32 MCU is powered ON or reset occurs:

- Cortex-M0+ core enters reset state.
- CPU registers are initialized to reset values.
- NVIC, peripherals, and system registers are reset.
- CPU starts boot sequence.

---

# 2. Identify Boot Mode

STM32 checks boot configuration:

- BOOT0 pin
- Option Bytes

Possible boot sources:

```
1. Main Flash Memory
2. System Memory (ST Bootloader)
3. SRAM (if supported/configured)
```

For normal application execution:

```
Boot Mode = Main Flash
```

Flash starts at:

```
0x08000000
```

---

# 3. Vector Table Location

Cortex-M vector table is located at:

```
0x00000000
```

After Flash boot, this address is aliased to:

```
0x08000000 (Flash)
```

Vector table format:

```
Flash Memory

Address          Content
----------------------------------

0x08000000  ->  Initial MSP value
0x08000004  ->  Reset_Handler address
0x08000008  ->  NMI_Handler address
0x0800000C  ->  HardFault_Handler address

...
```

---

# 4. Fetch Initial Stack Pointer (MSP)

CPU reads first vector table entry:

```
Address:

0x08000000
```

Value stored:

```
0x20009000
```

CPU loads:

```
MSP = 0x20009000
```

Meaning:

- MSP register receives SRAM end address.
- Stack starts from the top of SRAM.
- Stack grows downward.

Memory:

```
SRAM

0x20009000
+----------------+
|                |
| Stack          |
|      ↓         |
|                |
+----------------+
0x20000000
SRAM Start
```

Important:

```
0x20009000 = Stack start address
```

It is NOT the address of SP register.

---

# 5. Fetch Reset Handler Address

CPU reads second vector table entry:

```
Address:

0x08000004
```

Value stored:

```
0x080001E5
```

Bit 0 indicates Thumb mode.

Actual Reset_Handler address:

```
0x080001E4
```

CPU loads:

```
PC = 0x080001E4
```

Execution jumps to:

```
Reset_Handler()
```

---

# 6. Flash Memory Layout Example (STM32G070RB)

```
FLASH (0x08000000)

0x08000000
+-----------------------+
| Initial SP            |
| 0x20009000            |
+-----------------------+
| Reset_Handler Address |
| 0x080001E5            |
+-----------------------+
| NMI Handler Address   |
+-----------------------+
| HardFault Handler     |
+-----------------------+

        ...

0x08000104
+-----------------------+
| SysTick_Initialize()  |
+-----------------------+

0x0800012C
+-----------------------+
| main()                |
+-----------------------+

0x080001E4
+-----------------------+
| Reset_Handler()       |
+-----------------------+
```

---

# 7. Reset_Handler Execution

Startup assembly code:

```assembly
Reset_Handler:

    ldr   r0, =_estack
    mov   sp, r0
```

Linker defines:

```
_estack = 0x20009000
```

Execution:

```
r0 = 0x20009000

SP = r0

SP = 0x20009000
```

The stack pointer is initialized again.

---

# 8. Initialize Clock System

Reset_Handler calls:

```
SystemInit()
```

Purpose:

- Configure clock source
- Configure PLL
- Setup CPU clock frequency

Example:

```
HSI -> PLL -> SYSCLK
```

---

# 9. Copy .data Section Flash --> SRAM

Global/static variables with initial values:

Example:

```c
int counter = 10;
```

Stored in Flash initially:

```
FLASH
0x080xxxxx
     |
     |
     | Copy during startup
     v

SRAM
0x200xxxxx
```

After copying:

```
SRAM

.data section
initialized variables
```

---

# 10. Clear .bss Section

Global/static variables without initialization:

Example:

```c
int flag;
```

Startup code clears:

```
.bss = 0
```

Example:

```
SRAM

+----------------+
| .data          |
+----------------+
| .bss = 0       |
+----------------+
| Heap           |
+----------------+
| Stack          |
|       ↓        |
+----------------+

0x20009000
```

---

# 11. Initialize C Library

Startup executes:

```
__libc_init_array()
```

Purpose:

- Initialize C runtime
- Initialize static constructors (if used)

---

# 12. Enter Application

Finally:

```
Reset_Handler()
        |
        |
        v
SystemInit()
        |
        |
        v
Copy .data
        |
        |
        v
Clear .bss
        |
        |
        v
__libc_init_array()
        |
        |
        v
main()
```

Application starts running.

---

# Complete STM32 Boot Flow

```
POWER ON
   |
   |
RESET
   |
   |
Check BOOT MODE
   |
   |
Boot from Flash
   |
   |
Vector Table @ 0x08000000
   |
   |
Read Initial MSP
   |
   |
SP = 0x20009000
   |
   |
Read Reset Handler
   |
   |
PC = 0x080001E4
   |
   |
Execute Reset_Handler()
   |
   |
Initialize Clock
   |
   |
Copy .data Flash --> SRAM
   |
   |
Clear .bss
   |
   |
Initialize C Library
   |
   |
main()
```