# RTOS Concepts
*By Sanjay Adhikari / November 20, 2019*

Before we go on to dig deep into the internal working of the Real time operating systems
let us first go over some fundamental concepts one needs to understand to go about
building their own RTOS. We are going to test and debug our custom RTOS on a
Microcontroller and more specifically an ARM cortex-M microcontroller. Hence we also
need to be aware of the features provided in the MCU (microcontroller unit). So let's get
started.

---

## SOME BASIC OPERATING SYSTEM CONCEPTS

There are some fundamental concepts that every operating system in the world follows.
And are equally important for Real time OS. Let's take a look at some of the
Fundamentals of operating systems:

### 1. Thread

Thread is a single unit of execution and is a part of a process. In a single core CPU which
is common for microcontroller based embedded system there are applications which
require you to perform multitasking. Each task you need to perform will be programmed
in a single sequential flow. In like manner several such thread are coded to perform
multiple tasks.

### 2. Task Scheduler

A task scheduler is a piece of code that decides which Thread/Task to run next. There are
multiple methods you can use to decide which thread should be loaded and executed
next. These 'methods' per se are called scheduling algorithms. A scheduling algorithm
takes help from the Task Control block during it's decision making process.

### 3. Context switching

The process of storing the state of the process in the memory so that it can be resumed
later, is known as context switching. Performing context switching allows CPU to write
multiple tasks simultaneously and is an essential part of a RTOS kernel.

### 4. Thread/task control block

A task control block (TCB) is a data structure used by kernels to maintain information
about a task. To give a sense of a typical Task control block given below is the task
control block of Micrium µC/OS-III.

```c
struct os_tcb {
    CPU_STK         *StkPtr;
    void            *ExtPtr;
    CPU_STK         *StkLimitPtr;
    OS_TCB          *NextPtr;
    OS_TCB          *PrevPtr;
    OS_TCB          *TickNextPtr;
    OS_TCB          *TickPrevPtr;
    OS_CHAR         *NamePtr;
    CPU_STK         *StkBasePtr;
    OS_TLS          TLS_Tbl[OS_CFG_TLS_TBL_SIZE] OS_TASK_PTR TaskEntryAddr;
    void            *TaskEntryArg;
    OS_PEND_DATA    *PendDataTblPtr;
    OS_STATE        PendOn;
    OS_STATUS       PendStatus;
    OS_STATE        TaskState;
    OS_PRIO         Prio;
    CPU_STK_SIZE    StkSize;
    OS_OPT          Opt;
    OS_OBJ_QTY      PendDataEntries;
    CPU_TS          TS;
    OS_SEM_CTR      SemCtr;
    OS_TICK         TickRemain;
    OS_TICK         TickCtrPrev;
    OS_TICK         TimeQuanta;
    OS_TICK         TimeQuantaCtr;
    void            *MsgPtr;
    OS_MSG_SIZE     MsgSize;
    OS_MSG_Q        MsgQ;
    CPU_TS          MsgQPendTime;
    CPU_TS          MsgQPendTimeMax;
    OS_REG          RegTbl[OS_TASK_REG_TBL_SIZE];
    OS_FLAGS        FlagsPend;
    OS_FLAGS        FlagsRdy;
    OS_OPT          FlagsOpt;
    OS_NESTING_CTR  SuspendCtr;
    OS_CPU_USAGE    CPUUsage;
    OS_CPU_USAGE    CPUUsageMax;
    OS_CTX_SW_CTR   CtxSwCtr;
    CPU_TS          CyclesDelta;
    CPU_TS          CyclesStart;
    OS_CYCLES       CyclesTotal;
    OS_CYCLES       CyclesTotalPrev;
    CPU_TS          SemPendTime;
    CPU_TS          SemPendTimeMax;
    CPU_STK_SIZE    StkUsed;
    CPU_STK_SIZE    StkFree;
    CPU_TS          IntDisTimeMax;
    CPU                SchedLockTimeMax;
    OS_TCB          *DbgNextPtr;
    OS_TCB          *DbgPrevPtr;
    CPU_CHAR        *DbgNamePtr;
};
```

The above block controls all the information a scheduler will need to perform context switching.

---

### 5. Scheduling algorithms

