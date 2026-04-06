### intreview structure
        basic c qurstion
        programminng
            bit manipulation
            dsa or array
        prohetc explanation
        problem you have faced

## Pre-prcoessor direcive
#include <stdio.h>       // include system header
#define PI 3.14          // object-like macro
### MISRA C
    Example:
        char a, b, c;
        c=a+b // here ans will overf flow and c should be int

    dynmica allocation not allowed

    recursion not allowed

### Pre processor directives
#include <stdio.h>       // include system header

#define PI 3.14          // object-like macro
#undef PI                // undefine macro

#ifdef DEBUG             // if macro defined
#endif

#undefine PI 3.24
#ifndef HEADER_H         // if macro NOT defined (include guard)
#define HEADER_H
#endif

#pragma pack(1)          // struct alignment

#error "message"         // force compile error
#warning "message"       // compile warning (GCC extension)

# what is rentrant fucntion
### inline vs MACRO
### Q3. Inline Function vs Macro

    Feature           Macro (#define)                     Inline Function
    -----------       ------------------------------      ------------------------------
    Expansion         Preprocessor (text substitution)    Compiler (code inlining hint)
    Type checking     None                                Yes — full C type checking
    Debugging         Hard — no symbol in debugger        Easy — shows in stack trace
    Scope             Global (no scope rules)             Follows C scoping rules
    Side effects      Dangerous — args evaluated twice    Safe — args evaluated once
    Return value      No (expression only)                Yes — has a return type
    Recursion         Not possible                        Possible (compiler may not inline)
    Header needed     No                                  Defined in header (static inline)

    Side effect trap (Macro):

        #define SQ(x)  ((x) * (x))

        int a = 3;
        int r = SQ(a++);   // expands to ((a++) * (a++)) — UB, a incremented twice

    Safe with inline:

        static inline int sq(int x) { return x * x; }

        int a = 3;
        int r = sq(a++);   // a++ evaluated once, safe — r = 9, a = 4

    When to use which:

        Use Macro    ->  Simple constants (#define MAX 100)
                         Conditional compilation (#ifdef DEBUG)
                         Stringification / token pasting (# and ##)

        Use Inline   ->  Any computation involving arguments
                         When type safety matters
                         When you need to step through in debugger

### Structure vs Union

    Feature           struct                              union
    -----------       ------------------------------      ------------------------------
    Memory            Sum of all member sizes             Size of largest member only
    Storage           Each member has its own memory      All members share same memory
    Access            All members accessible anytime      Only last-written member valid
    Use case          Group related data fields            Memory-efficient variant types
    Padding           Yes — compiler may add padding      Yes — based on largest member

### Q7. typedef vs #define

    Feature           typedef                             #define
    -----------       ------------------------------      ------------------------------
    Processed by      Compiler                            Preprocessor (before compile)
    Type checking     Yes — real type alias               No — pure text substitution
    Scope             Follows C scoping rules             Global from point of definition
    Pointer types     Correct and safe                    Dangerous — see trap below
    Debugger          Shows type name                     Expanded text, no type name
    Arrays / complex  Works cleanly                       Breaks easily

       
### what is rentrant fucntion
    If you call a function once, pause the execution while it's in the middle of running,
    then call it a second time, the function is now running in two "contexts."
    The point is that the function can be running multiple times simultaneously, which usually means in multiple threads.
    int add(int a, int b) {
        int c = a + b;   // c is on the stack, local to this call
        return c;
    }

    what is the use?
      That’s why you can call add(2,3) and add(5,7) at the same time FROM DIFFRENT THREAD— each call has its own c.

### Polymorphism in C++
    Polymorphism means **one interface, multiple behaviors**.
    Two types: Compile time and Runtime.

### Function Overloading — Compile Time Polymorphism
    Same function name, different parameter types or count.
    Compiler decides which function to call at **compile time**.

    int add(int a, int b)         { return a + b; }
    float add(float a, float b)   { return a + b; }

### Function Overriding — Runtime Polymorphism

    Child class redefines a parent class function.
    Decision is made at **runtime** using virtual table (vtable).

### Trap C questions
    --
    unsigned char x= 0xff;

    if(~x)
        printf("hello");
    else
        printf("world")
    
    Result: it will print hello,
    x is promoted to integer from char in bit mainpualtion before ~
    --

    (*fnptr)++; //this will incremnet  the value

####  array vs pointer

int main() {
    int a[] = {1, 2, 3};
    int *p = a;
    printf("%d", *(p + 2));
    return 0;
}

result : 03
-------------------------------------------------------------------------------
# 1. ASCII & Characters
-------------------------------------------------------------------------------

    '0' = 0x30 = 48
    'A' = 0x41 = 65
    'a' = 0x61 = 97
    Difference between upper and lower case = 32

    Lowercase to Uppercase:   str[i] = str[i] - 32
    Uppercase to Lowercase:   str[i] = str[i] + 32

### prmitive data types

    Type       Size      Range (signed)
    -------    ------    ----------------------------
    char       1 byte    -128 to 127
    int        4 bytes   -2,147,483,648 to 2,147,483,647
    float      4 bytes   ~6-7 decimal digits
    double     8 bytes   ~15-16 decimal digits

### Storage classes:
    Keyword     Lifetime     Scope          Stored In
    ---------   ----------   ------------   -----------
    auto        Block        Local          Stack
    static      Program      Local/File     .data / .bss
    extern      Program      Global         .data
    register    Block        Local          CPU Register (hint only)

### Volatile Keyword in C

    volatile uint32_t *TIMER_REG = (uint32_t *)0x40000000;

    while (*TIMER_REG == 0) {
        // Without volatile: compiler reads once, caches value
        //                   --> loop never exits (wrong!)
        // With volatile:    reads from HW register every iteration (correct)
    }

### What is const volatile — does it make sense?

    const volatile uint32_t *STATUS_REG = (uint32_t *)0x40000010;

    YES — makes perfect sense for read-only hardware status registers:
      const    --> your code cannot write to it
      volatile --> compiler must re-read it every time (hardware changes it)



### qualifiers :are keywords that modify the behavior of variables and data types
    const    --> value cannot change, compiler enforces read-only
    volatile --> value can change outside compiler's knowledge,
                 prevents compiler optimization
    
    example:
    const int var
    vaoltile int var
    const volatile int  var

    const volatile int *ptr → pointer to read-only volatile int (cannot modify the value, but pointer can change).

    int volatile *const ptr → constant pointer to a volatile int (can modify the value, but pointer cannot change)


-------------------------------------------------------------------------------
###### 5. Pointers
-------------------------------------------------------------------------------

    int  x   = 10;
    int *ptr = &x;    // ptr holds address of x
    *ptr = 20;        // dereference: changes x to 20
    ptr++;            // moves to next int (4 bytes ahead on 32-bit)

int array[6] = {4, 3, 5, 6, 3, 8};

+-----------------------+----------------------------------------------------------------------+
| Declaration           | Meaning and Example                                                  |
+-----------------------+----------------------------------------------------------------------+
| int *ptr              | pointer to int                                                       |
|                       | int *ptr = &array[0];                                                |
+-----------------------+----------------------------------------------------------------------+
| int **ptr             | pointer to pointer to int                                            |
|                       | int *p = &array[0];  int **ptr = &p;                                 |
+-----------------------+----------------------------------------------------------------------+
| int (*ptr)[6]         | pointer to entire array of 6 ints                                    |
|                       | int (*ptr)[6] = &array;                                              |
+-----------------------+----------------------------------------------------------------------+
| void (*ptr)(void)     | pointer to function, no args, void return                            |
|                       | void foo(void);  void (*ptr)(void) = foo;                            |
+-----------------------+----------------------------------------------------------------------+
| int (*ptr)(int, int)  | pointer to function, 2 int args, int return                          |
|                       | int add(int,int);  int (*ptr)(int,int) = add;                        |
+-----------------------+----------------------------------------------------------------------+
| int *ptr[6]           | array of 6 pointers to int                                           |
|                       | int *ptr[6] = {&array[0], &array[1], &array[2],                      |
|                       |                &array[3], &array[4], &array[5]};                     |
+-----------------------+----------------------------------------------------------------------+


### Difference between *ptr++, (*ptr)++, and *++ptr?

    int arr[] = {10, 20, 30};
    int *ptr = arr;

    *ptr++    --> returns 10, then moves ptr to arr[1]
    (*ptr)++  --> increments VALUE at ptr, arr[0] becomes 11, ptr unchanged
    *++ptr    --> moves ptr to arr[1] first, then returns 20

    *Note: 
    if + is near to p adress will increment  *++p or *p++
    if + is near to * data will increment (*ptr)++, ++*p, 

### Difference between const int *ptr and int * const ptr?

    const int *ptr        --> can change ptr, cannot change *ptr
    int * const ptr       --> can change *ptr, cannot change ptr
    const int * const ptr --> cannot change either

### What is a function pointer? Embedded use case?

    int add(int a, int b)
    {
        return a + b;
    }

    int main(void)
    {
        int (*fnptr)(int, int);   // declare function pointer
        fnptr = add;              // point it at add()

        int result = fnptr(3, 4); // call through pointer
        printf("Result = %d\n", result);  // prints 7
        return 0;
    }

    Used for: interrupt vector tables, state machines, callbacks.

### Pointer Types

    NULL Pointer:A pointer that is explicitly assigned NULL.It does not point to any valid memory address.
    int *p = NULL;
    Dereferencing a NULL pointer causes segmentation fault.

    Wild Pointer:A pointer that is declared but NOT initialized.
    It points to some random/garbage address — behavior is undefined.
    int *p;       // wild pointer — NOT initialized
    *p = 10;      // dangerous! writing to unknown address
    Fix: always initialize to NULL if address is not known yet.

    Dangling Pointer:
    A pointer that points to memory that has already been freed.
    After free(), the pointer still holds the old address — using it is undefined behavior.
    int *p = malloc(sizeof(int));
    free(p);      // memory released
    *p = 10;      // DANGLING — undefined behavior
    Fix: after free(), always set p = NULL.

    Double Pointer (Pointer to Pointer):
    A pointer that stores the address of another pointer.
    int a = 10;
    int *p = &a;
    int **pp = &p;   // pp → p → a
    Used in: dynamic 2D arrays, modifying pointer inside a function.

    Void Pointer (Generic Pointer):
    A pointer with no associated data type.
    Can be type-casted to any pointer type.
    void *p;
    int a = 10;
    p = &a;                    // valid — no cast needed
    printf("%d", *(int*)p);    // type cast required to dereference
    Used in: malloc(), memcpy(), generic functions like qsort().

### how to type case pointer adress
    (void *) ptr
    (char *)ptr

### Identifier: identifier is simply the name used to identify variables, functions, arrays, structures, or any other user-defined element in a program. It’s how you give a meaningful label to entities in your code.
    int a;
    void add()

-------------------------------------------------------------------------------
###### 6. Memory Layout
-------------------------------------------------------------------------------

    High Address
    +---------------------+
    |        Stack        |   Local vars, function frames  (grows downward)
    +---------------------+
    |    (free space)     |
    +---------------------+
    |        Heap         |   malloc/calloc                 (grows upward)
    +---------------------+
    |        .BSS         |   Uninitialized globals/statics (zeroed at startup)
    +---------------------+
    |        .Data        |   Initialized globals/statics   (copied FLASH->RAM)
    +---------------------+
    |        .Text        |   Code / machine instructions   (FLASH, read-only)
    +---------------------+
    Low Address

-------------------------------------------------------------------------------
###### 7. Compilation Stages
-------------------------------------------------------------------------------

    .c --> [Preprocessor] --> .i --> [Compiler] --> .s --> [Assembler] --> .o --> [Linker] --> .elf/.bin/.hex

    Stage          Input    Output   Job
    -----------    -----    ------   -------------------------------------------
    Preprocessor   .c       .i       Expand macros, ###include, ###ifdef, remove comments
    Compiler       .i       .s       Generate assembly (syntax + semantic check)
    Assembler      .s       .o       Generate machine code object file
    Linker         .o       .elf     Resolve symbols, link libs, apply memory map

### Difference between .bin, .hex, and .elf?

    Format   Description                          Used For
    ------   ----------------------------------   --------------------
    .bin     Raw binary bytes                     Direct flash write
    .hex     Intel HEX (ASCII + address + CRC)    Most programmers
    .elf     With debug symbols                   GDB debugging
    .mot     Motorola S-Record                    Automotive tools

### Bootup sequence
    Power ON / Reset
        │
        ▼
    Reset Vector ──► points to startup code (written in assembly)
        │
        ▼
    Startup Code
    ├── Set up Stack Pointer
    ├── Copy .data section: FLASH → RAM
    └── Zero out .bss section
        │
        ▼
    SystemInit()  ──► Configure system clocks & hardware
        │
        ▼
    main()  ──► Application entry point
                ⚠️  Must NEVER return in embedded systems!

#########  What is a Reset Vector?

    Fixed memory address the CPU fetches and jumps to after reset.
    On ARM Cortex-M:
        0x00000000 = initial Stack Pointer value
        0x00000004 = Reset Handler address (start of startup code)

### Embedded System Startup Flow or reset to main or power on

When an embedded system powers on:

- **Reset Vector**: CPU fetches the reset vector, which points to the startup code (written in assembly).
- **Startup Code**:
  - Sets up the **stack pointer**.
  - Copies initialized variables from **FLASH to RAM** (`.data` section).
  - Zeros out uninitialized variables (`.bss` section).
- **SystemInit()**: Configures system clocks and hardware setup.
- **main()**: Application entry point.  
  - In embedded systems, `main()` should **never return**.


-------------------------------------------------------------------------------
###### 9. Dynamic Memory Allocation
-------------------------------------------------------------------------------

    malloc(size)        allocate, memory is UNINITIALIZED (garbage)
    calloc(n, size)     allocate n items, memory is ZERO-INITIALIZED
    realloc(ptr, size)  resize existing allocation (may move memory)
    free(ptr)           release -- always set ptr = NULL after!

   ### google interview
    how to create our own malloc, my malloc?
        simply create statci int char[500] --> this will exceeds data segment and cross heap section

        we cant use pointer like assigning heap adress to ptr, next moment if we use malloca this adress wil be occupied



### Q2. What is a memory leak? How to detect?

    void leak(void) {
        int *ptr = malloc(100);
        return;   // forgot free() --> heap shrinks on every call
    }             //                --> eventually malloc returns NULL --> crash

    Fix: always pair malloc with free:
        int *ptr = malloc(100);
        if (ptr == NULL) return;
        // ... use ptr ...
        free(ptr);
        ptr = NULL;

    Detection tools: Valgrind (Linux), heap usage hooks, custom malloc wrappers.

### Q3. Why is malloc avoided in safety-critical embedded?

    - Non-deterministic timing (MISRA C rule violation)
    - Heap fragmentation over time
    - Memory leaks cause silent failure
    - Limited RAM on MCU gets exhausted unpredictably

    Alternative -- static memory pool:

        uint8_t pool[NUM_BUFS][BUF_SIZE];
        uint8_t inUse[NUM_BUFS] = {0};

        uint8_t *poolAlloc(void) {
            for (int i = 0; i < NUM_BUFS; i++)
                if (!inUse[i]) { inUse[i] = 1; return pool[i]; }
            return NULL;
        }

        void poolFree(uint8_t *p) {
            int i = (p - pool[0]) / BUF_SIZE;
            inUse[i] = 0;
        }


### Q2. What is interrupt latency?

    Time from interrupt signal assertion to first ISR instruction executing.
    Factors: CPU pipeline flush, saving context (stacking registers), priority.
    ARM Cortex-M3: typically 12 clock cycles minimum latency.



### Q3. What is a race condition between ISR and main? How to fix?

    Problem:
        volatile uint32_t counter = 0;
        void TIMER_ISR(void) 
        { 
            counter++; 
            }

        int main(void) {
            uint32_t val = counter;   // ISR may fire between read and write!
        }

    counter++ is a 3-step operation: read, modify, write.
    ISR can interrupt between any step --> corrupted value.

    Fix: disable interrupts around the critical section:
        __disable_irq();
        uint32_t val = counter;
        __enable_irq();


### Q5. What is interrupt priority and nesting?

    Higher priority interrupts can preempt lower priority ISRs.
    ARM Cortex-M: lower number = higher priority (0 = highest).
    Configured via NVIC (Nested Vectored Interrupt Controller).

        NVIC_SetPriority(UART1_IRQn, 1);   // high priority
        NVIC_SetPriority(TIM2_IRQn,  5);   // lower priority

-------------------------------------------------------------------------------
## 12. RTOS Concepts
-------------------------------------------------------------------------------

    RTOS = Real-Time Operating System
    Schedules multiple tasks with deterministic timing.
    Guarantees response within a deadline.

### Q1. Difference between a task and a thread?

    Process (one program running)
    │
    ├── Shared: heap, globals, code, file descriptors
    │
    ├── Thread 1 → own stack, PC, registers
    ├── Thread 2 → own stack, PC, registers
    └── Thread 3 → own stack, PC, registers

### Q2. What is a semaphore? Give an embedded example.

    Binary semaphore -- like a signal flag between ISR and task.

        SemaphoreHandle_t sem = xSemaphoreCreateBinary();

        void UART_ISR(void) {
            xSemaphoreGiveFromISR(sem, NULL);   // signal from ISR
        }

        void uartTask(void *arg) {
            while (1) {
                xSemaphoreTake(sem, portMAX_DELAY);  // block until ISR fires
                processData();
            }
        }


### Q3. Difference between mutex and semaphore?

    Feature              Mutex                         Semaphore
    ----------------     --------------------------    ----------------------
    Ownership            Owned by locking task         No ownership
    Priority inversion   Protected                     Not protected
    Use case             Mutual exclusion (shared data) Signaling

        xSemaphoreTake(mutex, portMAX_DELAY);
        sharedBuffer[0] = 42;   // critical section
        xSemaphoreGive(mutex);


### Q4. What is priority inversion? How is it solved?

    Scenario:
    - Low-priority task holds mutex
    - High-priority task needs that mutex -- blocks
    - Medium-priority task runs instead (doesn't need mutex)
    - High-priority task effectively runs at low priority

    Solution: Priority Inheritance
    - Temporarily boost low-priority task to match high-priority waiter
    - FreeRTOS mutexes support this automatically


### Q5. What is a deadlock? How to avoid it?

    Task A holds Mutex1, waits for Mutex2.
    Task B holds Mutex2, waits for Mutex1.
    Both block forever --> deadlock.

    Prevention:
    - Always acquire mutexes in the SAME ORDER across all tasks
    - Use timeouts instead of blocking forever
    - Minimize number of mutexes held at the same time

-------------------------------------------------------------------------------
## 13. Watchdog Timer
-------------------------------------------------------------------------------

    Hardware timer that resets the MCU if not kicked within a timeout.
    Detects software hangs and crashes.
    Essential for unattended and safety-critical systems.

### Q1. Difference between UART, SPI, CAN, I2C?
Feature          UART               SPI                      I2C                      CAN
-----------      ----------------   ----------------------   ----------------------   ----------------------
Wires            2 (TX, RX)         4 (MOSI,MISO,SCK,CS)     2 (SDA, SCL)             2 (CANH, CANL)
Speed            up to ~5 Mbps      up to 50+ Mbps           100k / 400k / 1MHz       125k / 250k / 500k / 1Mbps
Topology         Point-to-point     1 master, multi slave    Multi master+slave        Multi master (bus)
Addressing       None               Chip Select per slave    7-bit address             11-bit / 29-bit ID
Synchronous      No (async)         Yes                      Yes                      No (async)
Error handling   None               None                     ACK only                 CRC, ACK, error frames
Use case         Debug, GPS, BT     Flash, ADC, display      Sensors, EEPROM           Automotive ECUs, OBD


### Q3. What is I2C clock stretching?

    Slave holds SCL line LOW to pause the master while preparing data.
    Master must wait until slave releases SCL.
    Some I2C masters do not support clock stretching -- check datasheet!


### Q4. What is SPI mode (CPOL and CPHA)?

    Mode   CPOL   CPHA   Clock idle   Data sampled
    ----   ----   ----   ----------   ------------
    0      0      0      LOW          Rising edge
    1      0      1      LOW          Falling edge
    2      1      0      HIGH         Falling edge
    3      1      1      HIGH         Rising edge



---
## asm

# assembler directive
 commands in assembly language source code that instruct the assembler software how to process the program,
 rather than being translated into machine code instructions
 in Linker we have .bss, .data, .txt this are assebler directiver

## Communication Protocol

### i2c Communication

    +-------+----------+---+----------+---+--------+---+---+
    |   S   | ADDR[7:1]|R/W|  A/NA    |  DATA[7:0] | A |P  |
    +-------+----------+---+----------+---+--------+---+---+

    Field       Bits    Driven by       Description
    -------     ----    ----------      ---------------------------
    S             -     Master          START condition
    ADDR        [7:1]   Master          7-bit slave address
    R/W          [0]    Master          0 = Write, 1 = Read
    A/NA          -     Slave           ACK after address
    DATA        [7:0]   Master(W)/      8 data bits, MSB first
                        Slave(R)
    A/NA          -     Slave(W)/       ACK after data byte
                        Master(R)
    P             -     Master          STOP condition


#### clock Speed

    Mode            Speed       Notes
    -----------     --------    ---------------------------
    Standard        100 kHz     All devices supported
    Fast            400 kHz     MPU-6050, SSD1306 supported
    Fast mode+      1 MHz       SSD1306 (some variants)
    High speed      3.4 MHz     Rare, special hw needed

    Pull-up resistors:
    100 kHz  ->  4.7 kohm typical
    400 kHz  ->  2.2 kohm typical
    1 MHz    ->  1.0 kohm typical

### CAN Communication

Differential signaling on CAN_H and CAN_L lines:

State       CAN_H       CAN_L       Differential (H-L)
---------   -------     -------     ------------------
Dominant    3.5 V       1.5 V       +2.0 V  (logic 0)
Recessive   2.5 V       2.5 V        0.0 V  (logic 1)

Dominant wins on bus (wired-AND): any node sending 0 pulls bus dominant.

---
Type                Description
----------------    ----------------------------------------
Data Frame          Carries actual data (most common)
Remote Frame        Requests data from another node (RTR=1)
Error Frame         Signals a detected error on the bus
Overload Frame      Requests delay between frames
------

+-----+-------------+-----+-----+-----+-----+----------+-----------+-----+-----+
| SOF |   ID[10:0]  | RTR | IDE | r0  | DLC |   DATA   |  CRC+DEL  | ACK | EOF |
+-----+-------------+-----+-----+-----+-----+----------+-----------+-----+-----+
  1 b      11 b       1 b   1 b   1 b   4 b   0-64 b      15+1 b    1+1b   7 b

* Data: 0 to 8 bytes (0 to 64 bits)

Field       Bits    Value           Description
-------     ----    -----           ----------------------------------
SOF           1     0 (dom)         Start of frame, sync all nodes
ID         [10:0]   0x000-0x7FF     Message priority + identifier
RTR           1     0=Data, 1=Rmt  Remote Transmission Request
IDE           1     0               0 = Standard frame (11-bit ID)
r0            1     0 (dom)         Reserved, always dominant
DLC         [3:0]   0-8             Number of data bytes
DATA        0-64b   payload         Actual data, MSB first
CRC          15b    calculated      CRC over SOF+ID+ctrl+data
CRC DEL       1     1 (rec)         CRC delimiter, always recessive
ACK slot      1     0 (dom)         Receiver pulls dominant = ACK
ACK DEL       1     1 (rec)         ACK delimiter
EOF           7     1111111 (rec)   End of frame
IFS           3     111 (rec)       Intermission (bus idle)

---
### UART Communication

One UART frame = 1 start bit + data bits + optional parity + stop bit(s)

IDLE  Start   D0   D1   D2   D3   D4   D5   D6   D7   Parity  Stop  IDLE
----+       +----+----+----+----+----+----+----+----+--------+------+----
    |       |                                                 |      |
    +-------+                                                 +------+
      LOW                   data bits (LSB first)              HIGH

+------+------+----+----+----+----+----+----+----+----+--------+------+
| IDLE | STRT | D0 | D1 | D2 | D3 | D4 | D5 | D6 | D7 |  PAR  | STOP |
+------+------+----+----+----+----+----+----+----+----+--------+------+
         1 b   <-------- 5 to 9 data bits -------->   0 or 1b  1-2 b

Field       Bits    Value       Description
-------     ----    -----       ----------------------------------
IDLE          -     1 (HIGH)    Line idle state
Start         1     0 (LOW)     Signals start of frame
Data        5-9     payload     LSB sent first (D0 first)
Parity      0-1     E/O/N       Even, Odd, or None
Stop        1-2     1 (HIGH)    End of frame, line returns HIGH

---

### SPI communication
    Master                          Slave
    ------                          -----
    SCLK  -----------------------------> SCLK
    MOSI  -----------------------------> MOSI
    MISO  <----------------------------- MISO
    CS    -----------------------------> CS
    GND   ------------------------------ GND

    CS pulled LOW by master to select slave.