The scheduling decision making process can be as simple as executing them one after
the other (round Robin). The complexity of the scheduling methods depends on the
application requirements. I have listed below some common scheduling methods for a
real time kernel:

#### First-Come, First-Served (FCFS) Scheduling

First come first serve (FCFS) scheduling algorithm schedules the jobs according to their
arrival time. The job which arrives first in the queue will get the CPU first.

#### Shortest-Job-Next (SJN) Scheduling

Shortest job next (SJN) is a scheduling policy that selects the process with the smallest
execution time. This is a non-pre emptive method.

#### Priority Scheduling

Priority scheduling is a scheduling processes based on the task priority. In this method,
the scheduler chooses the task to be executed next as per the priority.

#### Shortest Remaining Time

It is a scheduling method which uses the task completion time to decide its next task.
This algorithm in a sense is a pre-emptive version of shortest-job-next algorithm. In this
method the job with the shortest remaining time is executed first.

#### Rate monotonic Scheduling

It is a static priority assignment algorithm used in real-time operating systems (RTOS).
These algorithm assigns the priority to the task according to their periodicity and run
time. i.e. a task with lower periodicity is assigned a higher priority. Round Robin
algorithm: is a pre-emptive algorithm and switches between the task one after the other
in a circular fashion. This is the simplest scheduling algorithm.

---

### 6. Pre-emptive and Non Pre-emptive algorithm

Pre-emption refers to the temporary interruption and suspension of a task. The task are
pre-empted because sometimes it is important to serve the higher priority task first.
Therefore, the running task is interrupted and resumed later when the priority task has
finished its execution. In non-pre-emptive scheduling, a task cannot be interrupted and is
executed till its completion.

---

### 7. Semaphore

Semaphores are integer variables that are used to solve the critical section problem. They
use wait and signal method for process synchronization. Wait and signal are atomic
operations. First of all what are atomic operations? They are instructions which during
their execution cannot be interrupted.

Next, what is the critical section problem?

The part of the program which tries to access any kind of shared resource is known as
the critical section. These resources may be any resource in a computer like a memory

# RTOS Concepts - Page 2
*By Sanjay Adhikari / November 20, 2019*

---

## Which controller can I use that support RTOS?

A Scheduler can be written for most of the microcontrollers. Even the low end profiles
such as 8051 can support RTOS (RTX51tiny, FreeRtos etc. have designed kernels for
8051). The choice of the MCU totally depends on the application requirement. But since
we are building a kernel for ARM cortex-M profile of Microcontrollers we are going to
focus our attention on the feature of cortex-m processors. ARM provides multiple OS
support Features in their cortex-M profile using which the performance of the scheduler
can be enhanced. Although we are not going to use all the features listed below but it is
really important to have a basic understanding of these features.

---

## ARM Cortex-M Register Map

**General Purpose Registers:** R0 – R12 (13 registers)
- Used by instructions for general execution

**Special Registers:**
- **R13 (Stack Pointer):**
  - MSP (Main Stack Pointer) — used by OS kernel, exception handlers, privileged code. Default stack pointer.
  - PSP (Process Stack Pointer) — used by base-level application code (when not running an exception handler)
  - This dual-SP feature is known as **Shadowed Stack Pointer**

- **R14 (Link Register)** — stores the return address when a branch with link instruction is executed (e.g. returning from a function)

- **R15 (Program Counter)** — stores address of current instruction being executed. In ARM cortex-m, due to pipeline architecture, PC always points ahead of the currently executing instruction depending on pipeline depth.

---

## Special Purpose Registers (5 types)

1. **PSRs** (Program Status Registers)
2. **PRIMASK, FAULTMASK, BASEPRI** (Interrupt Mask Registers)
3. **CONTROL** (Control Register)

---

### Program Status Registers (PSRs)

Divided into 3 parts:
- **APSR** — Application Program Status Register
- **IPSR** — Interrupt Program Status Register
- **EPSR** — Execution Program Status Register

All three can be accessed together or separately using MSR and MRS instructions.
When accessed collectively, the name **xPSR** is used.
- PSRs can be read using MRS instruction
- APSR can be changed using MSR instruction
- EPSR and IPSR are **read-only**

---

### PRIMASK, FAULTMASK, and BASEPRI

The **Interrupt Mask Registers**:
- **PRIMASK** and **BASEPRI** — useful for disabling interrupts temporarily for timing critical tasks
- **FAULTMASK** — can be used to disable fault handling temporarily; useful when OS kernel is cleaning up after a crashed task and doesn't want to be interrupted by other faults from the crashed process

---

### The Control Register

Used to define:
- Selection between **MSP** and **PSP**
- The **privilege level**

Has 2 bits:
- **CONTROL[1]** — checks Stack Status: `1` if PSP is used, `0` if MSP (default) is used
- **CONTROL[0]** — defines privileged thread mode (`1`) or user state in thread mode (`0`)

---

## Operating Modes and Privilege Levels

Cortex-M provides two operating modes:
- **Thread mode** — default main program
- **Handler mode** — triggered by NVIC for exception handling; always privileged mode

And two access levels:
- **Privileged mode** — can access all special and control registers; can switch between user and privileged level
- **User mode** — cannot access special function registers or control registers; attempting to do so causes a fault handler exception

> Switching from user thread mode to privileged thread mode can only be done via handler mode.

---

## Systick Timer

- A **24-bit down counter** for generating periodic OS exceptions for time keeping and task management
- Present **inside the core** of the MCU (not a peripheral)
- Chosen over other timers because its **interrupt priority is much higher** than all other timers and peripherals in the MCU
- Higher priority ensures the handler won't be pre-empted during execution

---

## ARM Cortex-M Exception Table (Fig. 5)

| Exception Number | Exception Type | Priority | Description |
|---|---|---|---|
| 0 | NA | NA | No exception running |
| 1 | Reset | -3 (Highest) | Reset |
| 2 | NMI | -2 | NMI (external NMI input) |
| 3 | Hard fault | -1 | All fault conditions if fault handler not enabled |
| 4 | MemManage fault | Programmable | Memory management fault; MPU violation |
| 5 | Bus fault | Programmable | Bus error (prefetch abort or data abort) |
| 6 | Usage fault | Programmable | Program error |
| 7–10 | Reserved | NA | Reserved |
| 11 | SVCall | Programmable | Supervisor call |
| 12 | Debug monitor | Programmable | Debug monitor (breakpoints, watchpoints) |
| 13 | Reserved | NA | Reserved |
| 14 | PendSV | Programmable | Pendable request for system service |
| 15 | SYSTICK | Programmable | System tick timer |
| 16 | IRQ #0 | Programmable | External interrupt #0 |
| 17 | IRQ #1 | Programmable | External interrupt #1 |
| ... | ... | ... | ... |
| 255 | IRQ #239 | Programmable | External interrupt #239 |

*Source: The Definitive Guide to ARM Cortex-M3 (second edition)*

---

## The PendSV and SVC Exception

**SVC (Supervisor Call):**
- Used for generating system function calls
- Allows OS to provide hardware access through a service call routine
- Prevents user programs from accessing hardware directly
- When user program needs hardware → generates SVC exception → software exception handler in OS executes and provides the service

**PendSV (Pendable Service Call):**
- Usually used along with SVC
- Unlike SVC (which expects immediate execution), PendSV **can be pended**
- Useful for OS to pend an exception so action is performed after other important tasks complete
- PendSV interrupt routine called by writing `1` to `PENDSVSET` bit in the NVIC Interrupt Control State Register (ICSR)

---

## How will I start writing my own RTOS?

### Tools Required:

**1. Keil uVision**
- Keil MDK is a software development solution for ARM-based microcontrollers
- Includes all components needed to create, build, and debug embedded applications
- Download: https://www2.keil.com/mdk5

**2. Hardware — STM32F746 (Nucleo144 board)**
- Any MCU with ARM cortex-m3 or higher will work
- STM32F746 is a CORTEX-M7 based microcontroller by ST microelectronics
- Nucleo144 development board has an on-board ST-link debugger
- Recommended: choose a board with on-board debugger for easier error resolution

---

*Now that we are acquainted with the internal aspects of the operating system and our
hardware, we can jump right into creating our own project and start building our scheduler.*

*Author: Jayvik Desai*
