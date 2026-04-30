const FLASHCARDS = [
  {
    q: "what are interview Interview Structure?",
    a: `- Basic C Questions
- Programming
  - Bit Manipulation
  - DSA / Array
- Project Explanation
- Problems You Have Faced`
  },
  {
    q: "What is my Professional Summary\",?",
    a: `Senior Embedded Software Engineer with 11+ years of experience in automotive embedded systems, specializing in
device driver development, AUTOSAR MCAL, and low-level firmware engineering.\``
  },
  {
    q: "What are my Technical Skills\",?",
    a: `Device Drivers: ADC, SPI, I2C, UART, PORT, GPIO, DMA & AUTOSAR MCAL
AUTOSAR Stack: MCAL, RTE, BSW configuration using EB Tresos; Vector DaVinci
Microcontrollers / SoCs: Infineon AURIX TriCore TC2xx, NXP MCU, ARM Cortex architecture
Protocols / Interfaces: SPI, I2C, UART, CAN
RTOS: OSEK-based RTOS, task/ISR scheduling, interrupt handling
Debugging & Test Tools: TRACE32 (JTAG), Oscilloscope, Logic Analyzer, USB Analyzer, CANoe, HIL setups
Programming Languages: Embedded C, Python, MATLAB, MISRA-C guidelines
Build & DevOps: Linux, Docker, cross-compilation, CI/CD pipelines, GitHub, Makefile, ARM GCC toolchain
Requirements & SCM: IBM DOORS (traceability), MKS/PTC Integrity, SW-E5 process compliance\``
  },
  {
    q: "What is my Experience\",?",
    a: `Continental Automotive, Bangalore
Software Engineer | May 2019 – Present
• Responsible for MCAL development and software integration and testing
• Performed software integration and validation of AUTOSAR MCAL drivers ADC, SPI
• Performed Linux Docker migration

Tech Mahindra, Bangalore
Software Engineer | Dec 2017 – Apr 2019
• Developed and configured AUTOSAR MCAL IO drivers for ADC, SPI, and Timer modules in EB Tresos
• Performed board bring-up on Infineon AURIX TC2xx including JTAG debug via TRACE32, flash programming, and ADC/SPI peripheral validation on target hardware

KPIT Technologies Limited, Bangalore
Software Engineer | Feb 2017 – Aug 2017
• Designed and developed reusable AUTOSAR-compliant software libraries for MFX and IFX modules
• Conducted unit testing to validate functionality and integration alignment

BISS-ITW, Bangalore
Firmware Developer | Sep 2013 – Jan 2017
• Developed and optimized software on Texas Instruments DSP processors for real-time signal processing applications
• Developed drivers for ADC and DAC modules to support sensor data acquisition and signal conversion\``
  },
  {
    q: "What are my Projects\",?",
    a: `ADC and Timer/Watchdog Driver Development | Infineon AURIX TC2xx, EB Tresos, TRACE32
• Developed and validated low-level MCAL device drivers for Infineon AURIX TC2xx (TriCore) microcontroller, covering ADC, SPI, PORT, DMA, Timer, and Watchdog peripherals
• Performed register-level peripheral configuration, interrupt handling, and DMA channel setup
• Configured Timer channels for periodic triggering
• Configured Watchdog timer to monitor MCU health and trigger system reset on failure
• Performed board bring-up activities including JTAG debug via TRACE32, flash programming, and peripheral validation on TC2xx target hardware
• Validated driver functionality using TRACE32 (JTAG) debugger, Logic Analyzer, and Oscilloscope

SPI Driver Development
• Developed and integrated SPI driver for external memory (read/write operations) on Infineon AURIX TC2xx, covering register-level configuration, chip select handling, and data transfer sequences
• Validated SPI communication and memory read/write functionality using TRACE32 (JTAG) debugger, Logic Analyzer, and Oscilloscope

Software Integration
• End-to-end software integration, release preparation, and validation aligned with DOORS-defined requirements
• Ensured compliance with SW-E5 process through build delivery, traceability, and milestone-based quality checkpoints

AUTOSAR Library Development
• Developed modular software libraries conforming to AUTOSAR v4.2.2 specifications (MFX, IFX, IFL, MFL, EFX, E2E)
• Applied MISRA C guidelines to ensure code safety, reliability, and compliance
• Performed rigorous unit testing to validate functionality`
  },
  {
    q: "ADC Project?",
    a: `![ADC SW and HW Group Block Diagram](doc/adc_block_diagram.svg)`
  },
  {
    q: "QSPI Project?",
    a: `![QSPI](doc/qspi.svg)`
  },
  {
    q: "DMA Example using 6 channel ADC?",
    a: `![DMA Channel](doc/6CHADC1DMA.svg)`
  },
  {
    q: "what is prmitive data types?",
    a: `Type       Size      Range (signed)
    -------    ------    ----------------------------
    char       1 byte    -128 to 127
    int        4 bytes   -2,147,483,648 to 2,147,483,647
    float      4 bytes   ~6-7 decimal digits
    double     8 bytes   ~15-16 decimal digits`
  },
  {
    q: "what are the Storage classes:?",
    a: `Keyword     Lifetime     Scope          Stored In
    ---------   ----------   ------------   -----------
    1.auto        Block        Local          Stack
    2.static      Program      Local/File     .data / .bss
    3.extern      Program      Global         .data
    4.register    Block        Local          CPU Register (hint only)`
  },
  {
    q: "what is qualifiers ?",
    a: `qualifiers are keywords that modify the behavior of variables and data types
    volatile
    const`
  },
  {
    q: "what are the type modifier in c?",
    a: `short, long, signed, unsigned`
  },
  {
    q: "Derived dataypes?",
    a: `Structure
    Union`
  },
  {
    q: "wha are the Userdefined data types?",
    a: `Enum
    Typedef`
  },
  {
    q: "what is typecasting and type conversion?",
    a: `implicit->autoatically done by compiler for two compatiable data types
    explicit ->done by programmer using typecast operator to make sure no valuble data los
    type promotion-> smaller data to large one`
  },
  {
    q: "what is Identifier:?",
    a: `identifier is simply the name used to identify variables, functions, arrays, structures, 
or any other user-defined element in a program. It’s how you give a meaningful label to entities in your code.
    int a;
    void add()`
  },
  {
    q: "Volatile Keyword in C?",
    a: `Volatile is a qualifier that is applied to a variable when it is declared.
    It tells the compiler that the value of the variable may change at any time-without any action being taken by the code the compiler finds nearby.

    volatile uint32_t *TIMER_REG = (uint32_t *)0x40000000;

    while (*TIMER_REG == 0) {
        // Without volatile: compiler reads once, caches value
        //                   --> loop never exits (wrong!)
        // With volatile:    reads from HW register every iteration (correct)
    }`
  },
  {
    q: "what is the use of const keyword in c?",
    a: `The const (constant) qualifier is a type qualifier in C and C++ programming languages 
    used to declare that a variable's value is fixed, read-only, 
    and cannot be modified after initialization. 
    It acts as a compiler-enforced constraint to prevent accidental modifications,
     enhancing code security and allowing optimization.`
  },
  {
    q: "What is const volatile — does it make sense?",
    a: `const volatile uint32_t *STATUS_REG = (uint32_t *)0x40000010;

    YES — makes perfect sense for read-only hardware status registers:
    const    --> value cannot change, compiler enforces read-only
    volatile --> value can change outside compiler's knowledge,
                 prevents compiler optimization
    
    example:
    const volatile int  var`
  },
  {
    q: "What is  directrives in C?",
    a: `pre-prcoessor directive: #include, #ifdef
    assembler Directive: .data , .bss, .section
    Compiler directive: #pragma pack`
  },
  {
    q: "what is Pre-prcoessor direcive?",
    a: `#include <stdio.h>       // include system header
    #define PI 3.14          // object-like macro

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
    #warning "message"       // compile warning (GCC extension)`
  },
  {
    q: "what is assembler directive?",
    a: `commands in assembly language source code that instruct the assembler software how to process the program,
 rather than being translated into machine code instructions
 in Linker we have .bss, .data, .txt this are assebler directiver`
  },
  {
    q: "what is compiler Directive?",
    a: `Instructions to the compiler during compilation. Tells it how to compile, optimize, or handle specific code.

    #pragma is a compiler-specific directive.
    It gives special instructions to the compiler that are not part of standard C syntax.

    #pragma pack(n)Set structure member alignment to n bytes`
  },
  {
    q: "Error in embedded C?",
    a: `| Error Type        | When Detected      | Tool                  | Output                       |
|-------------------|--------------------|-----------------------|------------------------------|
| Compiler Error    | Compile time       | GCC / armcc           | No .o file generated         |
| Linker Error      | Link time          | LD / armlink          | No .elf / .hex generated     |
| Runtime Error     | Execution on target| Debugger / TRACE32    | HardFault / wrong behavior   |
| Warning           | Compile time       | GCC                   | Binary generated (risky)     |
| Logical Error     | Testing/Validation | Logic analyser / CANoe| Wrong output                 |
| Preprocessor Error| Pre-compile        | CPP                   | No .o file generated         |`
  },
  {
    q: "what is inline fucntion?",
    a: `“Inline” Function is a provision or feature provided by the compiler. Inline is a request made to the compiler to replace the inline function call with the function definition.

inline void fun(/*fun argument */)
{
    /* Function source Code */
}
When a normal function call happens function creates its stack in the main stack and initializes all local variables. After completion of function call return value is given back if any and stack is destroyed. Much time is consumed in stack operation. Hence for small functions, Inline function is beneficial as the call is replaced by definition, so no external stack is created and operations are much faster for small, commonly-used functions.`
  },
  {
    q: "Inline Function vs Macro?",
    a: `Feature           Macro (#define)                     Inline Function
    -----------       ------------------------------      ------------------------------
    Expansion         Preprocessor (text substitution)    Compiler (code inlining hint)
    Type checking     None                                Yes — full C type checking
    Debugging         Hard — no symbol in debugger        Easy — shows in stack trace
    Scope             Global (no scope rules)             Follows C scoping rules
    Side effects      Dangerous — args evaluated twice    Safe — args evaluated once
    Return value      No (expression only)                Yes — has a return type
    Recursion         Not possible                        Possible (compiler may not inline)
    Header needed     No                                  Defined in header (static inline)`
  },
  {
    q: "what is side of MACRO instead of using inline function?",
    a: `Side effect trap (Macro):

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
                         When you need to step through in debugger`
  },
  {
    q: "what is the diffrence between Structure vs Union?",
    a: `Feature           struct                              union
    -----------       ------------------------------      ------------------------------
    Memory            Sum of all member sizes             Size of largest member only
    Storage           Each member has its own memory      All members share same memory
    Access            All members accessible anytime      Only last-written member valid
    Use case          Group related data fields            Memory-efficient variant types
    Padding           Yes — compiler may add padding      Yes — based on largest member`
  },
  {
    q: "what is the diffrence between typedef vs #define?",
    a: `Feature           typedef                             #define
    -----------       ------------------------------      ------------------------------
    Processed by      Compiler                            Preprocessor (before compile)
    Type checking     Yes — real type alias               No — pure text substitution
    Scope             Follows C scoping rules             Global from point of definition
    Pointer types     Correct and safe                    Dangerous — see trap below
    Debugger          Shows type name                     Expanded text, no type name
    Arrays / complex  Works cleanly                       Breaks easily`
  },
  {
    q: "what is rentrant fucntion?",
    a: `If you call a function once, pause the execution while it's in the middle of running,
    then call it a second time, the function is now running in two "contexts."
    The point is that the function can be running multiple times simultaneously, which usually means in multiple threads.

    Example:
    int add(int a, int b) {
        int c = a + b;   // c is on the stack, local to this call
        return c;
    }

    what is the use?
      That’s why you can call add(2,3) and add(5,7) at the same time FROM DIFFRENT THREAD— each call has its own c.`
  },
  {
    q: "Polymorphism in C++?",
    a: `Polymorphism means **one interface, multiple behaviors**.
    Two types: Compile time and Runtime.`
  },
  {
    q: "Whats  Function Overloading — Compile Time Polymorphism?",
    a: `Same function name, different parameter types or count.
        Compiler decides which function to call at **compile time**.

        int add(int a, int b)         { return a + b; }
        float add(float a, float b)   { return a + b; }`
  },
  {
    q: "Whatis  Function Overriding — Runtime Polymorphism?",
    a: `Child class redefines a parent class function.
        Decision is made at **runtime** using virtual table (vtable).`
  },
  {
    q: "Trap C questions?",
    a: `--
    unsigned char x= 0xff;

    if(~x)
        printf("hello");
    else
        printf("world")
    
    Result: it will print hello,
    x is promoted to integer from char in bit mainpualtion before ~
    --

    (*fnptr)++; //this will incremnet  the value

#### what is  array vs pointer

    int main() {
        int a[] = {1, 2, 3};
        int *p = a;
        printf("%d", *(p + 2));
        return 0;
    }

    result : 03`
  },
  {
    q: "ASCII & Characters?",
    a: `'0' = 0x30 = 48
    'A' = 0x41 = 65
    'a' = 0x61 = 97
    Difference between upper and lower case = 32

    Lowercase to Uppercase:   str[i] = str[i] - 32
    Uppercase to Lowercase:   str[i] = str[i] + 32`
  },
  {
    q: "What are th Pointers declartion and meaning?",
    a: `int array[6] = {4, 3, 5, 6, 3, 8};

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
+-----------------------+----------------------------------------------------------------------+`
  },
  {
    q: "what is the Difference between ptr++, (ptr)++, and *++ptr?",
    a: `int arr[] = {10, 20, 30};
    int *ptr = arr;

    *ptr++    --> returns 10, then moves ptr to arr[1]
    (*ptr)++  --> increments VALUE at ptr, arr[0] becomes 11, ptr unchanged
    *++ptr    --> moves ptr to arr[1] first, then returns 20

    *Note: 
    if + is near to p adress will increment  *++p or *p++
    if + is near to * data will increment (*ptr)++, ++*p,`
  },
  {
    q: "Difference between const int ptr and int  const ptr?",
    a: `const int *ptr        --> can change ptr, cannot change *ptr
    int * const ptr       --> can change *ptr, cannot change ptr
    const int * const ptr --> cannot change either`
  },
  {
    q: "What is a function pointer? Embedded use case?",
    a: `int add(int a, int b)
    {
        return a + b;
    }

    int main(void)
    {
        int (*fnptr)(int, int);   // declare function pointer
        fnptr = add;              // point it at add()

        int result = fnptr(3, 4); // call through pointer
        printf("Result = %d\\n", result);  // prints 7
        return 0;
    }

    Used for: interrupt vector tables, state machines, callbacks.`
  },
  {
    q: "what are the Pointer Types?",
    a: `1.Null pointer
    2.wild pointer
    3.dangling pointer
    4.double pointer
    5.void pointer`
  },
  {
    q: "what is null nul, wild, dangling pointer?",
    a: `NULL Pointer:A pointer that is explicitly assigned NULL.It does not point to any valid memory address.
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
    Fix: after free(), always set p = NULL.`
  },
  {
    q: "what double, void pointer?",
    a: `Double Pointer (Pointer to Pointer):
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
    Used in: malloc(), memcpy(), generic functions like qsort().`
  },
  {
    q: "Array Pointer vs Function Pointer?",
    a: `| Aspect      | Array Pointer          | Function Pointer         |
    |-------------|------------------------|--------------------------|
    | Points to   | Data (RAM)             | Code (Flash / .text seg) |
    | Memory seg  | Stack / Heap / BSS     | .text segment            |
    | Operation   | Read / write the value | Call / execute only      |
    | Arithmetic  | Valid                  | Not meaningful           |`
  },
  {
    q: "what is the diffrence a[10] vs (a)[10]?",
    a: `*a[10]   -> [] first, array of pointers
    (*a)[10] -> *  first, pointer to an array

    /* array of pointers */
    int x = 1, y = 2, z = 3;
    int *a[3] = {&x, &y, &z};
    printf("%d\\n", *a[1]);       /* 2 */

    /* pointer to array */
    int arr[10] = {0};
    int (*p)[10] = &arr;
    printf("%d\\n", (*p)[3]);     /* 0 */`
  },
  {
    q: "how to type caste pointer adress?",
    a: `(void *) ptr
    (char *)ptr`
  },
  {
    q: "Explain memory layout in C?",
    a: `High Address
    +---------------------+
    |        Stack        |   Local vars, function frames      (grows ↓)
    +---------------------+
    |    (free space)     |
    +---------------------+
    |        Heap         |   malloc / calloc                  (grows ↑)
    +---------------------+
    |        .BSS         |   Uninitialized globals/statics    (zeroed at startup, RAM)
    +---------------------+
    |        .Data        |   Initialized globals/statics      (FLASH → RAM copy at boot)
    +---------------------+
    |       .rodata       |   const globals, string literals   (FLASH, read-only)
    +---------------------+
    |        .text        |   Machine instructions only        (FLASH, read-only, execute)
    +---------------------+
    Low Address`
  },
  {
    q: "Explain startup code task?",
    a: `in startup  .ro data copied to .data section

    FLASH                              RAM
                                          
    +----------------+                +----------------+
    |   .text        |  (runs here    |                |
    |   .rodata      |   directly,    |                |
    |                |   no copy)     |                |
    +----------------+                +----------------+
    |   .data image  | ─── copy ───►  |   .data        |
    |   speed=100    |   at startup   |   speed=100    |
    +----------------+                +----------------+
                                      |   .bss         |
                            zero ──►  |  (zeroed)      |
                            fill      +----------------+
                                      |   Heap / Stack |
                                     +----------------+

#### what are the Compilation Stages
    .c --> [Preprocessor] --> .i --> [Compiler] --> .s --> [Assembler] --> .o --> [Linker] --> .elf/.bin/.hex

    Stage          Input    Output   Job
    -----------    -----    ------   -------------------------------------------
    Preprocessor   .c       .i       Expand macros, ###include, ###ifdef, remove comments
    Compiler       .i       .s       Generate assembly (syntax + semantic check)
    Assembler      .s       .o       Generate machine code object file
    Linker         .o       .elf     Resolve symbols, link libs, apply memory map`
  },
  {
    q: "Difference between .bin, .hex, and .elf?",
    a: `Format   Description                          Used For
    ------   ----------------------------------   --------------------
    .bin     Raw binary bytes                     Direct flash write
    .hex     Intel HEX (ASCII + address + CRC)    Most programmers
    .elf     With debug symbols                   GDB debugging
    .mot     Motorola S-Record                    Automotive tools`
  },
  {
    q: "Bootup sequence?",
    a: `Power ON / Reset
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
                ⚠️  Must NEVER return in embedded systems!`
  },
  {
    q: "What is a Reset Vector?",
    a: `Fixed memory address the CPU fetches and jumps to after reset.
    On ARM Cortex-M:
        0x00000000 = initial Stack Pointer value
        0x00000004 = Reset Handler address (start of startup code)`
  },
  {
    q: "Embedded System Startup Flow or reset to main or power on?",
    a: `- **Reset Vector**: CPU fetches the reset vector, which points to the startup code (written in assembly).
- **Startup Code**:
  - Sets up the **stack pointer**.
  - Copies initialized variables from **FLASH to RAM** (\`.data\` section).
  - Zeros out uninitialized variables (\`.bss\` section).
- **SystemInit()**: Configures system clocks and hardware setup.
- **main()**: Application entry point.  
  - In embedded systems, \`main()\` should **never return**.`
  },
  {
    q: "Dynamic Memory Allocation?",
    a: `malloc(size)        allocate, memory is UNINITIALIZED (garbage)
    calloc(n, size)     allocate n items, memory is ZERO-INITIALIZED
    realloc(ptr, size)  resize existing allocation (may move memory)
    free(ptr)           release -- always set ptr = NULL after!`
  },
  {
    q: "how to create our own malloc, my malloc?",
    a: `simply create statci int char[500] --> this will exceeds data segment and cross heap section
    we cant use pointer like assigning heap adress to ptr, next moment if we use malloca this adress wil be occupied`
  },
  {
    q: "What is a memory leak? How to detect?",
    a: `void leak(void) {
        int *ptr = malloc(100);
        return;   // forgot free() --> heap shrinks on every call
    }             //                --> eventually malloc returns NULL --> crash

    Fix: always pair malloc with free:
        int *ptr = malloc(100);
        if (ptr == NULL) return;
        // ... use ptr ...
        free(ptr);
        ptr = NULL;`
  },
  {
    q: "Why is malloc avoided in safety-critical embedded?",
    a: `- Non-deterministic timing (MISRA C rule violation)
    - Heap fragmentation over time
    - Memory leaks cause silent failure
    - Limited RAM on MCU gets exhausted unpredictably

    Alternative -- static memory pool:

        uint8_t pool[NUM_BUFS][BUF_SIZE];
        uint8_t inUse[NUM_BUFS] = {0};`
  },
  {
    q: "What is interrupt latency?",
    a: `Time from interrupt signal assertion to first ISR instruction executing.
    Factors: CPU pipeline flush, saving context (stacking registers), priority.
    ARM Cortex-M3: typically 12 clock cycles minimum latency.`
  },
  {
    q: "What is a race condition between ISR and main? How to fix?",
    a: `Problem:
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
        __enable_irq();`
  },
  {
    q: "What is interrupt priority and nesting?",
    a: `Higher priority interrupts can preempt lower priority ISRs.
    ARM Cortex-M: lower number = higher priority (0 = highest).
    Configured via NVIC (Nested Vectored Interrupt Controller).

        NVIC_SetPriority(UART1_IRQn, 1);   // high priority
        NVIC_SetPriority(TIM2_IRQn,  5);   // lower priority`
  },
  {
    q: "Whats is NVIC Table?",
    a: `| Letter | Full Word  | What It Does                                           |
    |--------|------------|--------------------------------------------------------|
    | N      | Nested     | Higher priority IRQ can interrupt a lower priority ISR |
    | V      | Vectored   | Each interrupt has a fixed address in the vector table |
    | I      | Interrupt  | Handles hardware interrupt signals from peripherals    |
    | C      | Controller | Hardware block that manages priorities, enabling, pending |`
  },
  {
    q: "Dynamic memory allocation?",
    a: `// 1. malloc — allocates raw uninitialized memory
    int *ptr = malloc(sizeof(int));          // contents are garbage

    // 2. calloc — allocates AND zero-initializes
    int *ptr = calloc(100, sizeof(int));     // 100 ints, all set to 0

    // 3. realloc — resize an existing allocation
    ptr = realloc(ptr, 200 * sizeof(int));   // grow/shrink, may move ptr

    // 4. free — release back to heap
    free(ptr);                               // how does it know the size? ↓

    Note:When you call malloc(100), the allocator doesn't just give you 100 bytes. 
        It secretly allocates a metadata block just before your pointer:`
  },
  {
    q: "Watchdog Timer?",
    a: `Hardware timer that resets the MCU if not kicked within a timeout.
    Detects software hangs and crashes.
    Essential for unattended and safety-critical systems.`
  },
  {
    q: "RTOS Concepts?",
    a: `RTOS = Real-Time Operating System
    Schedules multiple tasks with deterministic timing.
    Guarantees response within a deadline.`
  },
  {
    q: "Sempahore?",
    a: `in rtos, a semaphore is a syxbronization mechanism used to manage access to shared resource and cororinates task. 
semaphore helps prevent issues like race condtion and deadlock in multi tasking 
enviranioment by ensuring that only a specified number of task can access a resource at time.

exammple:
 Parking Lot with N slots Multiple people can enter (up to N slots).  ANY person can signal (release a slot). When slots = 0, everyone WAITS.`
  },
  {
    q: "Mutexes:?",
    a: `in rtos and multithreadifn environment, a mutex is asyncornization mecanism that prevent multiple task or thread from acess that same shared reosurce at asame trime/
    how mutex works:
    a mutex act like lock.a task must aquire the lock the mutex before access the shared resoucre.
    once the a task finsihed using the resoucrece, it release(unlcok) the mutx allowing other task to acess it.
    if another task tries to aquire the mutex while its locked, it has to wait untill the mutex is relases
Example:
Toilet with 1 key 🚽, Only 1 person can enter at a time. The SAME person who locked must unlock.`
  },
  {
    q: "Difference between mutex and semaphore?",
    a: `Feature              Mutex                         Semaphore
    ----------------     --------------------------    ----------------------
    Ownership            Owned by locking task         No ownership
    Priority inversion   Protected                     Not protected
    Use case             Mutual exclusion (shared data) Signaling

    xSemaphoreTake(mutex, portMAX_DELAY);
    sharedBuffer[0] = 42;   // critical section
    xSemaphoreGive(mutex);`
  },
  {
    q: "Difference between a Process and a thread?",
    a: `Process (one program running)
    │
    ├── Shared: heap, globals, code, file descriptors
    │
    ├── Thread 1 → own stack, PC, registers
    ├── Thread 2 → own stack, PC, registers
    └── Thread 3 → own stack, PC, registers`
  },
  {
    q: "What is priority inversion? How is it solved?",
    a: `Scenario:
    - Low-priority task holds mutex
    - High-priority task needs that mutex -- blocks
    - Medium-priority task runs instead (doesn't need mutex)
    - High-priority task effectively runs at low priority

    Solution: Priority Inheritance
    - Temporarily boost low-priority task to match high-priority waiter
    - FreeRTOS mutexes support this automatically`
  },
  {
    q: "What is a deadlock? How to avoid it?",
    a: `Task A holds Mutex1, waits for Mutex2.
    Task B holds Mutex2, waits for Mutex1.
    Both block forever --> deadlock.

    Prevention:
    - Always acquire mutexes in the SAME ORDER across all tasks
    - Use timeouts instead of blocking forever
    - Minimize number of mutexes held at the same time`
  },
  {
    q: "Difference between UART, SPI, CAN, I2C?",
    a: `Feature          UART               SPI                      I2C                      CAN
    -----------      ----------------   ----------------------   ----------------------   ----------------------
    Wires            2 (TX, RX)         4 (MOSI,MISO,SCK,CS)     2 (SDA, SCL)             2 (CANH, CANL)
    Speed            up to ~5 Mbps      up to 100mhz            100k / 400k / 1MHz/3mhz       125k / 250k / 500k / 1Mbps
    Topology         Point-to-point     1 master, multi slave    Multi master+slave        Multi master (bus)
    Addressing       None               Chip Select per slave    7-bit address             11-bit / 29-bit ID
    Synchronous      No (async)         Yes                      Yes                      No (async)
    Error handling   None               None                     ACK only                 CRC, ACK, error frames
    Use case         Debug, GPS, BT     Flash, ADC, display      Sensors, EEPROM           Automotive ECUs, OBD`
  },
  {
    q: "What is I2C clock stretching?",
    a: `Slave holds SCL line LOW to pause the master while preparing data.
    Master must wait until slave releases SCL.
    Some I2C masters do not support clock stretching -- check datasheet!`
  },
  {
    q: "i2c Communication?",
    a: `+-------+----------+---+----------+---+--------+---+---+
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

#### what is i2c clock Speed

    Mode            Speed       Notes
    -----------     --------    ---------------------------
    Standard        100 kHz     All devices supported
    Fast            400 kHz     MPU-6050, SSD1306 supported
    Fast mode+      1 MHz       SSD1306 (some variants)
    High speed      3.4 MHz     Rare, special hw needed

    Pull-up resistors:
    100 kHz  ->  4.7 kohm typical
    400 kHz  ->  2.2 kohm typical
    1 MHz    ->  1.0 kohm typical`
  },
  {
    q: "what is Dominat and reccesive?",
    a: `Differential signaling on CAN_H and CAN_L lines:

State       CAN_H       CAN_L       Differential (H-L)
---------   -------     -------     ------------------
Dominant    3.5 V       1.5 V       +2.0 V  (logic 0)
Recessive   2.5 V       2.5 V        0.0 V  (logic 1)

Dominant wins on bus (wired-AND): any node sending 0 pulls bus dominant.`
  },
  {
    q: "Expalin CAN frame?",
    a: `---
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

---`
  },
  {
    q: "UART Communication?",
    a: `One UART frame = 1 start bit + data bits + optional parity + stop bit(s)

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

---`
  },
  {
    q: "what are the ADC Formulas?",
    a: `Resolution = Vref / 2^n

    Example — 12-bit ADC:

    Resolution = 5V / 4096 = 1.22 mV

    Vout = (ADC_value / (2^n - 1)) x Vref
    \`\`\`

    - \`ADC_value\` — raw ADC output (0 to 4095 for 12-bit)
    - \`2^n - 1\` — max count = 4095
    - \`Vref\` — reference voltage = 5V

    Examples:

    | ADC Value | Calculation         | Result      |
    |-----------|---------------------|-------------|
    | 4095      | 4095 x 5 / 4095     | 5.00 V (max)|
    | 2048      | 2048 x 5 / 4095     | ~2.50 V     |
    | 0         | 0 x 5 / 4095        | 0.00 V (min)|`
  },
  {
    q: "ADC groups w.r.t AUTOSAR?",
    a: `ADC Groups
    AUTOSAR organizes ADC channels into Groups
    
    Group is a collection of one or more channels that are converted together.
    Each group has a trigger source (SW or HW)
    Each group has a conversion mode (one-shot or continuous)
    Each group has a result buffer (linear or circular)

    2. Conversion Modes
    Mode          Description
    One-shot       Single conversion per trigger, then stops
    Continuous     Keeps converting in a loop until explicitly stopped
    Scan           Converts all channels in the group sequentially

    3. Trigger Sources
    Trigger Source        Macro / Config Value      Description
    Software trigger      ADC_TRIGG_SRC_SW          Trigger via Adc_StartGroupConversion()
    Hardware trigger       ADC_TRIGG_SRC_HW         Timer, PWM event, or external pin

    4. Notification (Callback)
    Each group can have a notification function (callback) registered in configuration.
    It is called at end-of-conversion (similar to an ISR-driven callback).
    /* Example notification function prototype */
    void AdcGroup0_ConversionComplete(void);`
  },
  {
    q: "ADC API Reference?",
    a: `SW TRIGGERED FLOW
    Adc_Init(&AdcConfig)
        |
        v
Adc_SetupResultBuffer(Group0, resultBuffer)
// Tells the ADC driver where to store conversion results.
// Links Group0 to your result array in RAM.
        |
        v
Adc_EnableGroupNotification(Group0)
// Registers a callback to fire when Group0 conversion completes.
// Enables interrupt-based notification instead of polling.
        |
        v
Adc_StartGroupConversion(Group0)
// Triggers the ADC hardware to begin sampling all channels in Group0.
// Software initiates the conversion (SW-triggered mode).
        |
        v
    [HW converts all channels in Group0]
// ADC hardware samples each channel sequentially/simultaneously.
// Stores raw digital results into the linked resultBuffer.
        |
        v
    [Notification callback fires]
// ISR or callback function is invoked automatically by the driver.
// Signals application that all Group0 results are ready to read.
        |
        v
Adc_ReadGroup(Group0, resultBuffer)
// Copies converted ADC values from driver buffer into application buffer.
// Returns status; resultBuffer now holds valid channel readings.
        |
        v
    Use result in application logic
// Process ADC values: scaling, threshold check, control decisions, etc.
// e.g., temperature = (resultBuffer[0] * VREF) / ADC_RESOLUTION`
  },
  {
    q: "AUTOSAR SPI Key Concepts?",
    a: `Master                          Slave
    ------                          -----
    SCLK  -----------------------------> SCLK
    MOSI  -----------------------------> MOSI
    MISO  <----------------------------- MISO
    CS    -----------------------------> CS
    GND   ------------------------------ GND

    CS pulled LOW by master to select slave.

- **Channel** — Basic data unit. Holds a buffer of data elements to be transferred.
- **Job** — A sequence of one or more Channels sharing the same CS (Chip Select).
- **Sequence** — A group of one or more Jobs. Unit of transmission triggered by SW.
- **EB Buffer** — External Buffer; pointer to user-provided RAM buffer (dynamic).
- **IB Buffer** — Internal Buffer; statically allocated inside the SPI driver.
- **Hw Unit** — Physical SPI peripheral (e.g., QSPI0, QSPI2 on AURIX TriCore).`
  },
  {
    q: "List SPI MODES?",
    a: `SPI Modes (CPOL + CPHA)
\`\`\`
| Mode | CPOL | CPHA | Clock Idle | Sample On    |
|------|------|------|------------|--------------|
|  0   |  0   |  0   |    LOW     | Rising edge  |
|  1   |  0   |  1   |    LOW     | Falling edge |
|  2   |  1   |  0   |    HIGH    | Falling edge |
|  3   |  1   |  1   |    HIGH    | Rising edge  |
\`\`\``
  },
  {
    q: "What is SPI Synchronous vs Asynchronous or trnasimission mode?",
    a: `SPI bus is always clocked, hardware sync is not negotiable
    Sync vs Async is a software architecture choice, not a hardware one
    DMA frees CPU but driver design decides if SW is truly async
    Best architecture is async driver as base with sync wrapper on top
    In RTOS, task pends on semaphore, ISR gives on transfer complete
    Prefer sync for boot sequences, short commands, and simple debug scenarios
    Prefer async with DMA for flash bulk ops, frame buffers, and RTOS multitasking`
  },
  {
    q: "list SPI API?",
    a: `SPI SW TRIGGERED FLOW
    Spi_Init(&SpiConfig)
        |
        v
Spi_SetupEB(Channel0, srcBuffer, destBuffer, length)
// Tells the SPI driver source (TX) and destination (RX) buffers.
// Links Channel0 to your data arrays in RAM with transfer length.
        |
        v
Spi_EnableJobNotification(Job0)
// Registers a callback to fire when Job0 transmission completes.
// Enables interrupt-based notification instead of polling.
        |
        v
Spi_AsyncTransmit(Sequence0)
// Triggers the SPI hardware to begin transmitting Sequence0.
// Software initiates the transfer (SW-triggered async mode).
        |
        v
    [HW transmits all channels in Sequence0]
// SPI hardware shifts out TX bytes and simultaneously captures RX bytes.
// Handles chip select (CS) assertion/de-assertion automatically per job.
        |
        v
    [Job/Sequence notification callback fires]
// ISR or callback function is invoked automatically by the driver.
// Signals application that all Sequence0 bytes are sent and received.
        |
        v
Spi_ReadIB(Channel0, destBuffer)
// Copies received SPI bytes from driver internal buffer to app buffer.
// Returns status; destBuffer now holds valid RX data from slave device.
        |
        v
    Use result in application logic
// Process RX data: parse sensor response, decode register values, etc.
// e.g., sensorVal = (destBuffer[0] << 8) | destBuffer[1]`
  },
  {
    q: "what is SPI Synchronous vs Asynchronous ?",
    a: `| #  | Point                                                                              |
|----|------------------------------------------------------------------------------------|
| 1  | SPI bus is always clocked, hardware sync is not negotiable                         |
| 2  | Sync vs Async is a software architecture choice, not a hardware one                |
| 3  | DMA frees CPU but driver design decides if SW is truly async                       |
| 4  | Best architecture is async driver as base with sync wrapper on top                 |
| 5  | In RTOS, task pends on semaphore, ISR gives on transfer complete                   |
| 6  | Prefer sync for boot sequences, short commands, and simple debug scenarios         |
| 7  | Prefer async with DMA for flash bulk ops, frame buffers, and RTOS multitasking     |`
  },
  {
    q: "what is inheritance?",
    a: `Inheritance   = child gets parent's properties and methods`
  },
  {
    q: "MCU?",
    a: `Diffrenc between timer and counter
Timer   = counts internal clock pulses  (measures TIME)
Counter = counts external event pulses  (measures EVENTS)`
  },
  {
    q: "what is my Linux OS Road map?",
    a: `| Phase   | File             | Concepts                                  |
|---------|------------------|-------------------------------------------|
| Phase 1 | \`lo_mutex.c\`     | Mutex, threads, race conditions           |
| Phase 1 | \`lo_semaphore.c\` | Semaphore, shared memory, fork            |
| Phase 1 | \`lo_process.c\`   | fork, wait, waitpid, execvp, exit         |
| Phase 1 | \`lo_threads.c\`   | pthread_create, join, exit, return values |
| Phase 1 | \`lo_sharedmem.c\` | mmap, sem_init, shared structures         |
| Phase 2 | \`lo_pipe.c\`      | Pipes with fork                           |
| Phase 2 | \`lo_fifo.c\`      | Named pipes (FIFO)                        |
| Phase 2 | \`lo_msqueue.c\`   | Message queues                            |
| Phase 2 | \`lo_socket.c\`    | Sockets (do this last)                    |
| Phase 3 | \`lo_malloc.c\`    | malloc/free internals                     |
| Phase 3 | \`lo_stack_heap.c\`| Stack vs Heap                             |
| Phase 3 | \`lo_mmap.c\`      | Memory-mapped files                       |
| Phase 4 | \`lo_fileio.c\`    | File I/O (open, read, write, close)       |
| Phase 4 | \`lo_dirops.c\`    | Directory operations                      |
| Phase 4 | \`lo_filestat.c\`  | File metadata (stat)                      |
| Phase 5 | \`lo_signals.c\`   | Signal basics                             |
| Phase 5 | \`lo_sigaction.c\` | sigaction, custom handlers                |
| Phase 6 | \`lo_prodcons.c\`  | Producer–Consumer problem                 |
| Phase 6 | \`lo_readwrite.c\` | Readers–Writers problem                   |
| Phase 6 | \`lo_deadlock.c\`  | Deadlock detection                        |
| Phase 6 | \`lo_dining.c\`    | Dining Philosophers problem               |`
  },
  {
    q: "intrduction about myself?",
    a: `"Hi, I am Sudhir Acharya. 
I have over 11 years of experience in Embedded C, with a strong focus on the Automotive domain — specifically in the MCAL layer.
My core work has been in MCAL driver development, testing, and integration. 
I have hands-on experience with microcontrollers from Infineon, NXP, and STMicroelectronics.
On the tools side, I have worked with LAUTERBACH TRACE32 for software debugging, Logic Analyzers for signal-level analysis, and CANoe for automotive communication testing.
From a quality and compliance perspective, I have experience with ASPICE process requirements and MISRA C coding guidelines,`
  },
  {
    q: "how ro generate final html file?",
    a: `run this
@sudheerpaniyur ➜ /workspaces/vscpde_c_practice (main) $ chmod +x generate_html.sh
@sudheerpaniyur ➜ /workspaces/vscpde_c_practice (main) $ bash generate_html.sh

##### AI prompt
The source is HTML content containing:`
  },
  {
    q: "intrduction about myself?",
    a: `theory
Source code files
Use ONLY the provided content.
Do NOT generate any new theory, explanations, or code.
Do NOT add extra examples.
Only format and organize the existing content.
FORMAT REQUIREMENTS:
Page size: A4
Color: Strictly black and white (printer-friendly)
Fonts:
Serif or sans-serif for normal text
Monospace for code
Margins: 2.5 cm on all sides
Page numbers: Bottom center
Optional: Chapter title in header
COVER PAGE:
Title: C Programming Notes & Practice
Subtitle: Beginner to Intermediate Guide
Author: Sudhir Acharya
Center-aligned layout
Minimal, clean design
Must appear on a separate page
STRUCTURE:
Generate a Table of Contents based only on the provided content
Do NOT create or invent new chapters
Use file names or sections from README.md as chapter titles
THEORY SECTIONS (FROM README.md ONLY):
Preserve the original text exactly (no rewriting)
Maintain headings and formatting
Keep bullet points and spacing intact
Ensure tables remain aligned and readable
Do NOT split tables across pages
CODE SECTIONS:
Each program must start on a new page
Do NOT split any program across pages
Preserve code exactly (no modifications)
Use a monospace font
Add a heading:
Program: <filename>
Place code inside a thin bordered box
PAGE LAYOUT RULES:
Avoid awkward page breaks
Keep headings with their content
Maintain consistent spacing throughout
Ensure clean readability for printing
OUTPUT:
A clean, print-ready PDF
Structured like a professional textbook or notebook
Must strictly use only the provided content (no additions)
---

 ### list of future Questions
 Interview Preparation Checklist
🔢 Array Problems
Basic

 Maximum subarray sum (Kadane's Algorithm)
 Move zeros to end
 Remove duplicates from sorted array
 Sort 0s and 1s (Dutch flag - 2 elements)
 Sort 0s, 1s and 2s (Dutch flag - 3 elements)
 Reverse an array
 Find max and min in array
 Second largest element

Intermediate

 Two sum (find pair with given sum)
 Subarray with given sum
 Rotate array by K positions
 Merge two sorted arrays
 Find missing number (1 to N)
 Majority element (appears > N/2 times)
 Best time to buy & sell stock
 Trapping rain water

🔤 String Problems
Basic

 Reverse a string
 Check palindrome
 Count vowels/consonants
 Remove duplicates from string
 Check anagram

Intermediate

 Longest substring without repeating characters
 String compression (aaabbb → a3b3)
 Valid parentheses
 First non-repeating character
 Reverse words in a sentence

🔗 Linked List

 Reverse a linked list
 Detect cycle (Floyd's algorithm)
 Find middle of linked list
 Merge two sorted linked lists
 Remove Nth node from end
 Intersection of two linked lists

📚 Stack & Queue

 Implement stack using array/queue
 Valid parentheses using stack
 Next greater element
 Min stack (getMin in O(1))
 Implement queue using two stacks

🌳 Trees

 Inorder / Preorder / Postorder traversal
 Height of binary tree
 Level order traversal (BFS)
 Check if binary tree is BST
 Lowest common ancestor
 Diameter of binary tree

🔍 Searching & Sorting

 Binary search
 Binary search on rotated array
 Bubble / Selection / Insertion sort
 Merge sort
 Quick sort
 Find first and last position of element

💡 Dynamic Programming (Basics)

 Fibonacci (memoization vs tabulation)
 0/1 Knapsack
 Longest Common Subsequence
 Longest Increasing Subsequence
 Coin change problem
 Climbing stairs

⚙️ Bit Manipulation (Important for Semiconductor!)

 Next power of 2 ✅
 Check if number is power of 2
 Count set bits (Hamming weight)
 Find only odd-occurring number (XOR trick)
 Swap two numbers without temp variable
 Find the two non-repeating numbers
 Set / Clear / Toggle a specific bit
 Reverse bits of a number

🧮 Math & Number Theory

 Check prime number
 GCD / LCM (Euclidean algorithm)
 Reverse a number
 Check Armstrong number
 Sieve of Eratosthenes (all primes up to N)
 Integer overflow detection

🏭 Semiconductor / Embedded Specific

 Implement a circular buffer / ring buffer
 Endianness check (big vs little endian)
 Memory alignment concepts
 Bitfield manipulation in structs
 Fixed-point arithmetic
 CRC checksum basic concept
 Interrupt-safe data structures (volatile, atomic)`
  },
  {
    q: "Write array_ptr code?",
    a: `#include <stdio.h>

int main()
{
    int a[]={2,3,5,6};
    int (*ptr)[]=&a;
    int n=sizeof(a)/sizeof(a[0]);
    
    for( int  i=0; i<n ;i++)
    {
        printf("%d",(*ptr)[i]);
    }


    return 0;
}`
  },
  {
    q: "Write bitfield code?",
    a: `#include <stdio.h>
#include <stdint.h>

struct EngineStatus {
    uint8_t engine_on   : 1;   /* bit 0 — 0 or 1 */
    uint8_t gear        : 3;   /* bits 1-3 — 0 to 7 */
    uint8_t error_code  : 4;   /* bits 4-7 — 0 to 15 */
};

int main() {
    struct EngineStatus status = {0};

    status.engine_on  = 1;
    status.gear       = 5;
    status.error_code = 3;

    printf("Engine on  : %d\\n", status.engine_on);
    printf("Gear       : %d\\n", status.gear);
    printf("Error code : %d\\n", status.error_code);
    printf("Size       : %zu byte\\n", sizeof(status));

    return 0;
}`
  },
  {
    q: "Write callbcakfunction code?",
    a: `#include <stdio.h>
#include <stdlib.h>

void add(int a, int b)
{
    int c=a+b;
    printf("addition :%d \\n", c);
}


//(*xyz)(int, int) --> function pointer
void calulcate(int a, int b, void (*xyz)(int, int))
{
    xyz(a,b);

}

int main()
{
    calulcate(3, 2, add);
    return 0;

}`
  },
  {
    q: "Write enum code?",
    a: `#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    SUN,
    MON,
    TUE
}WEEKDAY;

int main(void)
{

    WEEKDAY today;

    today=TUE;
    printf("today:%d \\n", today);

    return 0;
}`
  },
  {
    q: "Write fun_struct code?",
    a: `#include <stdio.h>


//fucntion inside structure
typedef struct {
    int x;
    int y;
    int (*add)(int a, int b);
} Calc;

int do_add(int a, int b)
 { 
 return a + b; 
 }
 
 
int main(void) {

    /* 1 */
    Calc c = { .x = 3, .y = 4, .add = do_add };
    printf("add = %d\\n", c.add(c.x, c.y));      /* add = 7 */
	
	}`
  },
  {
    q: "Write function_ptr code?",
    a: `#include <stdio.h>
#include <stdlib.h>

void add(int a, int b)
{
    int c= a+b;
    printf("addition %d \\n", c);
}
void sub(int a, int b)
{
    int c= a-b;
    printf("sub %d\\n", c);
}
int main()
{
    void (*ptr)(int, int) = add;
    ptr = add;
    ptr(3,2);

    return 0;

}`
  },
  {
    q: "Write getchar code?",
    a: `#include <stdio.h>
#include <stdint.h>
// enter date of birth and print
int getnum()
{
    int num;
    int value = 0;

    do {
        num = getchar();
        if (num >= '0' && num <= '9') {
            value = value * 10 + (num - '0');
        }
    } while (num != '\\n' && num != EOF);// EOF END OF FILE

    return value;
}

int main()
{
    printf("dob %d\\n", getnum());
    return 0;
}`
  },
  {
    q: "Write inlinefun code?",
    a: `#include <stdio.h>
#include <stdlib.h>

// Benefits: Reduces function call overhead (no pushing arguments/return addresses to the stack).
// Drawbacks: Excessive inlining can cause "code bloat" (larger binary size) and may increase cache misses.

// If you comment out the inline function and use a normal function call,
// you can observe changes in RBP and RSP (stack frame setup).
// With a normal function, the compiler generates prologue/epilogue code (push/pop).
// With inline, there is no function call overhead — the code is expanded directly.

// In Visual Studio, you may not see a difference because the compiler optimizes differently.
// In Eclipse/GCC, you can see the difference at compile time by commenting/uncommenting the inline function.
// In assembly, without inline you will see push/pop instructions for the function call.
// With inline, those push/pop operations disappear since the function body is inserted directly.

inline int add(int a, int b) __attribute__((always_inline));


__attribute__((always_inline)) inline int add(int a, int b) {
    int c;
   return c=a+b;
 


}
int main()
{

    int a=10, b=20;
    printf("result %d \\n", add(a,b));
    // printf("result %d \\n", add(a,b));

    return 0;
}`
  },
  {
    q: "Write lo_mutex code?",
    a: `#include <stdio.h>      // For printf()
#include <pthread.h>    // For pthread functions (threads, mutex)


//commnd for running
/*
@sudhirvacharya ➜ /workspaces/vscpde_c_practice (main) $ gcc -o mutex_example mutex_example.c -lpthread
@sudhirvacharya ➜ /workspaces/vscpde_c_practice (main) $ ./mutex_example
Final counter: 200000

*/
/* 
 * Mutex (Mutual Exclusion Lock)
 * Think of it like a TOILET LOCK 🚽
 * Only ONE person (thread) can use it at a time.
 * Others WAIT outside until the lock is released.
 */
pthread_mutex_t lock;

/*
 * This is the SHARED variable — both threads will try to
 * increment this at the same time. Without mutex, they
 * would corrupt each other's work (race condition).
 */
int shared_counter = 0;


/*
 * -------------------------------------------------------
 * THREAD FUNCTION: increment()
 * -------------------------------------------------------
 * This function runs INSIDE a thread.
 * Both Thread 1 and Thread 2 will run this same function.
 *
 * void* arg  → input  (we are not passing anything, so NULL)
 * void*      → output (we are not returning anything, so NULL)
 * -------------------------------------------------------
 */
void* increment(void* arg) {

    /* Loop 100,000 times and increment the shared counter */
    for (int i = 0; i < 100000; i++) {

        /*
         * LOCK the mutex before touching shared_counter.
         * If another thread already has the lock,
         * THIS thread will WAIT here until it's free.
         */
        pthread_mutex_lock(&lock);

        /*
         * CRITICAL SECTION — only ONE thread runs this at a time.
         * Safe to modify shared_counter here.
         */
        shared_counter++;

        /*
         * UNLOCK the mutex so the other thread can now
         * enter the critical section.
         */
        pthread_mutex_unlock(&lock);

    } // end of for loop

    return NULL; // Thread finished, return nothing
}


/*
 * -------------------------------------------------------
 * MAIN FUNCTION
 * -------------------------------------------------------
 * Program starts here.
 * We create 2 threads and wait for them to finish.
 * -------------------------------------------------------
 */
int main() {

    /*
     * pthread_t = Thread ID / Handle
     * t1 and t2 represent our two threads.
     * Think of them like two workers.
     */
    pthread_t t1, t2;

    /*
     * INITIALIZE the mutex before using it.
     * NULL = use default settings.
     * Always do this BEFORE creating threads.
     */
    pthread_mutex_init(&lock, NULL);

    /*
     * CREATE Thread 1
     * → It will start running increment() immediately.
     * Arguments:
     *   &t1        = store thread ID here
     *   NULL       = default thread settings
     *   increment  = function to run in the thread
     *   NULL       = no argument to pass to increment()
     */
    pthread_create(&t1, NULL, increment, NULL);

    /*
     * CREATE Thread 2
     * → It also runs increment() at the same time as Thread 1.
     * Both threads now run SIMULTANEOUSLY (parallel).
     */
    pthread_create(&t2, NULL, increment, NULL);

    /*
     * WAIT for Thread 1 to finish before moving on.
     * Without this, main() might exit before threads are done!
     * NULL = we don't care about thread's return value.
     */
    pthread_join(t1, NULL);

    /*
     * WAIT for Thread 2 to finish.
     */
    pthread_join(t2, NULL);

    /*
     * DESTROY the mutex after we are done using it.
     * Frees up the resources used by the mutex.
     * Always clean up what you initialize!
     */
    pthread_mutex_destroy(&lock);

    /*
     * Print the final result.
     * Since both threads did 100,000 increments each:
     * Expected result = 100,000 + 100,000 = 200,000
     * Thanks to mutex, the answer will always be correct!
     */
    printf("Final counter: %d\\n", shared_counter);

    return 0; // Program ended successfully
}

/*

Simple mental model to remember:
Mutex = Toilet Lock 🚽

Thread 1 enters → LOCKS door → does work → UNLOCKS door
Thread 2 arrives → sees LOCKED → WAITS → enters when free
Without Mutex ❌         With Mutex ✅
─────────────────        ─────────────────
Both read  → 5           T1 reads  → 5
Both write → 6           T1 writes → 6
Lost one increment!      T2 reads  → 6
Result: WRONG            T2 writes → 7
                         Result: CORRECT


                         main() starts
│
├── pthread_create(&t1, ..., increment, ...)
│       └── OS creates Thread 1 → starts running increment()
│               └── loops 100000 times, locking/unlocking mutex
│
├── pthread_create(&t2, ..., increment, ...)
│       └── OS creates Thread 2 → starts running increment()
│               └── loops 100000 times, locking/unlocking mutex
│
├── pthread_join(t1) → main BLOCKS here until Thread 1 finishes
├── pthread_join(t2) → main BLOCKS here until Thread 2 finishes
│
└── prints final counter = 200000

*/`
  },
  {
    q: "Write lo_process code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>      // fork(), getpid(), getppid(), exec()
#include <sys/wait.h>    // wait(), waitpid()
#include <sys/types.h>   // pid_t
/*
CMD FOR EXECUTING
gcc -o lo_process lo_process.c
./lo_process

/*
========================================
  lo_process.c — Process Management
========================================
Main process PID: 5001

===== DEMO 1: Basic fork() =====
PARENT: I am parent! My PID = 5001
PARENT: I created child with PID = 5002
CHILD : I am child!  My PID = 5002
CHILD : My parent's PID = 5001
PARENT: Child finished!

===== DEMO 2: Multiple Children =====
CHILD 1 (PID 5003): Working...
CHILD 2 (PID 5004): Working...
CHILD 1 (PID 5003): Done!
PARENT: Waiting for Child 1 (PID 5003)...
PARENT: Child 1 finished!
PARENT: Waiting for Child 2 (PID 5004)...
CHILD 2 (PID 5004): Done!
PARENT: Child 2 finished!
PARENT: All children done!

===== DEMO 3: Exit Status =====
CHILD : Exiting with status 42
PARENT: Child exited with code = 42

===== DEMO 4: execvp() =====
CHILD : About to exec 'ls -l'
total 24
-rwxr-xr-x 1 user user 16832 Apr 20 10:00 lo_process
-rw-r--r-- 1 user user  3200 Apr 20 10:00 lo_process.c
PARENT: exec child finished!

===== ALL DEMOS COMPLETE =====

/*
 * FILE: lo_process.c
 * TOPIC: Linux OS — Process Management
 * COVERS:
 *   1. fork()     — create child process
 *   2. getpid()   — get current process ID
 *   3. getppid()  — get parent process ID
 *   4. wait()     — parent waits for child
 *   5. waitpid()  — wait for specific child
 *   6. exit()     — terminate process
 *   7. execvp()   — replace process with new program
 *
 * COMPILE: gcc -o lo_process lo_process.c
 * RUN:     ./lo_process
 */

/*
 * ─────────────────────────────────────────
 * MENTAL MODEL
 * ─────────────────────────────────────────
 *
 *   fork() = PHOTOCOPIER 🖨️
 *   Parent = original document
 *   Child  = exact copy
 *   Both run independently after copy!
 *
 *   PROCESS TREE:
 *
 *   main (Parent)
 *       │
 *       ├── fork() ──→ Child 1
 *       │                  └── does work → exit(0)
 *       │
 *       ├── fork() ──→ Child 2
 *       │                  └── does work → exit(0)
 *       │
 *       └── wait() for both → prints final result
 *
 * ─────────────────────────────────────────
 */


/* -----------------------------------------------
 * DEMO 1: Basic fork() — parent and child
 * ----------------------------------------------- */
void demo_basic_fork() {
    printf("\\n===== DEMO 1: Basic fork() =====\\n");

    pid_t pid = fork();   // creates child process here

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        exit(1);
    }

    else if (pid == 0) {
        /*
         * CHILD PROCESS
         * pid == 0 means "I am the child"
         */
        printf("CHILD : I am child!  My PID = %d\\n", getpid());
        printf("CHILD : My parent's PID = %d\\n", getppid());
        exit(0);   // child done
    }

    else {
        /*
         * PARENT PROCESS
         * pid > 0 means "I am the parent, child PID = pid"
         */
        printf("PARENT: I am parent! My PID = %d\\n", getpid());
        printf("PARENT: I created child with PID = %d\\n", pid);

        wait(NULL);   // wait for child to finish
        printf("PARENT: Child finished!\\n");
    }
}


/* -----------------------------------------------
 * DEMO 2: Multiple children — waitpid()
 * ----------------------------------------------- */
void demo_multiple_children() {
    printf("\\n===== DEMO 2: Multiple Children =====\\n");

    pid_t child1, child2;

    /* --- Create Child 1 --- */
    child1 = fork();
    if (child1 == 0) {
        printf("CHILD 1 (PID %d): Working...\\n", getpid());
        sleep(1);   // simulate some work
        printf("CHILD 1 (PID %d): Done!\\n", getpid());
        exit(0);
    }

    /* --- Create Child 2 --- */
    child2 = fork();
    if (child2 == 0) {
        printf("CHILD 2 (PID %d): Working...\\n", getpid());
        sleep(2);   // simulate more work
        printf("CHILD 2 (PID %d): Done!\\n", getpid());
        exit(0);
    }

    /*
     * PARENT waits for SPECIFIC child using waitpid()
     * More control than wait() which waits for ANY child
     */
    printf("PARENT: Waiting for Child 1 (PID %d)...\\n", child1);
    waitpid(child1, NULL, 0);
    printf("PARENT: Child 1 finished!\\n");

    printf("PARENT: Waiting for Child 2 (PID %d)...\\n", child2);
    waitpid(child2, NULL, 0);
    printf("PARENT: Child 2 finished!\\n");

    printf("PARENT: All children done!\\n");
}


/* -----------------------------------------------
 * DEMO 3: exit status — child sends code to parent
 * ----------------------------------------------- */
void demo_exit_status() {
    printf("\\n===== DEMO 3: Exit Status =====\\n");

    pid_t pid = fork();

    if (pid == 0) {
        /* Child exits with code 42 */
        printf("CHILD : Exiting with status 42\\n");
        exit(42);
    }

    else {
        int status;

        /*
         * waitpid() with &status captures child's exit code
         * WIFEXITED(status)   → did child exit normally?
         * WEXITSTATUS(status) → what exit code did it use?
         */
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("PARENT: Child exited with code = %d\\n",
                   WEXITSTATUS(status));
        }
    }
}


/* -----------------------------------------------
 * DEMO 4: execvp() — replace process image
 * ----------------------------------------------- */
void demo_exec() {
    printf("\\n===== DEMO 4: execvp() =====\\n");

    pid_t pid = fork();

    if (pid == 0) {
        /*
         * execvp() REPLACES child process with a new program.
         * Here we run the Unix "ls" command from inside C!
         *
         * char *args[] = command + arguments + NULL terminator
         */
        char *args[] = {"ls", "-l", NULL};

        printf("CHILD : About to exec 'ls -l'\\n");

        execvp("ls", args);

        /*
         * If execvp() returns — it FAILED.
         * Normally it never returns (process is replaced).
         */
        perror("execvp failed");
        exit(1);
    }

    else {
        wait(NULL);
        printf("PARENT: exec child finished!\\n");
    }
}


/* -----------------------------------------------
 * MAIN — runs all demos
 * ----------------------------------------------- */
int main() {
    printf("========================================\\n");
    printf("  lo_process.c — Process Management\\n");
    printf("========================================\\n");
    printf("Main process PID: %d\\n", getpid());

    demo_basic_fork();
    demo_multiple_children();
    demo_exit_status();
    demo_exec();

    printf("\\n===== ALL DEMOS COMPLETE =====\\n");
    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ========================================
 *   lo_process.c — Process Management
 * ========================================
 * Main process PID: 1234
 *
 * ===== DEMO 1: Basic fork() =====
 * PARENT: I am parent! My PID = 1234
 * PARENT: I created child with PID = 1235
 * CHILD : I am child!  My PID = 1235
 * CHILD : My parent's PID = 1234
 * PARENT: Child finished!
 *
 * ===== DEMO 2: Multiple Children =====
 * CHILD 1 (PID 1236): Working...
 * CHILD 2 (PID 1237): Working...
 * CHILD 1 (PID 1236): Done!
 * PARENT: Child 1 finished!
 * CHILD 2 (PID 1237): Done!
 * PARENT: Child 2 finished!
 * PARENT: All children done!
 *
 * ===== DEMO 3: Exit Status =====
 * CHILD : Exiting with status 42
 * PARENT: Child exited with code = 42
 *
 * ===== DEMO 4: execvp() =====
 * CHILD : About to exec 'ls -l'
 * [output of ls -l command]
 * PARENT: exec child finished!
 *
 * ===== ALL DEMOS COMPLETE =====
 *
 * ─────────────────────────────────────────
 * QUICK REFERENCE:
 * ─────────────────────────────────────────
 * fork()            → create child process
 * getpid()          → my PID
 * getppid()         → my parent's PID
 * wait(NULL)        → wait for ANY child
 * waitpid(pid,...)  → wait for SPECIFIC child
 * exit(code)        → terminate with code
 * execvp(cmd, args) → replace with new program
 * ─────────────────────────────────────────
 */`
  },
  {
    q: "Write lo_semaphore code?",
    a: `#include <stdio.h>       // For printf()
#include <pthread.h>     // For pthread functions (threads)
#include <semaphore.h>   // For semaphore functions ← NEW HEADER
/*
Compile and run:
gcc -o semaphore_example semaphore_example.c -lpthread
./semaphore_example

*/
/*
 * -------------------------------------------------------
 * SEMAPHORE vs MUTEX — What's the difference?
 * -------------------------------------------------------
 *
 * MUTEX  = Toilet with 1 key 🚽
 *          Only 1 person can enter at a time.
 *          The SAME person who locked must unlock.
 *
 * SEMAPHORE = Parking Lot with N slots 🅿️
 *          Multiple people can enter (up to N slots).
 *          ANY person can signal (release a slot).
 *          When slots = 0, everyone WAITS.
 *
 * In this example we use sem value = 1 (binary semaphore)
 * which behaves similar to a mutex.
 * -------------------------------------------------------
 */
sem_t semaphore;   // Declare a semaphore variable

/*
 * Shared variable — both threads will increment this.
 * Without semaphore, threads corrupt each other (race condition).
 */
int shared_counter = 0;


/*
 * -------------------------------------------------------
 * THREAD FUNCTION: increment()
 * -------------------------------------------------------
 * Both Thread 1 and Thread 2 run this same function.
 * Uses semaphore to protect the shared_counter.
 * -------------------------------------------------------
 */
void* increment(void* arg) {

    /* Loop 100,000 times and increment the shared counter */
    for (int i = 0; i < 100000; i++) {

        /*
         * sem_wait() = "Take a slot from parking lot"
         *
         * → If semaphore value > 0 : decrease by 1, enter
         * → If semaphore value = 0 : WAIT (block) until free
         *
         * This is equivalent to pthread_mutex_lock()
         */
        sem_wait(&semaphore);

        /*
         * CRITICAL SECTION
         * Only ONE thread executes this at a time
         * (because we initialized semaphore to 1)
         */
        shared_counter++;

        /*
         * sem_post() = "Give back a slot to parking lot"
         *
         * → Increases semaphore value by 1
         * → Wakes up any thread that was waiting
         *
         * This is equivalent to pthread_mutex_unlock()
         */
        sem_post(&semaphore);

    } // end of for loop

    return NULL; // Thread finished, return nothing
}


/*
 * -------------------------------------------------------
 * MAIN FUNCTION
 * -------------------------------------------------------
 * Program starts here.
 * We initialize semaphore, create 2 threads, wait for them.
 * -------------------------------------------------------
 */
int main() {

    /*
     * pthread_t = Thread ID / Handle
     * t1 and t2 represent our two threads (two workers).
     */
    pthread_t t1, t2;

    /*
     * INITIALIZE the semaphore before using it.
     *
     * sem_init() Arguments:
     *   &semaphore  = semaphore to initialize
     *   0           = 0 means shared between THREADS
     *                 (1 would mean shared between PROCESSES)
     *   1           = INITIAL VALUE of the semaphore
     *                 (1 = only 1 thread allowed at a time)
     *
     * If you set initial value to 3 → 3 threads can enter at once
     */
    sem_init(&semaphore, 0, 1);

    /*
     * CREATE Thread 1
     * → Starts running increment() immediately
     */
    pthread_create(&t1, NULL, increment, NULL);

    /*
     * CREATE Thread 2
     * → Also runs increment() at the same time as Thread 1
     * Both threads now run SIMULTANEOUSLY (parallel)
     */
    pthread_create(&t2, NULL, increment, NULL);

    /*
     * WAIT for Thread 1 to finish.
     * Without this, main() might exit before threads complete!
     */
    pthread_join(t1, NULL);

    /*
     * WAIT for Thread 2 to finish.
     */
    pthread_join(t2, NULL);

    /*
     * DESTROY the semaphore after we are done.
     * Always clean up what you initialize!
     */
    sem_destroy(&semaphore);

    /*
     * Print the final result.
     * Both threads did 100,000 increments each.
     * Expected = 100,000 + 100,000 = 200,000
     * Semaphore ensures the answer is always correct!
     */
    printf("Final counter: %d\\n", shared_counter);

    return 0; // Program ended successfully
}

/*

Simple mental model:
Semaphore = Parking Lot 🅿️

Initial value = 1 means only 1 car allowed

Thread 1 arrives → slot available (1→0) → ENTERS
Thread 2 arrives → no slots (0)        → WAITS
Thread 1 leaves  → slot released (0→1) → Thread 2 ENTERS

Semaphore value explained:
sem_init value = 1   → Only 1 thread at a time (like mutex)
sem_init value = 3   → 3 threads allowed simultaneously
sem_init value = 0   → All threads WAIT until someone calls sem_post()

Mutex vs Semaphore — Quick comparison:
Feature            MUTEX 🚽          SEMAPHORE 🅿️
─────────────────────────────────────────────────────
Who can unlock?    Only the locker   Anyone
Count              1 (binary only)   0 to N (any number)
Use case           Protect 1 resource  Control N resources
Header             <pthread.h>       <semaphore.h>
Lock function      pthread_mutex_lock   sem_wait
Unlock function    pthread_mutex_unlock sem_post

*/`
  },
  {
    q: "Write lo_sharedmem code?",
    a: `/*
 * ============================================================
 * FILE    : lo_sharedmem.c
 * TOPIC   : Linux OS — Shared Memory between Processes
 * ============================================================
 *
 * COMPILE:
 *   gcc -o lo_sharedmem lo_sharedmem.c -lpthread
 *
 * RUN:
 *   ./lo_sharedmem
 *
 * ============================================================
 * EXPECTED OUTPUT:
 * ============================================================
 *
 *   ========================================
 *     lo_sharedmem.c — Shared Memory
 *   ========================================
 *   MAIN  : Main process PID = 5001
 *
 *   ===== DEMO 1: Basic Shared Memory =====
 *   PARENT: My PID = 5001
 *   CHILD : My PID = 5002
 *   PARENT: Written 100 to shared memory
 *   CHILD : Read value from shared memory = 100
 *   CHILD : Added 50, new value = 150
 *   PARENT: Final value in shared memory = 150
 *
 *   ===== DEMO 2: Shared Counter (Race Condition Safe) =====
 *   PARENT: Starting 100000 increments...
 *   CHILD : Starting 100000 increments...
 *   PARENT: Done incrementing!
 *   CHILD : Done incrementing!
 *   MAIN  : Final counter = 200000 (expected 200000) ✓
 *
 *   ===== DEMO 3: Shared Struct =====
 *   PARENT: Written to shared struct:
 *           name    = HelloFromParent
 *           value   = 42
 *           flag    = 1
 *   CHILD : Read from shared struct:
 *           name    = HelloFromParent
 *           value   = 42
 *           flag    = 1
 *
 *   ===== ALL DEMOS COMPLETE =====
 *   MAIN  : Shared memory released
 *
 * ============================================================
 * NOTE:
 *   PID numbers         → different on your machine
 *   PARENT/CHILD order  → may vary, OS scheduler decides
 *   Final counter       → ALWAYS 200000, semaphore protects it
 * ============================================================
 *
 * WHAT EACH FUNCTION DOES:
 * ──────────────────────────────────────────────────────────
 *  mmap()        → create shared memory region in RAM
 *  munmap()      → release shared memory when done
 *  fork()        → create child process that shares memory
 *  sem_init()    → initialize semaphore inside shared memory
 *  sem_wait()    → LOCK   (like pthread_mutex_lock)
 *  sem_post()    → UNLOCK (like pthread_mutex_unlock)
 *  sem_destroy() → cleanup semaphore
 *  wait()        → parent waits for child to finish
 * ──────────────────────────────────────────────────────────
 *
 * MENTAL MODEL:
 * ──────────────────────────────────────────────────────────
 *  mmap()   = rent a WHITEBOARD both processes can see
 *  sem      = a TOKEN — only holder can write on whiteboard
 *  fork()   = make a copy of current process
 *  munmap() = return the whiteboard when done
 * ──────────────────────────────────────────────────────────
 *
 * COMPARISON:
 * ──────────────────────────────────────────────────────────
 *  lo_mutex.c          │ lo_sharedmem.c
 * ──────────────────────────────────────────────────────────
 *  threads             │ processes (fork)
 *  pthread_mutex       │ semaphore (sem_t)
 *  global variable     │ mmap() shared memory
 *  mutex_lock()        │ sem_wait()
 *  mutex_unlock()      │ sem_post()
 *  pthread_join()      │ wait()
 *  automatic sharing   │ explicit mmap needed
 * ──────────────────────────────────────────────────────────
 *
 * COMMON MISTAKES:
 * ──────────────────────────────────────────────────────────
 *  WRONG: sem_init(&sem, 0, 1) ← pshared=0, threads only
 *  RIGHT: sem_init(&sem, 1, 1) ← pshared=1, across processes
 *
 *  WRONG: MAP_PRIVATE          ← changes NOT visible to child
 *  RIGHT: MAP_SHARED           ← changes visible to all
 *
 *  WRONG: sem_t outside mmap() ← copied by fork, NOT shared
 *  RIGHT: sem_t inside mmap()  ← truly shared by both
 * ──────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>          /* fork(), getpid(), sleep()  */
#include <sys/mman.h>        /* mmap(), munmap()           */
#include <sys/wait.h>        /* wait()                     */
#include <semaphore.h>       /* sem_t, sem_init/wait/post  */


/* ============================================================
 * SHARED DATA STRUCTURES
 * ============================================================ */

/* Demo 1 + 2 */
typedef struct {
    int   counter;     /* shared counter                   */
    int   value;       /* simple shared value              */
    sem_t sem;         /* semaphore INSIDE shared memory   */
} SharedBasic;

/* Demo 3 */
typedef struct {
    char  name[32];    /* shared string                    */
    int   value;       /* shared integer                   */
    int   flag;        /* shared flag 0 or 1               */
    sem_t sem;         /* semaphore INSIDE shared memory   */
} SharedStruct;


/* ============================================================
 * DEMO 1: Basic shared memory — parent writes, child reads
 * ============================================================ */
void demo_basic_shared_memory() {
    printf("\\n===== DEMO 1: Basic Shared Memory =====\\n");

    /*
     * mmap() — create shared memory
     * MAP_SHARED    → changes visible to ALL processes
     * MAP_ANONYMOUS → no file, just RAM
     */
    SharedBasic* shared = mmap(
        NULL,
        sizeof(SharedBasic),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    shared->value = 0;
    sem_init(&shared->sem, 1, 1);  /* pshared=1, value=1 */

    pid_t pid = fork();

    if (pid == 0) {
        /* ── CHILD ── */
        printf("CHILD : My PID = %d\\n", getpid());
        sleep(1);   /* wait for parent to write first */

        sem_wait(&shared->sem);                          /* LOCK   */
        printf("CHILD : Read value from shared memory = %d\\n",
               shared->value);
        shared->value += 50;
        printf("CHILD : Added 50, new value = %d\\n", shared->value);
        sem_post(&shared->sem);                          /* UNLOCK */

        exit(0);
    }
    else {
        /* ── PARENT ── */
        printf("PARENT: My PID = %d\\n", getpid());

        sem_wait(&shared->sem);                          /* LOCK   */
        shared->value = 100;
        printf("PARENT: Written 100 to shared memory\\n");
        sem_post(&shared->sem);                          /* UNLOCK */

        wait(NULL);   /* wait for child */

        printf("PARENT: Final value in shared memory = %d\\n",
               shared->value);
    }

    sem_destroy(&shared->sem);
    munmap(shared, sizeof(SharedBasic));
}


/* ============================================================
 * DEMO 2: Shared counter — both processes increment safely
 * ============================================================ */
void demo_shared_counter() {
    printf("\\n===== DEMO 2: Shared Counter (Race Condition Safe) =====\\n");

    SharedBasic* shared = mmap(
        NULL,
        sizeof(SharedBasic),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    shared->counter = 0;
    sem_init(&shared->sem, 1, 1);

    pid_t pid = fork();

    if (pid == 0) {
        /* ── CHILD: increment 100000 times ── */
        printf("CHILD : Starting 100000 increments...\\n");

        for (int i = 0; i < 100000; i++) {
            sem_wait(&shared->sem);   /* LOCK   */
            shared->counter++;         /* safe!  */
            sem_post(&shared->sem);   /* UNLOCK */
        }

        printf("CHILD : Done incrementing!\\n");
        exit(0);
    }
    else {
        /* ── PARENT: increment 100000 times ── */
        printf("PARENT: Starting 100000 increments...\\n");

        for (int i = 0; i < 100000; i++) {
            sem_wait(&shared->sem);   /* LOCK   */
            shared->counter++;         /* safe!  */
            sem_post(&shared->sem);   /* UNLOCK */
        }

        printf("PARENT: Done incrementing!\\n");

        wait(NULL);   /* wait for child */

        printf("MAIN  : Final counter = %d (expected 200000) %s\\n",
               shared->counter,
               shared->counter == 200000 ? "✓" : "✗ ERROR!");
    }

    sem_destroy(&shared->sem);
    munmap(shared, sizeof(SharedBasic));
}


/* ============================================================
 * DEMO 3: Shared struct — pass complex data between processes
 * ============================================================ */
void demo_shared_struct() {
    printf("\\n===== DEMO 3: Shared Struct =====\\n");

    SharedStruct* shared = mmap(
        NULL,
        sizeof(SharedStruct),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        -1, 0
    );

    if (shared == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    memset(shared->name, 0, sizeof(shared->name));
    shared->value = 0;
    shared->flag  = 0;
    sem_init(&shared->sem, 1, 1);

    pid_t pid = fork();

    if (pid == 0) {
        /* ── CHILD: read the struct ── */
        sleep(1);   /* wait for parent to write */

        sem_wait(&shared->sem);
        printf("CHILD : Read from shared struct:\\n");
        printf("        name    = %s\\n", shared->name);
        printf("        value   = %d\\n", shared->value);
        printf("        flag    = %d\\n", shared->flag);
        sem_post(&shared->sem);

        exit(0);
    }
    else {
        /* ── PARENT: write to the struct ── */
        sem_wait(&shared->sem);
        strncpy(shared->name, "HelloFromParent",
                sizeof(shared->name) - 1);
        shared->value = 42;
        shared->flag  = 1;
        printf("PARENT: Written to shared struct:\\n");
        printf("        name    = %s\\n", shared->name);
        printf("        value   = %d\\n", shared->value);
        printf("        flag    = %d\\n", shared->flag);
        sem_post(&shared->sem);

        wait(NULL);
    }

    sem_destroy(&shared->sem);
    munmap(shared, sizeof(SharedStruct));
}


/* ============================================================
 * MAIN
 * ============================================================ */
int main() {
    printf("========================================\\n");
    printf("  lo_sharedmem.c — Shared Memory\\n");
    printf("========================================\\n");
    printf("MAIN  : Main process PID = %d\\n", getpid());

    demo_basic_shared_memory();
    demo_shared_counter();
    demo_shared_struct();

    printf("\\n===== ALL DEMOS COMPLETE =====\\n");
    printf("MAIN  : Shared memory released\\n");

    return 0;
}`
  },
  {
    q: "Write lo_threads code?",
    a: `/*
 * ============================================================
 * FILE    : lo_threads.c
 * TOPIC   : Linux OS — Thread Management (POSIX Threads)
 * AUTHOR  : sudhirvacharya
 * ============================================================
 *
 * WHAT IS A THREAD?
 * ─────────────────
 * Thread = lightweight unit of execution INSIDE a process
 * Process = factory 🏭
 * Thread  = worker inside factory 👷
 * All threads SHARE the same memory (heap, globals)
 * Each thread has its OWN stack
 *
 * COVERS:
 *   1. pthread_create()   — create a thread
 *   2. pthread_join()     — wait for thread to finish
 *   3. pthread_self()     — get my own thread ID
 *   4. pthread_exit()     — exit from thread
 *   5. pass argument      — send data INTO thread
 *   6. return value       — get data BACK from thread
 *   7. multiple threads   — array of threads in loop
 *
 * ============================================================
 * COMPILE:
 *   gcc -o lo_threads lo_threads.c -lpthread
 *
 * RUN:
 *   ./lo_threads
 *
 * NOTE: -lpthread flag is MANDATORY for pthread functions
 * ============================================================
 *
 * MENTAL MODEL:
 *
 *   main() [Manager 👔]
 *       │
 *       ├── pthread_create ──→ Thread 1 [Worker 👷]
 *       ├── pthread_create ──→ Thread 2 [Worker 👷]
 *       ├── pthread_create ──→ Thread 3 [Worker 👷]
 *       │
 *       └── pthread_join × 3 ──→ wait for all workers
 *
 * ============================================================
 *
 * THREAD vs PROCESS COMPARISON:
 * ──────────────────────────────────────────────────────
 *  Process (lo_process.c)  │  Thread (lo_threads.c)
 * ──────────────────────────────────────────────────────
 *  fork()                  │  pthread_create()
 *  wait()                  │  pthread_join()
 *  exit()                  │  pthread_exit()
 *  getpid()                │  pthread_self()
 *  separate memory         │  shared memory
 *  heavyweight             │  lightweight
 *  created by OS           │  created inside process
 * ──────────────────────────────────────────────────────
 *
 * ============================================================
 * EXPECTED OUTPUT:
 * ============================================================
 *
 * ========================================
 *   lo_threads.c — Thread Management
 * ========================================
 * MAIN  : Main thread ID = 139785234567890
 *
 * ===== DEMO 1: Basic Thread =====
 * MAIN  : Thread created, ID = 139785234567891
 * THREAD: I am running! Thread ID = 139785234567891
 * THREAD: Doing some work...
 * THREAD: Work done! Exiting.
 * MAIN  : Thread joined (finished)!
 *
 * ===== DEMO 2: Pass Argument to Thread =====
 * THREAD 1: Hello from thread number 1!
 * THREAD 1: My ID = 139785234567892
 * THREAD 2: Hello from thread number 2!
 * THREAD 2: My ID = 139785234567893
 * THREAD 3: Hello from thread number 3!
 * THREAD 3: My ID = 139785234567894
 * THREAD 1: Done!
 * THREAD 2: Done!
 * THREAD 3: Done!
 * MAIN  : All 3 threads finished!
 *
 * ===== DEMO 3: Return Value from Thread =====
 * THREAD: Calculating 7 x 7...
 * THREAD: Result = 49, returning to main!
 * MAIN  : Thread returned result = 49
 *
 * ===== DEMO 4: Multiple Threads =====
 * MAIN  : Created worker 1
 * MAIN  : Created worker 2
 * MAIN  : Created worker 3
 * MAIN  : Created worker 4
 * WORKER 1: Started
 * WORKER 2: Started
 * WORKER 3: Started
 * WORKER 4: Started
 * WORKER 1: Finished (slept 1 sec)
 * MAIN  : Worker 1 joined!
 * WORKER 2: Finished (slept 2 sec)
 * MAIN  : Worker 2 joined!
 * WORKER 3: Finished (slept 3 sec)
 * MAIN  : Worker 3 joined!
 * WORKER 4: Finished (slept 4 sec)
 * MAIN  : Worker 4 joined!
 * MAIN  : All workers done!
 *
 * ===== DEMO 5: pthread_exit() =====
 * THREAD: Running...
 * THREAD: Calling pthread_exit() now
 * MAIN  : Thread exited cleanly!
 *
 * ===== ALL DEMOS COMPLETE =====
 *
 * ============================================================
 * NOTE: Thread IDs will be DIFFERENT on your machine
 *       Demo 2 print order may vary — OS scheduler decides
 *       Demo 4 finish order is fixed because of sleep()
 * ============================================================
 *
 * QUICK REFERENCE:
 * ──────────────────────────────────────────────────────────
 *  pthread_create(&t, NULL, func, arg) → create thread
 *  pthread_join(t, &retval)            → wait + get return
 *  pthread_self()                      → my thread ID
 *  pthread_exit(val)                   → exit this thread
 *  -lpthread                           → link flag needed
 * ──────────────────────────────────────────────────────────
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>     // all pthread functions
#include <unistd.h>      // sleep()


/* ============================================================
 * DEMO 1: Basic thread creation
 * ============================================================ */
void* basic_thread(void* arg) {
    printf("THREAD: I am running! Thread ID = %lu\\n",
           (unsigned long)pthread_self());
    printf("THREAD: Doing some work...\\n");
    sleep(1);
    printf("THREAD: Work done! Exiting.\\n");
    return NULL;
}

void demo_basic_thread() {
    printf("\\n===== DEMO 1: Basic Thread =====\\n");

    pthread_t t1;

    pthread_create(&t1, NULL, basic_thread, NULL);

    printf("MAIN  : Thread created, ID = %lu\\n",
           (unsigned long)t1);

    pthread_join(t1, NULL);

    printf("MAIN  : Thread joined (finished)!\\n");
}


/* ============================================================
 * DEMO 2: Pass argument to thread
 * ============================================================ */
void* thread_with_arg(void* arg) {
    int thread_num = *((int*)arg);

    printf("THREAD %d: Hello from thread number %d!\\n",
           thread_num, thread_num);
    printf("THREAD %d: My ID = %lu\\n",
           thread_num, (unsigned long)pthread_self());
    sleep(1);
    printf("THREAD %d: Done!\\n", thread_num);
    return NULL;
}

void demo_pass_argument() {
    printf("\\n===== DEMO 2: Pass Argument to Thread =====\\n");

    pthread_t t1, t2, t3;
    int n1 = 1, n2 = 2, n3 = 3;

    pthread_create(&t1, NULL, thread_with_arg, &n1);
    pthread_create(&t2, NULL, thread_with_arg, &n2);
    pthread_create(&t3, NULL, thread_with_arg, &n3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("MAIN  : All 3 threads finished!\\n");
}


/* ============================================================
 * DEMO 3: Return value from thread
 * ============================================================ */
void* thread_return_value(void* arg) {
    int num = *((int*)arg);

    printf("THREAD: Calculating %d x %d...\\n", num, num);
    sleep(1);

    /*
     * IMPORTANT: use malloc() NOT local variable
     * Local variable lives on STACK — destroyed when thread exits
     * malloc() lives on HEAP  — survives after thread exits
     */
    int* result = malloc(sizeof(int));
    *result = num * num;

    printf("THREAD: Result = %d, returning to main!\\n", *result);
    return (void*)result;
}

void demo_return_value() {
    printf("\\n===== DEMO 3: Return Value from Thread =====\\n");

    pthread_t t1;
    int num = 7;

    pthread_create(&t1, NULL, thread_return_value, &num);

    void* retval;
    pthread_join(t1, &retval);   // captures thread's return

    int* result = (int*)retval;
    printf("MAIN  : Thread returned result = %d\\n", *result);

    free(result);   // always free heap memory!
}


/* ============================================================
 * DEMO 4: Multiple threads using array + loop
 * ============================================================ */
void* worker(void* arg) {
    int id = *((int*)arg);
    printf("WORKER %d: Started\\n", id);
    sleep(id);   // worker 1 sleeps 1s, worker 4 sleeps 4s
    printf("WORKER %d: Finished (slept %d sec)\\n", id, id);
    return NULL;
}

void demo_multiple_threads() {
    printf("\\n===== DEMO 4: Multiple Threads =====\\n");

    pthread_t threads[4];
    int ids[4] = {1, 2, 3, 4};

    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, worker, &ids[i]);
        printf("MAIN  : Created worker %d\\n", ids[i]);
    }

    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
        printf("MAIN  : Worker %d joined!\\n", ids[i]);
    }

    printf("MAIN  : All workers done!\\n");
}


/* ============================================================
 * DEMO 5: pthread_exit() vs return NULL
 * ============================================================ */
void* thread_exit_demo(void* arg) {
    printf("THREAD: Running...\\n");
    printf("THREAD: Calling pthread_exit() now\\n");

    /*
     * pthread_exit() → exits ONLY this thread
     * return NULL    → same effect inside thread function
     *
     * KEY DIFFERENCE — when called from main():
     * pthread_exit() → process stays alive until all threads done
     * return 0       → kills ALL threads immediately!
     */
    pthread_exit(NULL);

    printf("THREAD: You will NEVER see this line!\\n");
    return NULL;
}

void demo_pthread_exit() {
    printf("\\n===== DEMO 5: pthread_exit() =====\\n");

    pthread_t t1;
    pthread_create(&t1, NULL, thread_exit_demo, NULL);
    pthread_join(t1, NULL);

    printf("MAIN  : Thread exited cleanly!\\n");
}


/* ============================================================
 * MAIN
 * ============================================================ */
int main() {
    printf("========================================\\n");
    printf("  lo_threads.c — Thread Management\\n");
    printf("========================================\\n");
    printf("MAIN  : Main thread ID = %lu\\n",
           (unsigned long)pthread_self());

    demo_basic_thread();
    demo_pass_argument();
    demo_return_value();
    demo_multiple_threads();
    demo_pthread_exit();

    printf("\\n===== ALL DEMOS COMPLETE =====\\n");
    return 0;
}`
  },
  {
    q: "Write memory_layout code?",
    a: `#include <stdio.h>
#include <stdlib.h>

int main()
{

    	int a = 0x02;          // an integer
	    int *ptr = &a;         // pointer to int
	    int **ptr_ptr = &ptr;  // pointer to pointer to int

        int a_stack;
    static int b_bss;
    static int c_init=8;
    volatile register int d_reg=10;
  //  char *ptr="ro_data";
    char *buff_ptr=malloc(10);

    printf("a_stack adress=%p \\t",&a_stack);
    printf("a_stack data=%d\\n",a_stack);

    printf("b_bss adress=%p\\t",&b_bss);
    printf("b_bss data =%d\\n",b_bss);

    printf("c_init adress=%p \\t",&c_init);
     printf("c_init data=%d \\n",c_init);

    //printf("d_reg adress=%p \\t",&d_reg);/* this will not due ti register will not give acess to user*/
       printf("d_reg data=%d \\n",d_reg);

       printf("ptr adress=%p \\t",&ptr);
           printf("ptr data=%#lx \\n",ptr);

           printf("buff_ptr adress=%p \\t",&buff_ptr);
                   printf("buff_ptr data=%#lx \\n",buff_ptr);

                   if (buff_ptr)
                	  free(buff_ptr) ;




	    printf("a: %d\\n", a);
	    printf("*ptr: %d\\n", *ptr);
	    printf("**ptr_ptr: %d\\n", **ptr_ptr);

	    // Print addresses
	    printf("\\nAddresses:\\n");
	    printf("&a: %p\\n", (void*)&a);
	    printf("ptr (address of a): %p\\n", (void*)ptr);
	    printf("&ptr: %p\\n", (void*)&ptr);
	    printf("ptr_ptr (address of ptr): %p\\n", (void*)ptr_ptr);
	    printf("&ptr_ptr: %p\\n", (void*)&ptr_ptr);

    return 0;
}

/*

High Address
+---------------------------+
|         STACK             |
|  0x7ffe0be28790  a_stack  |  local var, value=0 (uninitialized local)
|  0x7ffe0be28798  ptr      |  pointer variable lives on stack
|  0x7ffe0be287a0  buff_ptr |  pointer variable lives on stack
+---------------------------+
|                           |
|      (free space)         |
|                           |
+---------------------------+
|         HEAP              |
|  0x618afd6392a0  ◄──────────── buff_ptr points here (large gap!)
|                           |
|  0x618adea26004  ◄──────────── ptr points here
+---------------------------+
|         .BSS              |
|  0x618adea28018  b_bss    |  value=0, uninitialized global
+---------------------------+
|         .data             |
|  0x618adea28010  c_init   |  value=8, initialized global
+---------------------------+
|         .text / .rodata   |  const int a=4;
+---------------------------+
Low Address
*/`
  },
  {
    q: "Write practice code?",
    a: `#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//sort 01
void movezerotoend(int *a, int n)
{

    int left=0;
    int right=0;
    while(right < n)
    {

        if(a[right] !=0)
        {
            int tmp;
            tmp=a[right];
            a[right]=a[left];
            a[left]=tmp;
            left++;
            right++;

            
        }
        else
        {
            right++;
        }


    }

}
int main()
{
    int a[]={1,0,0,1,0};
    int n=sizeof(a)/sizeof(a[0]);
    movezerotoend(a, n);
    for(int i=0;i<n ; i++)
    {
        printf("%d", a[i]);
    }

    return 0;
}`
  },
  {
    q: "Write ptr_array code?",
    a: `#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30;
    int *arr[3];   // array of 3 int pointers

    arr[0] = &a;
    arr[1] = &b;
    arr[2] = &c;

    for(int i=0; i<3; i++) {
        printf("Value at arr[%d] = %d\\n", i, *arr[i]);
    }
    return 0;
}`
  },
  {
    q: "Write struct code?",
    a: `#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int a;
    int b;

}__attribute__((packed)) reg1;

int main(void)
{
    reg1 *gpio= malloc(sizeof(reg1));
   gpio->a=1;

    printf("hello \\n");
}`
  },
  {
    q: "Write switch_case code?",
    a: `#include <stdio.h>
int main() {
   int day = 3;
   switch (day) {
       case 1:
           printf("Monday");
           break;
       case 2:
           printf("Tuesday");
           break;
       default:
           printf("Invalid day number");
   }
   return 0;
}`
  },
  {
    q: "Write ternary code?",
    a: `#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a=2, b=5, c=0, max;

    (a>b)? (c=10):(c=20); 
    max= ( a > b) ? a:b;
    max = (a > b) ? ((a > c) ? a : c) : ((b > c) ? 5 : 7);
    printf("c:%d \\n",c);
    return 0;
}`
  },
  {
    q: "Write union code?",
    a: `// union is a userdefined data types that allows multiple member
// with poeencially diffrent data types, to share the same memory


#include <stdio.h>

//type punning
typedef union {
    char a[4];
    int i_num;
} Number;


//strucure inside unioin and also using bitf

typedef struct regb
{
    unsigned int setbit:1;
    unsigned int overflow:31;
}structb;

typedef union{
    unsigned int reg;
    structb bits;
}unionreg;

unionreg gpio;

int main()
{
    gpio.reg=0xffff;
    printf("setbit : %d \\n", gpio.bits.setbit);
}`
  },
  {
    q: "Write xbmp_2byte_swap code?",
    a: `#include <stdio.h>
#include <stdint.h>

uint16_t n=0x1234;
//3412
int main()
{

  n= ((n & 0x00ff) << 8)  | (( n & 0xff00 )>> 8);

  printf("0x%x\\n",n);
    
}`
  },
  {
    q: "Write xbmp_4byteswap code?",
    a: `#include <stdio.h>
#include <stdint.h>

uint32_t n=0x12345678;
//78563412
int main()
{

  n= ((n & 0x000000ff) << 24)  | (( n & 0x0000ff00 ) <<8) | (( n & 0xff000000 ) >> 24) | (( n & 0x00ff0000 ) >> 8);

  printf("0x%x\\n",n);
    
}`
  },
  {
    q: "Write xbmp_anagram code?",
    a: `#include <stdio.h>

void sort(char *array, int n)
{

    for(int i=0 ; i< n; i++)
    {
        for( int  j=i+1 ;j<n ; j++)
        {
            if(array[i] > array[j])
            {
                char tmp;
                tmp= array[i];
                array[i]=array[j];
                array[j]=tmp;

            }


        }
    }

}
int main()
{
    char str1[]="anagram";
	char str2[]="ramanag";
    int n = sizeof(str1)/sizeof(str1[0]);
    sort(str1 , n-1);
    sort(str2 , n-1);
    for(int i=0 ; i<n-1 ; i++)
    {
         printf("%c",str1[i]);

    }
    printf("\\n");
    for(int i=0 ; i<n-1 ; i++)
    {
        printf("%c",str2[i]);
    }
    printf("\\n");

  
   
    return 0;
}`
  },
  {
    q: "Write xbmp_bit_op code?",
    a: `#include <stdio.h>
#include <stdlib.h>

#define SETBIT(N, POS) ( N |= 1<< POS )
#define CLEABIT(N, POS) ( N &= ~( 1 <<POS ) )
#define TOGGLE(N, POS) ( N ^=( 1 <<POS ))
#define IS_BIT_SET(n, pos) ((n) & (1U << (pos)))

int main()
{
    int a=0;
    int b=1;
    int c=1;
        int d=1;

    printf("SETBIT %d \\n", SETBIT(a, 0));
    printf("CLEABIT %d \\n", CLEABIT(b, 0));
    printf("TOGGLE %d \\n", TOGGLE(c, 0));
    printf(" is bit set" %d \\n",  IS_BIT_SET(d, 0));

    return 0;
}`
  },
  {
    q: "Write xbmp_byteswap code?",
    a: `#include <stdio.h>
#include <stdint.h>

uint8_t n=0x12;
int main()
{

  n= ((n & 0x0f) << 4)  | (( n & 0xf0 )>> 4);

  printf("0x%x\\n",n);
    
}`
  },
  {
    q: "Write xbmp_cnt_vowel code?",
    a: `#include <stdio.h>
#include <ctype.h>
 
int main()
{
    // Initializing variable.
    char str[100]="india";  
    int i, vowels = 0;

    
    //Initializing for loop. 
    for(i = 0; str[i]; i++)  // loops until the null terminator ('\\0') is reached.
    {
        //Counting the vowels.
        //a, e, i, o, u
        if(str[i]=='a'|| str[i]=='e'||str[i]=='i'||
           str[i]=='o'|| str[i]=='u'||str[i]=='A'||
           str[i]=='E'||str[i]=='I'||str[i]=='O' ||str[i]=='U')
        {
            vowels++;
        }
    }
 	
    //Printing the count of vowels.
    printf("Total number of vowels: = %d\\n",vowels);
    
    return 0;
}`
  },
  {
    q: "Write xbmp_endians code?",
    a: `#include <stdio.h>
#include <stdlib.h>

  int a= 0x12345678;
  int var= 0x12345678;
  // DONT LOOK INTO VARIABLE, LOOK INOT MEMORY HOW ITS SAVED.
  /*
  a = 0x12345678 (stored as 4 bytes: 0x12345678)

  Big Endian (MSB at lowest address):
  addr 0x0000 --> 0x12
  addr 0x0001 --> 0x24
  addr 0x0002 --> 0x56
  addr 0x0003 --> 0x78

  Little Endian (LSB at lowest address):
  addr 0x0000 --> 0x78   <-- ptr points here; matches (a & 0x000000FF) = 0x78
  addr 0x0001 --> 0x56
  addr 0x0002 --> 0x34
  addr 0x0003 --> 0x12
  */

 char *ptr = (char *)&a;

 void convert_endians(  )
 {
    /* var = 0x12345678
     * Byte layout (big endian view):
     *  [31:24]   [23:16]   [15:8]    [7:0]
     *   0x12      0x34      0x56      0x78
     *
     * Mask reference:
     *   0xFF000000  -> bits 31:24  (byte 3)
     *   0x00FF0000  -> bits 23:16  (byte 2)
     *   0x0000FF00  -> bits 15:8   (byte 1)
     *   0x000000FF  -> bits  7:0   (byte 0)
     *
     * Swap: byte0<->byte3, byte1<->byte2
     * Result: 0x78563412
     */
    printf("Before conv: 0x%08x \\n", var);
    var = ((var & 0x000000FF) << 24) |  /* byte0 -> byte3 */
          ((var & 0x0000FF00) <<  8) |  /* byte1 -> byte2 */
          ((var & 0x00FF0000) >>  8) |  /* byte2 -> byte1 */
          ((var & 0xFF000000) >> 24);   /* byte3 -> byte0 */
    printf("After  conv: 0x%08x \\n", var);
 }

int main()
{
    /* Cast to char* to read the lowest address byte.
     * On little endian: lowest addr holds LSB = (a & 0x000000FF) = 0x34
     * On big endian:    lowest addr holds MSB = 0x00, not equal to 0x34
     */
    if(*ptr == (char)(a & 0x000000FF)) // checking with lsb
    {
        printf("Little endian: lowest addr byte = 0x%x \\n", (unsigned char)*ptr);
    }
    else
    {
         printf("big endian: lowest addr byte = 0x%x \\n", (unsigned char)*ptr);
    }

    //convert endians
    convert_endians();
    return 0;
}`
  },
  {
    q: "Write xbmp_factorial code?",
    a: `#include <stdio.h>
#include <stdlib.h>


int fact(int n)
{
    if(n <=1)
        return 1;
    else
        return n * fact(n-1);
}
int main()
{
    int n=3;

    printf("factresult: %d", fact(n) );


    return 0;
}`
  },
  {
    q: "Write xbmp_fibonacci code?",
    a: `#include <stdio.h>

int main() {
    int n=9, i;
    long long a = 0, b = 1, next;


    printf("Fibonacci Series: ");
    for (i = 1; i <= n; i++) {
        printf("%lld ", a);
        next = a + b;
        a = b;
        b = next;
    }

    return 0;
}
//ans: 0 1 1 2 3 5 8 13 21`
  },
  {
    q: "Write xbmp_mcal_reg code?",
    a: `#include <stdio.h>
#include <stdint.h>

/*
 * Control Register Bit-Field Layout (32-bit register)
 *
 * Bit  0     : enable (n)       - 1-bit  : peripheral enable flag
 * Bits 1-3   : addr             - 3-bits : target address select (0-7)
 * Bit  4     : parity (p)       - 1-bit  : parity enable flag
 * Bits 5-31  : reserved
 */
typedef struct
{
    uint32_t enable  : 1;   /* bit 0     : peripheral enable          */
    uint32_t addr    : 3;   /* bits 1-3  : address select (0 to 7)    */
    uint32_t parity  : 1;   /* bit 4     : parity enable              */
    uint32_t reserved: 27;  /* bits 5-31 : reserved, keep 0           */
} CtrlReg_Bits_t;

typedef union
{
    uint32_t       reg;     /* full 32-bit register access            */
    CtrlReg_Bits_t bit;     /* individual bit-field access            */
} CtrlReg_t;

/* Peripheral control register mapped to a fixed hardware address */
#define CTRL_REG_BASE_ADDR    0x40001000UL

volatile CtrlReg_t * const pCtrlReg = (volatile CtrlReg_t *)CTRL_REG_BASE_ADDR;

int main(void)
{
    /* --- 1. Clear the whole register first (safe init) --- */
    pCtrlReg->reg = 0x00000000UL;

    /* --- 2. Set individual bit-fields --- */
    pCtrlReg->bit.enable = 1u;   /* enable peripheral                 */
    pCtrlReg->bit.addr   = 5u;   /* select address line 5 (3-bit max) */
    pCtrlReg->bit.parity = 1u;   /* enable parity check               */

    /* --- 3. Read back and verify --- */
    printf("Full register value : 0x%08X\\n", pCtrlReg->reg);
    printf("  enable  (bit 0)   : %u\\n",     pCtrlReg->bit.enable);
    printf("  addr    (bits 1-3): %u\\n",     pCtrlReg->bit.addr);
    printf("  parity  (bit 4)   : %u\\n",     pCtrlReg->bit.parity);

    return 0;
}`
  },
  {
    q: "Write xbmp_nextpower2 code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

uint32_t next_pow2(uint32_t n) {
    if (n == 0) return 1;
    n--;          // Handle exact powers of 2
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}
/*

**How it works — trace with \`n = 5\` (binary \`0101\`):**
\`\`\`
n--      → 4       = 0000 0100
n |= n>>1  0000 0100
         | 0000 0010
         = 0000 0110
n |= n>>2  0000 0110
         | 0000 0001
         = 0000 0111
n |= n>>4  0000 0111 (no change, bits already set)
...
n + 1    → 8       = 0000 1000  ✓
*/

//left shift by 1, example 5-> 00101
//16 8 4 2 1
//0  0 0 0 0
//0  0 0 0 1
//0  0 0 1 0
//0  0 1 0 0
//0  1 0 0 0
//1  0 0 0 0


int main()
{
   printf("%d \\n", next_pow2(4));
   printf("%d\\n", next_pow2_loop(4));
    return 0;
}`
  },
  {
    q: "Write xbmp_odd_occur code?",
    a: `#include <stdio.h>
#include <stdlib.h>
/*  this works only for odd number of repeation 1,3,5,7,9...

00->0
01->1
10->0
11->0

//if the odd input, output willl be high
000->0
001->1
010->1
011->0

*/
int main()
{
    int array[]={2,2,3,3,4,4,4,1,1};
    int n =sizeof(array)/sizeof(array[0]);
    int odd_occ=0;
    for( int i =0 ; i<n ; i++)
         odd_occ ^= array[i];
    printf("odd ocurence %d \\n", odd_occ);



    return 0;
}`
  },
  {
    q: "Write xbmp_point2arry code?",
    a: `#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};

    // ptr is a pointer to an array of 5 ints
    int (*ptr)[5] = &arr;

    printf("Array address : %p\\n", ptr);
    printf("First element : %d\\n", (*ptr)[0]);
    printf("Third element : %d\\n", (*ptr)[2]);

    // Traversing using pointer to array
    for (int i = 0; i < 5; i++) {
        printf("(*ptr)[%d] = %d\\n", i, (*ptr)[i]);
    }

    return 0;
}`
  },
  {
    q: "Write xbmp_print_bin code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void displaybits(unsigned char n)
{
    for(int i = 7; i >= 0; i--)
    {
        printf("%c", ((n >> i) & 1) ? '1' : '0');
    }
    printf("\\n");
}
int main()
{
    
    displaybits(6);



    return 0;
}`
  },
  {
    q: "Write xbmp_reverse_array code?",
    a: `#include <stdio.h>
#include <stdlib.h>
void reverse_recursion(int *ptr, int left, int right)
{
  
    if(left >= right)
        return;

    int tmp;
    tmp=ptr[left];
    ptr[left]=ptr[right];
    ptr[right]=tmp;

   reverse_recursion(ptr, left +1, right -1);
   
 


}
int main()
{

    int array[]={2, 0,1, 5,6};
    int n=sizeof(array)/sizeof(array[0]);

    reverse_recursion(array, 0, n-1);
    for ( int i=0 ; i<n ; i++)
        printf("%d", array[i]);
    
    return 0;
}`
  },
  {
    q: "Write xbmp_reverse_binary code?",
    a: `#include <stdio.h>
#include <stdlib.h>

void reversebit(unsigned int n)
{ 
    unsigned int tmp=0;
    for(int i=0 ;i<32 ;i++)
    {
        tmp= (tmp <<1);
        tmp |= (n>>i) & 1;
       
        
    }
    printf("result: %x \\n",tmp);
}
int main()
{
    unsigned int n=3;//0011
    reversebit(n);

    return 0;

}`
  },
  {
    q: "Write xbmp_reverse_string code?",
    a: `#include <stdio.h>
#include <stdlib.h>
void reverse_str(char *ptr, int n)
{
    while(n)
    {
        putchar(ptr[n-1]);
        fflush(stdout);
        n--;
    }

}
void recur_reverse_str(char *ptr)
{
    if(*ptr != '\\0')
    {
        recur_reverse_str(ptr +1);
         putchar(*ptr);
         fflush(stdout);

    }
   
}

void reverse12(char *ptr, int n)
{
    int left =0;
    int right=n-1;
    char tmp;

    while(left < right)
    {
        tmp= ptr[left];
        ptr[left]=ptr[right];
        ptr[right]=tmp;
        left++;
        right;;
    }
}
int main()
{
    char str[]="india";
    int n=sizeof(str)/sizeof(str[0]);
    //reverse_str(str, n-1);
    //recur_reverse_str(str);

    reverse12(str, n-1);
    printf("%s",str);

       
    return 0;
}`
  },
  {
    q: "Write xbmp_rotate_oper code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define bit 8
bool bits;
void displaybits(unsigned char n)
{
    for(int i=7 ;i >=0 ;i--)
    {
        bits =( n >> i ) &1;

        printf(" %c ",     bits > 0 ?  '1' : '0'       ) ;
    }

}
//https://www.browserling.com/tools/rotate-binary-right
int main()
{
    unsigned char var=67;//rottat left 01000011, outpput  -->00011010
    unsigned char var1=67;//rottat right 01000011, outpput  -->01101000
    unsigned char r=3;//0000 0011

    printf("before rotate left\\n");
    displaybits(var);
    //left shift operator
    var = (var << r) |( var >> (bit - r) );
    printf("aft rtae left\\n");
    displaybits(var);

//rotate right operator
  printf("before rotate right\\n");
    displaybits(var1);

    var1 = (var1 >> r ) | var1 << (bit -r);
      printf("aft rotate right\\n");
    displaybits(var1);




}`
  },
  {
    q: "Write xbmp_shift_operator code?",
    a: `#include <stdio.h>
#include <stdlib.h>

int main()
{
    // basic shifts
    printf("1 << 0 = %d\\n", 1 << 0);   // 1
    printf("1 << 1 = %d\\n", 1 << 1);   // 2
    printf("1 << 2 = %d\\n", 1 << 2);   // 4
    printf("1 << 3 = %d\\n", 1 << 3);   // 8

    // tricky 1 — people forget shift multiplies/divides by 2
    printf("\\n-- tricky: shift = multiply/divide by 2 --\\n");
    printf("5 << 1 = %d\\n", 5 << 1);   // 5 * 2 = 10
    printf("5 << 2 = %d\\n", 5 << 2);   // 5 * 4 = 20
    printf("8 >> 1 = %d\\n", 8 >> 1);   // 8 / 2 = 4
    printf("8 >> 2 = %d\\n", 8 >> 2);   // 8 / 4 = 2

    // tricky 2 — shifting by 0 does nothing
    printf("\\n-- tricky: shift by 0 --\\n");
    printf("7 << 0 = %d\\n", 7 << 0);   // still 7

    // tricky 3 — OR sets a bit, AND checks a bit
    printf("\\n-- tricky: set vs check bit --\\n");
    unsigned char reg = 0;
    reg |= (1 << 3);                    // SET bit 3
    printf("after set  bit3 = %d\\n", reg);       // 8

    if(reg & (1 << 3))                  // CHECK bit 3
        printf("bit 3 is SET\\n");

    reg &= ~(1 << 3);                   // CLEAR bit 3
    printf("after clear bit3 = %d\\n", reg);      // 0

    // tricky 4 — ~ on small variable promotes to int!
    printf("\\n-- tricky: ~ on unsigned char --\\n");
    unsigned char a = 1;
    printf("~a = %d\\n", ~a);            // NOT 254! prints -2 due to int promotion
    printf("~a & 0xFF = %d\\n", ~a & 0xFF);  // correct way = 254

    // tricky 5 — shifting negative number is undefined behavior
    printf("\\n-- tricky: never shift negative --\\n");
    int x = -1;
    // x << 1  — undefined behavior! never do this
    printf("always use unsigned for shifts\\n");

    return 0;
}`
  },
  {
    q: "Write xbmp_strip_lowes_bit code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//strip lowet bit example 1100
//                         ^
// 12 -11 = 1100 - 1011 --> here lowest bit got cleared.
/*
1100

&

1011
1000 <----ans
*/
bool b;

void display_bits(unsigned char n)
{
    for(int i = 7; i >= 0; i--)
    {
        printf("%c", ((n >> i) & 1) ? '1' : '0');
    }
    printf("\\n");
}
int main()
{
    unsigned char n=12;//0000 1100
    printf("before \\n");
    display_bits(n);
    n=n & (n-1);
      printf("aft \\n");
    display_bits(n);
     printf("\\n");




    return 0;
}`
  },
  {
    q: "Write xbmp_swap_adj code?",
    a: `#include <stdio.h>

int main()
{
    unsigned int n=0xaa;
    //// take odd  bits, shift right 0xaa
    //  // take even bits, shift left 0x55
    n = (n & 0xaaaaaaaa) >> 1 | (n & 0x55555555) << 1;
    printf("%x \\n", n);

    return 0;
}`
  },
  {
    q: "Write xbmp_swap_nibble code?",
    a: `#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char var =0xAB;
    unsigned int var1 =0x12345678;
    var = ( (var & 0xF0) >> 4) | ( (var & 0x0F) << 4);
    var1=  (var1 & 0xffff0000  ) >> 16  |   (var1 & 0x00000ffff ) << 16;

    printf(" swap nibble %x \\n", var);
    printf(" swap nibble %x \\n", var1);

    return 0;
}`
  },
  {
    q: "Write xbmp_swap_values code?",
    a: `#include <stdio.h>
#include <stdlib.h>
void swap(int a, int b)
{
    a ^=b;
    b ^=  a;
    a ^= b;
     printf("aft swap: \\n %d \\n %d \\n", a, b);

}
int main()
{

    int a=2, b=5;
    printf("before swap: \\n %d \\n %d \\n", a, b);
    swap(a, b);


}`
  },
  {
    q: "Write xbmp_tricky code?",
    a: `#include <stdio.h>

#if 1
int main()
{
/****************************************************************/
	/* When an int and an unsigned int of the same rank (width) are compared,
	 * the signed int is converted to unsigned due to the usual arithmetic conversions.
	 * x = 5 → 0x00000005
	 * y = -1 → 0xFFFFFFFF (two's complement, interpreted as unsigned = 4294967295)
	 * So the comparison becomes if (5 > 4294967295), which is false,
	 * and the program prints "test".
	 */

	unsigned int x=5;
	         int y=-1;
	if(x > y)
		printf("Sudheer \\n");
	else
		printf("test\\n");

    return 0;
}
#endif
#if 0
int main()
{
/**********************************************************************/
	/* In C, when an unsigned short and an int are compared,
	 * the usual arithmetic conversions apply. Since int has
	 * higher rank than unsigned short, x (unsigned short = 5)
	 * is promoted to int before comparison.
	 * So the comparison is (5 > -1), which is true,
	 * and the program prints "Sudheer".
	 */
	unsigned short x=5;
	         int y=-1;
	if(x > y)
		printf("Sudheer\\n");
	else
		printf("test\\n");

return 0;
   }
#endif`
  },
  {
    q: "Write xbmp_xor code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// xor operation without xor operator
// xor is high when both input are diffrent lvel
//compare both bits and bot diffrent high or low
/*
a b y
00  0
01  1
10  1
11  0
*/

//how to design xor operation
//how we can create xor gate?
// from tt we derive  y=(a' & b ) | (a | b')

bool tmpa, tmpb;
        unsigned char a =3;//0011
    unsigned char b=7;// 0101-->output is 0100
unsigned char tmp;

void xor_oper()
{

    for(int i=7 ; i>=0 ;i--)
    {
        unsigned char tmpa= (a >> i) & 1;
        unsigned char tmpb= (b >> i) & 1;

        if( tmpa   != tmpb)
        {
            tmp |= 1 << i;
        }
       
    }
    printf(" xor operation %d \\n",tmp);
}
int main()
{
   // xor_oper();
    // XOR = A'B + AB'
    tmp = (~a & b) | (a & ~b);
     printf(" xor operation %d \\n",tmp);


    return 0;
}`
  },
  {
    q: "Write xmp_countsetbits code?",
    a: `#include <stdio.h>
#include <stdlib.h>


// 8421
// 0101
// 0100
// 0011
// 0010
// 0001
// 0000

int main()
{
    int var =5, cnt=0;
    while(var)
    {
        var = var & (var -1);
        cnt++;
        printf("var:%b \\n", var);
    }
    printf("total count:%d \\n", cnt);
}`
  },
  {
    q: "Write y_adc_baremetal code?",
    a: `void Adc_Init()
{

	RCC->CFGR |= (6 <<12); //APB = HCLK/8 = 8Mhz
	RCC->APBENR2 |= (1<<20); //adc clock
	if(ADC1->ISR & (1<<0)) //ADC READY
	{
		ADC1->CR |= 1<<1;//DISABLED ADC
	}
	ADC1->CR |= 1<<28; //REGULATOR ENABLE
	delay_ms(1);
	ADC1->CR |= 1<<31; //ADC CALIBARATION STARTED
	delay_ms(1);
	while(ADC1->CR & (1<<31));


}
void Adc_Cfg(uint8_t ch)
{
	//22,24
	ADC1_COMMON->CCR |= (1<<24); //VBAT

	ADC1_COMMON->CCR |= (1<<22); //VREGU
	delay_ms(10);
	ADC1->CHSELR |= (1<<ch);
	ADC1->SMPR |= 4<<0; //SAMPLING RATE
	ADC1->CR |= 1<<0; //ADC EN
	while(!(ADC1->ISR & (1<<0))); //AD   RDY
}

uint16_t Adc_Read()
{
	ADC1->CR |= 1<<2; //ADC START
	while(!(ADC1->ISR & (1<<2))); //eoc
	return ADC1->DR;

}

#define DEBUG 1
int main(void)
{
	uint16_t raw_value;

	float voltage;
	Adc_Init();
	while(1)
	{
		Adc_Cfg(14); //p7

		raw_value=Adc_Read();
		raw_value1= raw_value;
		voltage = (raw_value*3.3)/4095 ;
	}


}`
  },
  {
    q: "Write y_spi_baremetal code?",
    a: `#include "stm32g0xx.h"
#include <stdint.h>
#include <stdbool.h>

/* ─────────────────────────────────────────────
 * SPI1_Init
 * Configures PLL clock, GPIO alternate functions,
 * and SPI1 control registers for master mode.
 * ───────────────────────────────────────────── */
void SPI1_Init(void)
{
    /* 1. Configure PLL clock source
     * PLLCFGR: set PLLM divider = 1 (bits [5:0])
     * << 0 means writing to bit position 0 */
    RCC->PLLCFGR = (2 << 0);

    /* 2. Enable GPIOA and SPI1 peripheral clocks */
    RCC->IOPENR  |= RCC_IOPENR_GPIOAEN;
    RCC->APBENR2 |= RCC_APBENR2_SPI1EN;

    /* 3. Set PA5 (SCK), PA6 (MISO), PA7 (MOSI) to Alternate Function mode
     * MODER bits: 10 = Alternate Function
     * Clear 2 bits per pin first, then set to 0b10 */
    GPIOA->MODER &= ~((3 << 10) | (3 << 12) | (3 << 14));
    GPIOA->MODER |=  ((2 << 10) | (2 << 12) | (2 << 14));

    /* 4. Assign AF0 to PA5, PA6, PA7 (SPI1 on STM32G0)
     * AFR[0] controls pins 0-7, each pin uses 4 bits
     * PA5 = bits[23:20], PA6 = bits[27:24], PA7 = bits[31:28] */
    GPIOA->AFR[0] &= ~((0xF << 20) | (0xF << 24) | (0xF << 28));
    GPIOA->AFR[0] |=  ((0x0 << 20) | (0x0 << 24) | (0x0 << 28)); /* AF0 */

    /* 5. Configure SPI1 Control Register 1 (CR1)
     * Bit 2 (MSTR) = 1 → Master mode
     * CPOL = 0 → Clock idle LOW  (Mode 0)
     * CPHA = 0 → Sample on first edge (Mode 0)
     * BR[2:0] = 0b000 → fPCLK/2 (fastest clock speed)
     * SSM = 1, SSI = 1 → Software slave management */
    SPI1->CR1 = (1 << 2)   /* MSTR  */
              | (0 << 1)   /* CPOL=0 */
              | (0 << 0)   /* CPHA=0 */
              | (0 << 3)   /* BR: fPCLK/2 */
              | (1 << 9)   /* SSM: software NSS */
              | (1 << 8);  /* SSI: internal slave select high */

    /* 6. Enable SPI1 (SPE bit 6) */
    SPI1->CR1 |= (1 << 6);
}

/* ─────────────────────────────────────────────
 * SPI1_TransceiveByte
 * Sends 1 byte and returns the received byte.
 * INTERVIEW: SPI is full-duplex — every transmit
 * also clocks in a byte from the slave.
 * ───────────────────────────────────────────── */
static uint8_t SPI1_TransceiveByte(uint8_t data)
{
    /* Wait until TX buffer is empty (TXE flag) */
    while (!(SPI1->SR & SPI_SR_TXE));
    *(volatile uint8_t *)&SPI1->DR = data;

    /* Wait until RX buffer has data (RXNE flag) */
    while (!(SPI1->SR & SPI_SR_RXNE));
    return (uint8_t)SPI1->DR;
}

/* ─────────────────────────────────────────────
 * SPI1_Receive
 * Reads 'size' bytes from slave.
 * INTERVIEW: Master must send dummy bytes (0xFF)
 * to generate SCK pulses — slave has no clock of its own.
 * ───────────────────────────────────────────── */
static void SPI1_Receive(uint8_t *pBuf, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        /* Dummy 0xFF clocks out SCK so slave can shift data in */
        pBuf[i] = SPI1_TransceiveByte(0xFF);
    }
}

/* ─────────────────────────────────────────────
 * main
 * Write data to W25Q flash, read it back, verify.
 * ───────────────────────────────────────────── */
int main(void)
{
    SPI1_Init();

    uint32_t testAddr   = 0x000000;
    uint8_t  txBuf[16]  = "HelloFlash123456";

    /* Step 1-4: Write data to W25Q flash memory */
    W25Q_WriteData(testAddr, txBuf, sizeof(txBuf));

    /* Step 5: Read back from same address */
    uint8_t rxBuf[16] = {0};
    W25Q_ReadData(testAddr, rxBuf, sizeof(rxBuf));

    /* Step 6: Verify write == read
     * INTERVIEW: ok=true means write→read→verify passed */
    bool ok = true;
    for (int i = 0; i < 16; i++) {
        if (txBuf[i] != rxBuf[i]) { ok = false; break; }
    }
    (void)ok; /* Inspect in debugger or set breakpoint here */

    while (1)
    {
        /* Application loop */
    }
}`
  },
  {
    q: "Write z_ascend_sort code?",
    a: `#include <stdio.h>
#include <stdlib.h>
void sort(int *array, int n)
{
    for(int i=0; i<n;i++)
    {
        for(int j=i+1;j<n; j++)
        {
            if(array[i] > array[j])
            {
                int tmp=array[i];
                array[i]=array[j];
                array[j]=tmp;
            }
        }
    }
}
int main()
{
    int array[]={2,1,7,4};
    int n=sizeof(array)/sizeof(array[0]);
    sort(array, n);
    for(int i =0 ; i<n; i++)
    {
        printf("sort %d \\n", array[i]);
    }
    return 0;
}`
  },
  {
    q: "Write z_move_zero_end code?",
    a: `#include <stdio.h>
#include <stdlib.h>

//move all zero to end using two pointers
/*
 <-- CLEAN ZONE -->|<-- UNSORTED -->
  1   2   4   3   |  0   0   5   0
                  ^           ^
                  L           R
*/

//left of array always zero expect irt iteration

// here comparing next element so
//left and right is zero
void moveZerotoEnd(int *arr, int n)
{
    int left=0;
    int right=0;
    while(right < n)
    {

        if(arr[right] != 0)
        {
            /* swap: non-zero at R goes to the clean-zone boundary L */
            int tmp = arr[right];
            arr[right] = arr[left];
            arr[left]=tmp;
            left++;
        }
        right++;
    }

}
int main()
{
    int arr[] = {1, 2, 0, 4, 3, 0, 5, 0};
    int n= sizeof(arr)/sizeof(arr[0]);
    moveZerotoEnd(arr, n);
    for(int i=0; i < n ; i++)
        printf("moveZerotoEnd %d\\n", arr[i]);
    return 0;
}
/*

    [ 0 ]
    [ 0 ]     [ 7 ]

    [ 7 ]     [ 0 ]
    L          R

        [ 0 ]     [ 0 ]
        L          R

        [ 0 ]          [ 4 ]
        L               R

        [ 4 ]          [ 0 ]
        L               R

            [ 0 ]     [ 0 ]
                L         R


*/`
  },
  {
    q: "Write z_remove_duplicate code?",
    a: `#include<stdio.h>
#include<stdlib.h>
int duplicate(int *array, int n)
{
    for(int i=0; i<n ;i++)
    {
        for(int j=i+1 ;j<n ;j++)
        {
            if(array[i]==array[j])
            {
                array[j]=array[n-1];
                n--;
                j--;
            }
        }
    }
    return n;
}
int main()
{
    int array[]={1,2,3,2,1,10,5};
    int n=sizeof(array)/sizeof(array[0]);
    n=duplicate(array, n);
    for(int i=0; i<n ;i++)
     printf("array %d \\n",array[i]);
}`
  },
  {
    q: "Write z_second_large_num code?",
    a: `#include <stdio.h>
#include <stdlib.h>

//find secodn largest using sort and find second higest
void sort(int *ptr, int len)
{
    for(int j=0; j<len; j++)
    {
        for( int i=j+1; i<len; i++)
        {
            if(ptr[j] > ptr[i])
            {
                int tmp= ptr[j];
                ptr[j]=ptr[i];
                ptr[i]=tmp;
    
            }
        }
    } 

}

int main()
{
    int array[]={7, 4, 6, 2};
    int second_large;
    int len= sizeof(array)/sizeof(array[0]);
    printf("len %d\\n ", len);
    sort(array, len);
    for(int i=0; i<len; i++)
    {
      printf("sort %d \\n", array[i]);
    }
    second_large=array[len-2];
    printf("second_large %d \\n", second_large);

    return 0;
}`
  },
  {
    q: "Write z_sizeof code?",
    a: `#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*find size of data types without size of operator*/
int main()
{

    int array[2]={2,3};// 0,1 index
    int *ptr1=&array[0];
    int *ptr2=&array[1];
    ptrdiff_t diff = (char*)ptr2 - (char*)ptr1;
    printf("size of int: %td\\n", diff);
    
}`
  },
  {
    q: "Write z_sort01 code?",
    a: `#include <stdio.h>
#include <stdlib.h>

// here comparing first and last 
//so right is n-1
void sort01(int *array, int n)
{
    int tmp=0;
    int left=0;
    int right=n-1;
    while(left <= right)
    {
        if(array[left] !=0)
        {
            tmp = array[left];
           array[left]= array[right];
           array[right]=tmp;
           right--;
        }
        else
        {
            left++;
        }
    }
}
int main()
{

    int array[]={1,0,1,1,1,0,0,1,0};
   int n=sizeof(array)/sizeof(array[0]);
    sort01(array, n);
    for( int i=0 ;i<n ; i++)
    printf( "%d",array[i]);

    return 0;


}

/*

Step 0:  |0  1  0  0  1|   L=0,R=4  arr[L]=0 → L++
          L-----------R

Step 1:   0|1  0  0  1|    L=1,R=4  arr[L]=1 → swap(1,4) R--
            L--------R

Step 2:   0|1  0  0  1|    swap 1↔1, no visible change, R--
            L-----R

Step 3:   0|1  0  0| 1     L=1,R=3  arr[L]=1 → swap(1,3) R--
            L-----R

Step 4:   0  0|0  1| 1     L=1,R=2  arr[L]=0 → L++
               L--R

Step 5:   0  0  0|1| 1     L=2,R=2  arr[L]=1 → swap(2,2) R--
                 LR

Step 6:   L > R  STOP

Result:  {0  0  0  1  1}  ✅

*/`
  },
  {
    q: "Write z_sort012 code?",
    a: `#include <stdio.h>
#include <stdlib.h>

void sort012(int *ptr, int n)
{
    /* Three pointers dividing array into zones:
     * [0..start-1]  = all 0s (sorted)
     * [start..mid-1]= all 1s (sorted)
     * [mid..end]    = unknown (to be processed)
     * [end+1..n-1]  = all 2s (sorted)
     */
    int start = 0, mid = 0, end = n - 1;
    int tmp;

    while (mid <= end)   /* keep going until unknown zone is empty */
    {
        if (ptr[mid] == 0)
        {
            /* 0 belongs in left zone: swap with start, expand both 0-zone and 1-zone */
            tmp = ptr[start];
            ptr[start] = ptr[mid];
            ptr[mid] = tmp;
            mid++;    //i had doubt why it here, this mid will transverse and pass to value to satar
            start++;    /* 0-zone grew by one */
        }
        else if (ptr[mid] == 1)
        {
            /* 1 is already in the correct middle zone, just move scanner forward */
            mid++;
        }
        else
        {
            /* 2 belongs in right zone: swap with end, shrink unknown zone from right */
            tmp = ptr[mid];
            ptr[mid] = ptr[end];
            ptr[end] = tmp;
            end--;      /* 2-zone grew by one */
            /* NOTE: mid does NOT move here — the swapped-in element is unexamined */
        }
    }
}

int main()
{
    int array[] = {2, 0, 1, 2, 0, 1, 0};
    int n = sizeof(array) / sizeof(array[0]);

    sort012(array, n);

    for (int i = 0; i < n; i++)
    {
        printf("sorted array: %d \\n", array[i]);
    }
    return 0;
}`
  },
  {
    q: "Write zz_circular_buff code?",
    a: `#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 6

typedef struct
{
    char data[MAX_BUFF];
    int  head;
    int  tail;
    int  count;
} ring_buff;

ring_buff *rb = NULL;

void enqueue(char tmp)
{
    if (rb->count == MAX_BUFF)
    {
        printf("buffer full, drop %d\\n", tmp);
        return;
    }

    rb->data[rb->head] = tmp;
    printf("enqueue: %d at head: %d\\n", rb->data[rb->head], rb->head);
    rb->head = (rb->head + 1) % MAX_BUFF;
    rb->count++;
}

void dequeue(void)
{
    char tmp;

    if (rb->count == 0)
    {
        printf("buffer empty\\n");
        return;
    }

    tmp = rb->data[rb->tail];
    printf("dequeue: %d from tail: %d\\n", tmp, rb->tail);
    rb->tail = (rb->tail + 1) % MAX_BUFF;
    rb->count--;
}

int is_full(void)
{
    return rb->count == MAX_BUFF;
}

int is_empty(void)
{
    return rb->count == 0;
}

void print_buffer(void)
{
    int i;
    int idx;

    if (is_empty())
    {
        printf("buffer empty\\n");
        return;
    }

    printf("buffer [count=%d]: ", rb->count);
    for (i = 0; i < rb->count; i++)
    {
        idx = (rb->tail + i) % MAX_BUFF;
        printf("%d ", rb->data[idx]);
    }
    printf("\\n");
}

int main(void)
{
    rb = malloc(sizeof(ring_buff));
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;

    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);
    enqueue(60);
    enqueue(70);    /* buffer full — dropped */

    print_buffer();

    dequeue();
    dequeue();

    print_buffer();

    enqueue(70);
    enqueue(80);

    print_buffer();

    free(rb);
    return 0;
}`
  },
  {
    q: "Write zz_linked_list code?",
    a: `#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

//double pointer
void insertend(node **head, int data)
{
    // Allocate memory for new node
    node *new_node= malloc(sizeof(node));
    new_node->data=data;
    new_node->next=NULL;

    // If list is empty, new node becomes the head
    //its compared same as how declared in main
    if(*head == NULL)
        {
                *head=new_node;
                        return;
                            }
                            
      // Use a temporary pointer to traverse the list
    node *tmp=*head; // don't move *head itself!
    while(tmp->next != NULL)// move until last node
        tmp=tmp->next;

    // Attach new node at the end
    //here tmp->next is NULL
    //new_node->next is NULL so we passing whole struct adress
    tmp->next=new_node;

}

void print_list(node *head)
{
    node *tempp = head;
    while(tempp !=NULL)
    {
        printf("%d-->", tempp->data);
        tempp=tempp->next;//this hsolb be place here , this soemthing i++;
    }
    printf("NULL \\n");


}

//double pointer explaination
//0x100  [int x = 2]          →  value lives here
//0x101  [int *ptr = 0x100]   →  *ptr  == 2   (single pointer: holds address of int)
//0x102  [int **pptr = 0x101] →  **pptr == 2  (double pointer: holds address of pointer)

/// Delete a node by value using double pointer
// head: pointer to the head pointer (so we can change the head if needed)
// data: the value we want to delete from the list
void delete_node(node **head, int data)
{
    node *curr = *head;  // curr starts at the first node
    node *prev = NULL;   // prev tracks the node BEFORE curr (starts as nothing)

    // Walk through the list one node at a time
    while (curr != NULL)  // stop when we reach the end of the list
    {
        if (curr->data == data)  // found the node we want to delete!
        {
            // Special case: the node to delete is the very first node (head)
            // We need to move the head forward to the next node
            if (prev == NULL)
            {
                *head = curr->next;  // head now points to the 2nd node
            }
            else
            {
                // Normal case: skip over curr by connecting prev directly to curr's next
                // Before: prev -> curr -> curr->next
                // After:  prev -> curr->next
                prev->next = curr->next;
            }

            free(curr);  // release the memory of the deleted node
            return;      // job done, exit the function
        }

        // Not found yet — move both pointers one step forward
        prev = curr;        // prev catches up to curr
        curr = curr->next;  // curr moves to the next node
    }

    // If we reach here, the value was not found in the list
    // (the function just exits quietly — no deletion happened)
}
int main()
{
    node *head=NULL;
    insertend(&head, 10);
    insertend(&head, 20);
    insertend(&head, 30);
    print_list(head);

    delete_node(&head, 20);
    printf("After delete: ");
    print_list(head);
    return 0;
}`
  },
  {
    q: "Write zz_stack code?",
    a: `#inlcude`
  },
  {
    q: "Explain 6Chadc1Dma diagram?",
    a: `Diagram: 6Chadc1Dma

Key Labels / Signals:
  - 6 ADC Channels — 1 DMA Channel (STM32 Scan Mode)
  - CH 0 (PA0)
  - CH 1 (PA1)
  - CH 2 (PA2)
  - CH 3 (PA3)
  - CH 4 (PA4)
  - CH 5 (PA5)
  - ADC_DR
  - One register
  - overwritten each conv.
  - DMA req
  - x6 per sweep
  - 1x DMA ch
  - DMA2 Stream0
  - Channel 0
  - SRAM buffer
  - buf[0] CH0
  - buf[1] CH1
  - buf[2] CH2
  - buf[3] CH3
  - buf[4] CH4
  - buf[5] CH5
  - 6 ADC channels → 1 ADC_DR register → 1 DMA channel → 1 buffer array (always)
  - Key Notes
  - All 6 channels share a single ADC_DR register — results come out one after another.
  - Only 1 DMA channel is needed regardless of how many ADC channels are used.
  - ADC_CR1: set SCAN bit to enable scan mode across all channels in the sequence.
  - ADC_CR2: set DMA + DDS + CONT bits. DDS is mandatory — without it DMA stops after 1 sweep.
  - DMA NDTR = NUM_CHANNELS x NUM_SWEEPS (e.g. 6 x 4 = 24).
  - Use CIRC mode for continuous sampling. Use HT + TC interrupts for double-buffer processing.
  - Access channel N of sweep S: buf[S * NUM_CH + N] e.g. CH2 sweep3 = buf[20].
  - STM32 ADC + DMA — Scan Mode Reference

SVG Source:
<svg width="680" height="560" viewBox="0 0 680 560" xmlns="http://www.w3.org/2000/svg" font-family="Arial, sans-serif">
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M2 1L8 5L2 9" fill="none" stroke="context-stroke" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
    </marker>
  </defs>
  <rect width="680" height="560" fill="#ffffff"/>
  <text x="340" y="22" text-anchor="middle" font-size="14" font-weight="700" fill="#1a1a1a">6 ADC Channels — 1 DMA Channel (STM32 Scan Mode)</text>
  <rect x="30" y="36" width="110" height="34" rx="6" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.8"/>
  <text x="85" y="57" text-anchor="middle" font-size="12" font-weight="600" fill="#085041">CH 0 (PA0)</text>
  <rect x="30" y="80" width="110" height="34" rx="6" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.8"/>
  <text x="85" y="101" text-anchor="middle" font-size="12" font-weight="600" fill="#085041">CH 1 (PA1)</text>
  <rect x="30" y="124" width="110" height="34" rx="6" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.8"/>
  <text x="85" y="145" text-anchor="middle" font-size="12" font-weight="600" fill="#085041">CH 2 (PA2)</text>
  <rect x="30" y="168" width="110" height="34" rx="6" fill="#EEEDFE" stroke="#534AB7" stroke-width="0.8"/>
  <text x="85" y="189" text-anchor="middle" font-size="12" font-weight="600" fill="#3C3489">CH 3 (PA3)</text>
  <rect x="30" y="212" width="110" height="34" rx="6" fill="#EEEDFE" stroke="#534AB7" stroke-width="0.8"/>
  <text x="85" y="233" text-anchor="middle" font-size="12" font-weight="600" fill="#3C3489">CH 4 (PA4)</text>
  <rect x="30" y="256" width="110" height="34" rx="6" fill="#FAECE7" stroke="#993C1D" stroke-width="0.8"/>
  <text x="85" y="277" text-anchor="middle" font-size="12" font-weight="600" fill="#712B13">CH 5 (PA5)</text>
  <path d="M140 53  Q215 53  215 162" fill="none" stroke="#1D9E75" stroke-width="1.2" marker-end="url(#arrow)"/>
  <path d="M140 97  Q215 97  215 166" fill="none" stroke="#1D9E75" stroke-width="1.2" marker-end="url(#arrow)"/>
  <path d="M140 141 Q215 141 215 170" fill="none" stroke="#1D9E75" stroke-width="1.2" marker-end="url(#arrow)"/>
  <path d="M140 185 Q215 185 215 178" fill="none" stroke="#534AB7" stroke-width="1.2" marker-end="url(#arrow)"/>
  <path d="M140 229 Q215 229 215 188" fill="none" stroke="#534AB7" stroke-width="1.2" marker-end="url(#arrow)"/>
  <path d="M140 273 Q215 273 215 198" fill="none" stroke="#993C1D" stroke-width="1.2" marker-end="url(#arrow)"/>
  <rect x="200" y="152" width="130" height="58" rx="8" fill="#FAEEDA" stroke="#BA7517" stroke-width="1"/>
  <text x="265" y="174" text-anchor="middle" font-size="13" font-weight="700" fill="#633806">ADC_DR</text>
  <text x="265" y="190" text-anchor="middle" font-size="11" fill="#854F0B">One register</text>
  <text x="265" y="204" text-anchor="middle" font-size="11" fill="#854F0B">overwritten each conv.</text>
  <line x1="330" y1="181" x2="386" y2="181" stroke="#BA7517" stroke-width="1.4" marker-end="url(#arrow)"/>
  <text x="358" y="170" text-anchor="middle" font-size="10" fill="#666666">DMA req</text>
  <text x="358" y="196" text-anchor="middle" font-size="10" fill="#666666">x6 per sweep</text>
  <rect x="388" y="152" width="130" height="58" rx="8" fill="#E6F1FB" stroke="#185FA5" stroke-width="1"/>
  <text x="453" y="172" text-anchor="middle" font-size="13" font-weight="700" fill="#0C447C">1x DMA ch</text>
  <text x="453" y="188" text-anchor="middle" font-size="11" fill="#185FA5">DMA2 Stream0</text>
  <text x="453" y="202" text-anchor="middle" font-size="11" fill="#185FA5">Channel 0</text>
  <line x1="518" y1="181" x2="554" y2="181" stroke="#185FA5" stroke-width="1.4" marker-end="url(#arrow)"/>
  <text x="557" y="146" font-size="11" font-weight="600" fill="#333333">SRAM buffer</text>
  <rect x="557" y="150" width="98" height="20" rx="3" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.7"/>
  <text x="606" y="164" text-anchor="middle" font-size="10" font-weight="600" fill="#085041">buf[0]  CH0</text>
  <rect x="557" y="172" width="98" height="20" rx="3" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.7"/>
  <text x="606" y="186" text-anchor="middle" font-size="10" font-weight="600" fill="#085041">buf[1]  CH1</text>
  <rect x="557" y="194" width="98" height="20" rx="3" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.7"/>
  <text x="606" y="208" text-anchor="middle" font-size="10" font-weight="600" fill="#085041">buf[2]  CH2</text>
  <rect x="557" y="216" width="98" height="20" rx="3" fill="#EEEDFE" stroke="#534AB7" stroke-width="0.7"/>
  <text x="606" y="230" text-anchor="middle" font-size="10" font-weight="600" fill="#3C3489">buf[3]  CH3</text>
  <rect x="557" y="238" width="98" height="20" rx="3" fill="#EEEDFE" stroke="#534AB7" stroke-width="0.7"/>
  <text x="606" y="252" text-anchor="middle" font-size="10" font-weight="600" fill="#3C3489">buf[4]  CH4</text>
  <rect x="557" y="260" width="98" height="20" rx="3" fill="#FAECE7" stroke="#993C1D" stroke-width="0.7"/>
  <text x="606" y="274" text-anchor="middle" font-size="10" font-weight="600" fill="#712B13">buf[5]  CH5</text>
  <rect x="30" y="308" width="620" height="24" rx="6" fill="#F1EFE8" stroke="#B4B2A9" stroke-width="0.7"/>
  <text x="340" y="324" text-anchor="middle" font-size="11" fill="#444441">6 ADC channels → 1 ADC_DR register → 1 DMA channel → 1 buffer array (always)</text>
  <line x1="30" y1="348" x2="650" y2="348" stroke="#cccccc" stroke-width="0.8" stroke-dasharray="5 4"/>
  <text x="30" y="370" font-size="13" font-weight="700" fill="#1a1a1a">Key Notes</text>
  <circle cx="42" cy="390" r="3.5" fill="#1D9E75"/>
  <text x="55" y="394" font-size="12" fill="#222222">All 6 channels share a single ADC_DR register — results come out one after another.</text>
  <circle cx="42" cy="413" r="3.5" fill="#1D9E75"/>
  <text x="55" y="417" font-size="12" fill="#222222">Only 1 DMA channel is needed regardless of how many ADC channels are used.</text>
  <circle cx="42" cy="436" r="3.5" fill="#534AB7"/>
  <text x="55" y="440" font-size="12" fill="#222222">ADC_CR1: set SCAN bit to enable scan mode across all channels in the sequence.</text>
  <circle cx="42" cy="459" r="3.5" fill="#534AB7"/>
  <text x="55" y="463" font-size="12" fill="#222222">ADC_CR2: set DMA + DDS + CONT bits. DDS is mandatory — without it DMA stops after 1 sweep.</text>
  <circle cx="42" cy="482" r="3.5" fill="#BA7517"/>
  <text x="55" y="486" font-size="12" fill="#222222">DMA NDTR = NUM_CHANNELS x NUM_SWEEPS (e.g. 6 x 4 = 24).</text>
  <circle cx="42" cy="505" r="3.5" fill="#BA7517"/>
  <text x="55" y="509" font-size="12" fill="#222222">Use CIRC mode for continuous sampling. Use HT + TC interrupts for double-buffer processing.</text>
  <circle cx="42" cy="528" r="3.5" fill="#993C1D"/>
  <text x="55" y="532" font-size="12" fill="#222222">Access channel N of sweep S: buf[S * NUM_CH + N]  e.g. CH2 sweep3 = buf[20].</text>
  <text x="340" y="554" text-anchor="middle" font-size="10" fill="#999999">STM32 ADC + DMA — Scan Mode Reference</text>
</svg>`
  },
  {
    q: "Explain Adc Block Diagram diagram?",
    a: `Title: AURIX VADC Block Diagram – SW Group and HW Group

Key Labels / Signals:
  - System PLL
  - 200 MHz
  - ÷2
  - SPB Peripheral Bus
  - 100 MHz
  - ÷5
  - ADC module clock
  - fADC = 20 MHz
  - Conversion time
  - ~1 µs / channel (12-bit)
  - GTM clock
  - GTM TOM0 – PWM
  - 20 kHz | T = 50 µs
  - HW trigger (ADCTrig0)
  - at midpoint 25 µs → 40 kHz
  - VADC Group 0 – AUTOSAR ADC Groups
  - VADC Group 0
  - 20 MHz | 5 channels
  - AdcGroup_0 – SW group
  - Continuous | Low priority
  - CH0 / CH1 / CH2
  - Phase A / B / C NTC sensor
  - VAREF = 5 V | 12-bit | 0–4095
  - Adc_StartGroupConversion()
  - SW trigger – once at startup
  - loops
  - auto
  - Adc_Temp_GroupNotify()
  - Adc_ReadGroup() → TempResultBuf
  - TempDataReady = TRUE
  - 10 ms thermal task
  - NTC lookup → °C | fault check
  - AdcGroup_1 – HW group
  - One-shot | High priority
  - GTM trigger
  - CH3 / CH4
  - Phase A / B current (shunt amp)
  - HW trigger – ADCTrig0
  - rising edge every 25 µs (PWM mid)
  - one-shot per trigger, no loop
  - Adc_Current_GroupNotify()
  - Adc_ReadGroup() → CurrentResultBuf
  - FOC_UpdateCurrentFeedback()
  - 50 µs FOC ISR context
  - Phase A & B current feedback
  - KEY EXPLANATION POINTS
  - 🕐 Clock Hierarchy
  - ▸ PLL 200 MHz → SPB 100 MHz
  - → ADC 20 MHz (÷5)
  - ▸ ~1 µs per 12-bit channel
  - at fADC = 20 MHz
  - ▸ GTM ref: 100 MHz for PWM
  - timing & ADC triggering
  - 🌡 SW Group – Temperature
  - ▸ Continuous scan of 3 NTC
  - sensors (Phase A / B / C)
  - ▸ Low priority, SW triggered
  - once at startup
  - ▸ 10 ms task: raw 12-bit →
  - °C via NTC LUT + fault check
  - ⚡ HW Group – Current
  - ▸ High-priority one-shot:
  - Phase A/B shunt amp
  - ▸ GTM PWM midpoint trigger
  - @ 40 kHz (every 25 µs)
  - ▸ Runs inside 50 µs FOC ISR
  - for real-time current control

SVG Source:
<svg width="100%" viewBox="0 0 680 1020" role="img" xmlns="http://www.w3.org/2000/svg" style="background:white">
  <title>AURIX VADC Block Diagram – SW Group and HW Group</title>
  <rect width="680" height="1020" fill="white"/>
  <defs>
    <marker id="arrow" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M2 1L8 5L2 9" fill="none" stroke="context-stroke" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
    </marker>
  </defs>

  <!-- CLOCK DOMAIN -->
  <rect x="240" y="20" width="200" height="44" rx="8" fill="#EEEDFE" stroke="#534AB7" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#3C3489" x="340" y="37" text-anchor="middle" dominant-baseline="central">System PLL</text>
  <text font-family="sans-serif" font-size="12" fill="#534AB7" x="340" y="55" text-anchor="middle" dominant-baseline="central">200 MHz</text>

  <line x1="340" y1="64" x2="340" y2="90" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <text font-family="sans-serif" font-size="12" fill="#888780" x="350" y="81" dominant-baseline="central">÷2</text>

  <rect x="200" y="90" width="280" height="44" rx="8" fill="#F1EFE8" stroke="#5F5E5A" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#444441" x="340" y="107" text-anchor="middle" dominant-baseline="central">SPB Peripheral Bus</text>
  <text font-family="sans-serif" font-size="12" fill="#5F5E5A" x="340" y="125" text-anchor="middle" dominant-baseline="central">100 MHz</text>

  <line x1="270" y1="134" x2="220" y2="160" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <text font-family="sans-serif" font-size="12" fill="#888780" x="216" y="151" text-anchor="end" dominant-baseline="central">÷5</text>
  <line x1="410" y1="134" x2="470" y2="160" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>

  <!-- ADC Clock -->
  <rect x="100" y="160" width="200" height="44" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#085041" x="200" y="177" text-anchor="middle" dominant-baseline="central">ADC module clock</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="200" y="195" text-anchor="middle" dominant-baseline="central">fADC = 20 MHz</text>

  <line x1="200" y1="204" x2="200" y2="228" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="100" y="228" width="200" height="44" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#085041" x="200" y="245" text-anchor="middle" dominant-baseline="central">Conversion time</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="200" y="263" text-anchor="middle" dominant-baseline="central">~1 µs / channel (12-bit)</text>

  <!-- GTM Clock -->
  <rect x="380" y="160" width="200" height="44" rx="8" fill="#FAEEDA" stroke="#854F0B" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#633806" x="480" y="177" text-anchor="middle" dominant-baseline="central">GTM clock</text>
  <text font-family="sans-serif" font-size="12" fill="#854F0B" x="480" y="195" text-anchor="middle" dominant-baseline="central">100 MHz</text>

  <line x1="480" y1="204" x2="480" y2="228" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="380" y="228" width="200" height="44" rx="8" fill="#FAEEDA" stroke="#854F0B" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#633806" x="480" y="245" text-anchor="middle" dominant-baseline="central">GTM TOM0 – PWM</text>
  <text font-family="sans-serif" font-size="12" fill="#854F0B" x="480" y="263" text-anchor="middle" dominant-baseline="central">20 kHz  |  T = 50 µs</text>

  <line x1="480" y1="272" x2="480" y2="296" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="380" y="296" width="200" height="44" rx="8" fill="#FAEEDA" stroke="#854F0B" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#633806" x="480" y="313" text-anchor="middle" dominant-baseline="central">HW trigger (ADCTrig0)</text>
  <text font-family="sans-serif" font-size="12" fill="#854F0B" x="480" y="331" text-anchor="middle" dominant-baseline="central">at midpoint  25 µs  →  40 kHz</text>

  <!-- Divider -->
  <line x1="40" y1="360" x2="640" y2="360" stroke="#B4B2A9" stroke-width="0.8" stroke-dasharray="6 4"/>
  <text font-family="sans-serif" font-size="12" fill="#888780" x="340" y="372" text-anchor="middle">VADC Group 0  –  AUTOSAR ADC Groups</text>

  <!-- VADC Group 0 box -->
  <line x1="200" y1="272" x2="200" y2="310" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="100" y="310" width="200" height="36" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#085041" x="200" y="323" text-anchor="middle" dominant-baseline="central">VADC Group 0</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="200" y="339" text-anchor="middle" dominant-baseline="central">20 MHz  |  5 channels</text>

  <line x1="200" y1="346" x2="170" y2="384" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <line x1="270" y1="328" x2="420" y2="380" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>

  <!-- SW GROUP -->
  <rect x="30" y="384" width="280" height="44" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#085041" x="170" y="401" text-anchor="middle" dominant-baseline="central">AdcGroup_0  –  SW group</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="170" y="419" text-anchor="middle" dominant-baseline="central">Continuous  |  Low priority</text>

  <rect x="30" y="440" width="280" height="56" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#085041" x="170" y="458" text-anchor="middle" dominant-baseline="central">CH0 / CH1 / CH2</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="170" y="474" text-anchor="middle" dominant-baseline="central">Phase A / B / C NTC sensor</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="170" y="488" text-anchor="middle" dominant-baseline="central">VAREF = 5 V  |  12-bit  |  0–4095</text>

  <line x1="170" y1="496" x2="170" y2="520" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="30" y="520" width="280" height="44" rx="8" fill="#F1EFE8" stroke="#5F5E5A" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#444441" x="170" y="537" text-anchor="middle" dominant-baseline="central">Adc_StartGroupConversion()</text>
  <text font-family="sans-serif" font-size="12" fill="#5F5E5A" x="170" y="555" text-anchor="middle" dominant-baseline="central">SW trigger – once at startup</text>

  <path d="M310 542 Q340 542 340 590 Q340 638 310 638" fill="none" stroke="#888780" stroke-width="0.8" stroke-dasharray="4 3" marker-end="url(#arrow)"/>
  <text font-family="sans-serif" font-size="12" fill="#888780" x="348" y="594" dominant-baseline="central">loops</text>
  <text font-family="sans-serif" font-size="12" fill="#888780" x="348" y="608" dominant-baseline="central">auto</text>

  <line x1="170" y1="564" x2="170" y2="588" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="30" y="588" width="280" height="56" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#085041" x="170" y="606" text-anchor="middle" dominant-baseline="central">Adc_Temp_GroupNotify()</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="170" y="622" text-anchor="middle" dominant-baseline="central">Adc_ReadGroup() → TempResultBuf</text>
  <text font-family="sans-serif" font-size="12" fill="#0F6E56" x="170" y="636" text-anchor="middle" dominant-baseline="central">TempDataReady = TRUE</text>

  <line x1="170" y1="644" x2="170" y2="668" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="30" y="668" width="280" height="44" rx="8" fill="#F1EFE8" stroke="#5F5E5A" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#444441" x="170" y="685" text-anchor="middle" dominant-baseline="central">10 ms thermal task</text>
  <text font-family="sans-serif" font-size="12" fill="#5F5E5A" x="170" y="703" text-anchor="middle" dominant-baseline="central">NTC lookup → °C  |  fault check</text>

  <!-- HW GROUP -->
  <rect x="370" y="384" width="280" height="44" rx="8" fill="#FAECE7" stroke="#993C1D" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#712B13" x="510" y="401" text-anchor="middle" dominant-baseline="central">AdcGroup_1  –  HW group</text>
  <text font-family="sans-serif" font-size="12" fill="#993C1D" x="510" y="419" text-anchor="middle" dominant-baseline="central">One-shot  |  High priority</text>

  <path d="M480 340 L480 350 L510 350 L510 384" fill="none" stroke="#888780" stroke-width="1" marker-end="url(#arrow)"/>
  <text font-family="sans-serif" font-size="12" fill="#888780" x="508" y="370" text-anchor="middle" dominant-baseline="central">GTM trigger</text>

  <rect x="370" y="440" width="280" height="56" rx="8" fill="#FAECE7" stroke="#993C1D" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#712B13" x="510" y="458" text-anchor="middle" dominant-baseline="central">CH3 / CH4</text>
  <text font-family="sans-serif" font-size="12" fill="#993C1D" x="510" y="474" text-anchor="middle" dominant-baseline="central">Phase A / B current (shunt amp)</text>
  <text font-family="sans-serif" font-size="12" fill="#993C1D" x="510" y="488" text-anchor="middle" dominant-baseline="central">VAREF = 5 V  |  12-bit  |  0–4095</text>

  <line x1="510" y1="496" x2="510" y2="520" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="370" y="520" width="280" height="44" rx="8" fill="#F1EFE8" stroke="#5F5E5A" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#444441" x="510" y="537" text-anchor="middle" dominant-baseline="central">HW trigger – ADCTrig0</text>
  <text font-family="sans-serif" font-size="12" fill="#5F5E5A" x="510" y="555" text-anchor="middle" dominant-baseline="central">rising edge every 25 µs (PWM mid)</text>

  <text font-family="sans-serif" font-size="12" fill="#888780" x="510" y="578" text-anchor="middle">one-shot per trigger, no loop</text>

  <line x1="510" y1="588" x2="510" y2="600" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="370" y="600" width="280" height="56" rx="8" fill="#FAECE7" stroke="#993C1D" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#712B13" x="510" y="618" text-anchor="middle" dominant-baseline="central">Adc_Current_GroupNotify()</text>
  <text font-family="sans-serif" font-size="12" fill="#993C1D" x="510" y="634" text-anchor="middle" dominant-baseline="central">Adc_ReadGroup() → CurrentResultBuf</text>
  <text font-family="sans-serif" font-size="12" fill="#993C1D" x="510" y="648" text-anchor="middle" dominant-baseline="central">FOC_UpdateCurrentFeedback()</text>

  <line x1="510" y1="656" x2="510" y2="680" stroke="#888780" stroke-width="1.5" marker-end="url(#arrow)"/>
  <rect x="370" y="680" width="280" height="44" rx="8" fill="#F1EFE8" stroke="#5F5E5A" stroke-width="0.5"/>
  <text font-family="sans-serif" font-size="14" font-weight="500" fill="#444441" x="510" y="697" text-anchor="middle" dominant-baseline="central">50 µs FOC ISR context</text>
  <text font-family="sans-serif" font-size="12" fill="#5F5E5A" x="510" y="715" text-anchor="middle" dominant-baseline="central">Phase A &amp; B current feedback</text>

  <!-- EXPLANATION SECTION -->
  <line x1="20" y1="738" x2="660" y2="738" stroke="#B4B2A9" stroke-width="1" stroke-dasharray="6 4"/>
  <rect x="20" y="748" width="640" height="258" rx="10" fill="#F8F8F8" stroke="#DDDDDD" stroke-width="0.8"/>

  <text font-family="sans-serif" font-size="13" font-weight="700" fill="#222222" x="340" y="768" text-anchor="middle" dominant-baseline="central">KEY EXPLANATION POINTS</text>

  <!-- Col 1: Clock Hierarchy -->
  <rect x="30" y="782" width="190" height="16" rx="3" fill="#EEEDFE"/>
  <text font-family="sans-serif" font-size="11" font-weight="700" fill="#3C3489" x="38" y="790" dominant-baseline="central">🕐 Clock Hierarchy</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="38" y="810" dominant-baseline="central">▸ PLL 200 MHz → SPB 100 MHz</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="48" y="826" dominant-baseline="central">→ ADC 20 MHz (÷5)</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="38" y="844" dominant-baseline="central">▸ ~1 µs per 12-bit channel</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="48" y="860" dominant-baseline="central">at fADC = 20 MHz</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="38" y="878" dominant-baseline="central">▸ GTM ref: 100 MHz for PWM</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="48" y="894" dominant-baseline="central">timing &amp; ADC triggering</text>

  <!-- Col 2: SW Group -->
  <rect x="240" y="782" width="190" height="16" rx="3" fill="#E1F5EE"/>
  <text font-family="sans-serif" font-size="11" font-weight="700" fill="#085041" x="248" y="790" dominant-baseline="central">🌡 SW Group – Temperature</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="248" y="810" dominant-baseline="central">▸ Continuous scan of 3 NTC</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="258" y="826" dominant-baseline="central">sensors (Phase A / B / C)</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="248" y="844" dominant-baseline="central">▸ Low priority, SW triggered</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="258" y="860" dominant-baseline="central">once at startup</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="248" y="878" dominant-baseline="central">▸ 10 ms task: raw 12-bit →</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="258" y="894" dominant-baseline="central">°C via NTC LUT + fault check</text>

  <!-- Col 3: HW Group -->
  <rect x="450" y="782" width="190" height="16" rx="3" fill="#FAECE7"/>
  <text font-family="sans-serif" font-size="11" font-weight="700" fill="#712B13" x="458" y="790" dominant-baseline="central">⚡ HW Group – Current</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="458" y="810" dominant-baseline="central">▸ High-priority one-shot:</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="468" y="826" dominant-baseline="central">Phase A/B shunt amp</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="458" y="844" dominant-baseline="central">▸ GTM PWM midpoint trigger</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="468" y="860" dominant-baseline="central">@ 40 kHz (every 25 µs)</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="458" y="878" dominant-baseline="central">▸ Runs inside 50 µs FOC ISR</text>
  <text font-family="sans-serif" font-size="10.5" fill="#333333" x="468" y="894" dominant-baseline="central">for real-time current control</text>

  <!-- Column dividers -->
  <line x1="235" y1="780" x2="235" y2="990" stroke="#DDDDDD" stroke-width="0.8"/>
  <line x1="445" y1="780" x2="445" y2="990" stroke="#DDDDDD" stroke-width="0.8"/>

</svg>`
  },
  {
    q: "Explain Qspi diagram?",
    a: `Diagram: Qspi

Key Labels / Signals:
  - AURIX TC2xx – QSPI Clock Chain & Key Parameters
  - Clock chain: fOSC → PLL → fCPU → fSPB → fQSPI → fSCLK (baud)
  - Crystal Oscillator
  - fOSC = 20 MHz (typical external)
  - x N (PLL multiply)
  - System PLL (fPLL)
  - up to 300 MHz (TC27x / TC29x)
  - ÷ k
  - CPU Clock (fCPU)
  - up to 200 MHz (TC27x)
  - SRI Bus (fSRI)
  - up to 200 MHz | core interconnect
  - SPB Bus (fSPB)
  - up to 100 MHz | peripheral bus
  - ÷ 1..4 (QSPI prescaler)
  - QSPI Module Clock (fQSPI)
  - up to 100 MHz = fSPB / prescaler
  - ÷ (Q+1) (baud divider)
  - QSPI Baud Rate (fSCLK)
  - fQSPI / (Q+1) | max 50 MHz SCK
  - e.g. 100 MHz / 2 = 50 MHz SCK
  - QSPI 0
  - master/slave | 50 Mbit/s max
  - FIFO 16x TX / 16x RX
  - QSPI 1 / 2
  - QSPI 3
  - Key Parameters Reference – AURIX TC2xx QSPI
  - Parameter
  - Value / Range
  - fOSC – crystal oscillator
  - 20 MHz (typical external quartz crystal)
  - fPLL – system PLL output
  - up to 300 MHz (TC27x / TC29x variants)
  - fCPU – CPU core clock
  - up to 200 MHz (TC27x), up to 300 MHz (TC29x)
  - fSRI – system resource bus
  - up to 200 MHz | CPU-to-memory interconnect
  - fSPB – peripheral bus clock
  - up to 100 MHz = fCPU / 2 (typical config)
  - fQSPI – QSPI module clock
  - fSPB / prescaler(1..4) → up to 100 MHz
  - fSCLK – SPI baud rate (SCK pin)
  - fQSPI / (Q+1) | max 50 MHz on wire
  - QSPI instances
  - 4 modules: QSPI0, QSPI1, QSPI2, QSPI3 (TC27x)
  - TX / RX FIFO depth
  - 16 entries each per QSPI module
  - CS lines (SLSO)
  - up to 15 HW chip selects per QSPI module
  - Data frame width
  - 2 – 32 bits per frame (configurable per Job)
  - SPI modes
  - CPOL/CPHA → Mode 0, 1, 2, 3 (all supported)
  - DMA support
  - DMA request triggered on TX/RX FIFO level threshold
  - Async handler modes
  - Interrupt / Polling (Spi_MainFunction) / DMA
  - Buffer type
  - IB (Internal, fixed size) / EB (External, runtime ptr)
  - Baud Rate Calculation Formula
  - Formula:
  - fSCLK = fQSPI / (Q + 1) = fSPB / prescaler / (Q + 1)
  - Example A (max speed):
  - 100 MHz (fSPB) / 1 (prescaler) / 2 (Q+1) = 50 MHz SCK
  - Example B (lower speed):
  - 100 MHz / 1 / 4 = 25 MHz SCK
  - Clock Chain – Explanation
  - 1. fOSC – Crystal Oscillator (20 MHz)
  - The on-board quartz crystal provides a stable 20 MHz reference clock to the PLL. This is the root of the entire
  - clock tree. The exact frequency depends on the board crystal chosen.
  - 2. fPLL – System PLL (up to 300 MHz)
  - The PLL multiplies fOSC to generate the high-speed system clock. On TC27x max is 300 MHz. Configured via
  - SCU_PLLCON registers (NDIV, PDIV, KDIV).
  - 3. fCPU → fSRI / fSPB split
  - fCPU feeds two buses: the SRI bus (same speed, for CPU-to-SRAM/Flash) and the SPB peripheral bus (half speed,
  - 100 MHz max), which clocks all peripherals including QSPI.
  - 4. fQSPI – QSPI Module Clock | 5. fSCLK – Actual SPI Baud Rate
  - The QSPI prescaler (div 1–4) divides fSPB to give fQSPI. The baud divider register (Q) then gives the final SCK
  - frequency on the physical SCLK pin. Maximum SCK = 50 MHz. Each Job can have a different baud setting.
  - AURIX TC2xx | AUTOSAR SPI / QSPI | Clock Chain Reference

SVG Source:
<svg xmlns="http://www.w3.org/2000/svg" width="900" height="1600" viewBox="0 0 900 1600" font-family="Arial, Helvetica, sans-serif">

  <!-- Background -->
  <rect width="900" height="1600" fill="#ffffff"/>

  <!-- Title -->
  <rect x="0" y="0" width="900" height="52" fill="#26215C"/>
  <text x="450" y="33" text-anchor="middle" font-size="18" font-weight="bold" fill="#ffffff">AURIX TC2xx – QSPI Clock Chain &amp; Key Parameters</text>

  <defs>
    <marker id="arr" viewBox="0 0 10 10" refX="8" refY="5" markerWidth="6" markerHeight="6" orient="auto-start-reverse">
      <path d="M2 1L8 5L2 9" fill="none" stroke="#888780" stroke-width="1.5" stroke-linecap="round" stroke-linejoin="round"/>
    </marker>
  </defs>

  <text x="450" y="80" text-anchor="middle" font-size="12" fill="#888780">Clock chain: fOSC → PLL → fCPU → fSPB → fQSPI → fSCLK (baud)</text>

  <!-- Crystal Oscillator -->
  <rect x="300" y="92" width="300" height="48" rx="8" fill="#F1EFE8" stroke="#5F5E5A" stroke-width="1"/>
  <text x="450" y="112" text-anchor="middle" font-size="13" font-weight="bold" fill="#444441">Crystal Oscillator</text>
  <text x="450" y="129" text-anchor="middle" font-size="11" fill="#5F5E5A">fOSC = 20 MHz (typical external)</text>

  <line x1="450" y1="140" x2="450" y2="162" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>
  <text x="462" y="155" font-size="10" fill="#888780">x N  (PLL multiply)</text>

  <!-- System PLL -->
  <rect x="300" y="162" width="300" height="48" rx="8" fill="#EEEDFE" stroke="#534AB7" stroke-width="1"/>
  <text x="450" y="182" text-anchor="middle" font-size="13" font-weight="bold" fill="#3C3489">System PLL  (fPLL)</text>
  <text x="450" y="199" text-anchor="middle" font-size="11" fill="#534AB7">up to 300 MHz  (TC27x / TC29x)</text>

  <line x1="450" y1="210" x2="450" y2="232" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>
  <text x="462" y="226" font-size="10" fill="#888780">÷ k</text>

  <!-- fCPU -->
  <rect x="300" y="232" width="300" height="48" rx="8" fill="#EEEDFE" stroke="#534AB7" stroke-width="1"/>
  <text x="450" y="252" text-anchor="middle" font-size="13" font-weight="bold" fill="#3C3489">CPU Clock  (fCPU)</text>
  <text x="450" y="269" text-anchor="middle" font-size="11" fill="#534AB7">up to 200 MHz  (TC27x)</text>

  <path d="M390 280 L260 304" fill="none" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>
  <path d="M510 280 L640 304" fill="none" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>

  <!-- fSRI -->
  <rect x="110" y="304" width="260" height="48" rx="8" fill="#EEEDFE" stroke="#534AB7" stroke-width="1"/>
  <text x="240" y="324" text-anchor="middle" font-size="13" font-weight="bold" fill="#3C3489">SRI Bus  (fSRI)</text>
  <text x="240" y="341" text-anchor="middle" font-size="11" fill="#534AB7">up to 200 MHz  |  core interconnect</text>

  <!-- fSPB -->
  <rect x="530" y="304" width="260" height="48" rx="8" fill="#EEEDFE" stroke="#534AB7" stroke-width="1"/>
  <text x="660" y="324" text-anchor="middle" font-size="13" font-weight="bold" fill="#3C3489">SPB Bus  (fSPB)</text>
  <text x="660" y="341" text-anchor="middle" font-size="11" fill="#534AB7">up to 100 MHz  |  peripheral bus</text>

  <line x1="660" y1="352" x2="660" y2="370" stroke="#888780" stroke-width="1.5"/>
  <path d="M660 370 L510 394" fill="none" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>
  <text x="662" y="386" font-size="10" fill="#888780">÷ 1..4  (QSPI prescaler)</text>

  <!-- fQSPI -->
  <rect x="300" y="394" width="300" height="48" rx="8" fill="#FAEEDA" stroke="#854F0B" stroke-width="1"/>
  <text x="450" y="414" text-anchor="middle" font-size="13" font-weight="bold" fill="#633806">QSPI Module Clock  (fQSPI)</text>
  <text x="450" y="431" text-anchor="middle" font-size="11" fill="#854F0B">up to 100 MHz  =  fSPB / prescaler</text>

  <line x1="450" y1="442" x2="450" y2="464" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>
  <text x="462" y="458" font-size="10" fill="#888780">÷ (Q+1)  (baud divider)</text>

  <!-- fSCLK -->
  <rect x="300" y="464" width="300" height="60" rx="8" fill="#FAEEDA" stroke="#854F0B" stroke-width="1.5"/>
  <text x="450" y="484" text-anchor="middle" font-size="13" font-weight="bold" fill="#633806">QSPI Baud Rate  (fSCLK)</text>
  <text x="450" y="501" text-anchor="middle" font-size="11" fill="#854F0B">fQSPI / (Q+1)  |  max 50 MHz SCK</text>
  <text x="450" y="516" text-anchor="middle" font-size="11" fill="#854F0B">e.g.  100 MHz / 2  =  50 MHz SCK</text>

  <line x1="450" y1="524" x2="450" y2="546" stroke="#888780" stroke-width="1.5" marker-end="url(#arr)"/>

  <!-- QSPI HW modules -->
  <rect x="60" y="546" width="240" height="60" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="1"/>
  <text x="180" y="568" text-anchor="middle" font-size="13" font-weight="bold" fill="#085041">QSPI 0</text>
  <text x="180" y="585" text-anchor="middle" font-size="11" fill="#0F6E56">master/slave  |  50 Mbit/s max</text>
  <text x="180" y="599" text-anchor="middle" font-size="10" fill="#0F6E56">FIFO 16x TX / 16x RX</text>

  <rect x="330" y="546" width="240" height="60" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="1"/>
  <text x="450" y="568" text-anchor="middle" font-size="13" font-weight="bold" fill="#085041">QSPI 1 / 2</text>
  <text x="450" y="585" text-anchor="middle" font-size="11" fill="#0F6E56">master/slave  |  50 Mbit/s max</text>
  <text x="450" y="599" text-anchor="middle" font-size="10" fill="#0F6E56">FIFO 16x TX / 16x RX</text>

  <rect x="600" y="546" width="240" height="60" rx="8" fill="#E1F5EE" stroke="#0F6E56" stroke-width="1"/>
  <text x="720" y="568" text-anchor="middle" font-size="13" font-weight="bold" fill="#085041">QSPI 3</text>
  <text x="720" y="585" text-anchor="middle" font-size="11" fill="#0F6E56">master/slave  |  50 Mbit/s max</text>
  <text x="720" y="599" text-anchor="middle" font-size="10" fill="#0F6E56">FIFO 16x TX / 16x RX</text>

  <path d="M390 524 L180 546" fill="none" stroke="#888780" stroke-width="1" stroke-dasharray="4 3"/>
  <path d="M450 524 L450 546" fill="none" stroke="#888780" stroke-width="1" stroke-dasharray="4 3"/>
  <path d="M510 524 L720 546" fill="none" stroke="#888780" stroke-width="1" stroke-dasharray="4 3"/>

  <!-- Divider -->
  <line x1="40" y1="628" x2="860" y2="628" stroke="#D3D1C7" stroke-width="1.5" stroke-dasharray="6 4"/>
  <text x="450" y="648" text-anchor="middle" font-size="13" font-weight="bold" fill="#26215C">Key Parameters Reference – AURIX TC2xx QSPI</text>

  <!-- Table header -->
  <rect x="40" y="658" width="280" height="30" rx="4" fill="#26215C"/>
  <rect x="326" y="658" width="534" height="30" rx="4" fill="#26215C"/>
  <text x="180" y="678" text-anchor="middle" font-size="12" font-weight="bold" fill="#ffffff">Parameter</text>
  <text x="593" y="678" text-anchor="middle" font-size="12" font-weight="bold" fill="#ffffff">Value / Range</text>

  <rect x="40" y="688" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="688" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="708" font-size="11" font-weight="bold" fill="#3C3489">fOSC – crystal oscillator</text>
  <text x="341" y="708" font-size="11" fill="#444441">20 MHz (typical external quartz crystal)</text>

  <rect x="40" y="718" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="718" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="738" font-size="11" font-weight="bold" fill="#3C3489">fPLL – system PLL output</text>
  <text x="341" y="738" font-size="11" fill="#444441">up to 300 MHz  (TC27x / TC29x variants)</text>

  <rect x="40" y="748" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="748" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="768" font-size="11" font-weight="bold" fill="#3C3489">fCPU – CPU core clock</text>
  <text x="341" y="768" font-size="11" fill="#444441">up to 200 MHz  (TC27x),  up to 300 MHz (TC29x)</text>

  <rect x="40" y="778" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="778" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="798" font-size="11" font-weight="bold" fill="#3C3489">fSRI – system resource bus</text>
  <text x="341" y="798" font-size="11" fill="#444441">up to 200 MHz  |  CPU-to-memory interconnect</text>

  <rect x="40" y="808" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="808" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="828" font-size="11" font-weight="bold" fill="#3C3489">fSPB – peripheral bus clock</text>
  <text x="341" y="828" font-size="11" fill="#444441">up to 100 MHz  =  fCPU / 2  (typical config)</text>

  <rect x="40" y="838" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="838" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="858" font-size="11" font-weight="bold" fill="#633806">fQSPI – QSPI module clock</text>
  <text x="341" y="858" font-size="11" fill="#444441">fSPB / prescaler(1..4)  →  up to 100 MHz</text>

  <rect x="40" y="868" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="868" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="888" font-size="11" font-weight="bold" fill="#633806">fSCLK – SPI baud rate (SCK pin)</text>
  <text x="341" y="888" font-size="11" fill="#444441">fQSPI / (Q+1)  |  max 50 MHz on wire</text>

  <rect x="40" y="898" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="898" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="918" font-size="11" font-weight="bold" fill="#085041">QSPI instances</text>
  <text x="341" y="918" font-size="11" fill="#444441">4 modules: QSPI0, QSPI1, QSPI2, QSPI3  (TC27x)</text>

  <rect x="40" y="928" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="928" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="948" font-size="11" font-weight="bold" fill="#085041">TX / RX FIFO depth</text>
  <text x="341" y="948" font-size="11" fill="#444441">16 entries each per QSPI module</text>

  <rect x="40" y="958" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="958" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="978" font-size="11" font-weight="bold" fill="#085041">CS lines (SLSO)</text>
  <text x="341" y="978" font-size="11" fill="#444441">up to 15 HW chip selects per QSPI module</text>

  <rect x="40" y="988" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="988" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="1008" font-size="11" font-weight="bold" fill="#085041">Data frame width</text>
  <text x="341" y="1008" font-size="11" fill="#444441">2 – 32 bits per frame  (configurable per Job)</text>

  <rect x="40" y="1018" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="1018" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="1038" font-size="11" font-weight="bold" fill="#085041">SPI modes</text>
  <text x="341" y="1038" font-size="11" fill="#444441">CPOL/CPHA → Mode 0, 1, 2, 3  (all supported)</text>

  <rect x="40" y="1048" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="1048" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="1068" font-size="11" font-weight="bold" fill="#085041">DMA support</text>
  <text x="341" y="1068" font-size="11" fill="#444441">DMA request triggered on TX/RX FIFO level threshold</text>

  <rect x="40" y="1078" width="280" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="1078" width="534" height="30" fill="#ffffff" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="1098" font-size="11" font-weight="bold" fill="#444441">Async handler modes</text>
  <text x="341" y="1098" font-size="11" fill="#444441">Interrupt  /  Polling (Spi_MainFunction)  /  DMA</text>

  <rect x="40" y="1108" width="280" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <rect x="326" y="1108" width="534" height="30" fill="#F1EFE8" stroke="#D3D1C7" stroke-width="0.5"/>
  <text x="55" y="1128" font-size="11" font-weight="bold" fill="#444441">Buffer type</text>
  <text x="341" y="1128" font-size="11" fill="#444441">IB (Internal, fixed size)  /  EB (External, runtime ptr)</text>

  <!-- Baud rate formula -->
  <line x1="40" y1="1152" x2="860" y2="1152" stroke="#D3D1C7" stroke-width="1.5" stroke-dasharray="6 4"/>
  <text x="450" y="1172" text-anchor="middle" font-size="13" font-weight="bold" fill="#26215C">Baud Rate Calculation Formula</text>
  <rect x="40" y="1182" width="820" height="110" rx="10" fill="#EEEDFE" stroke="#534AB7" stroke-width="1"/>
  <text x="60" y="1206" font-size="12" font-weight="bold" fill="#3C3489">Formula:</text>
  <text x="60" y="1224" font-size="12" font-family="Courier New, monospace" fill="#26215C">  fSCLK  =  fQSPI / (Q + 1)  =  fSPB / prescaler / (Q + 1)</text>
  <text x="60" y="1248" font-size="12" font-weight="bold" fill="#3C3489">Example A  (max speed):</text>
  <text x="60" y="1265" font-size="12" font-family="Courier New, monospace" fill="#26215C">  100 MHz (fSPB) / 1 (prescaler) / 2 (Q+1)  =  50 MHz SCK</text>
  <text x="460" y="1248" font-size="12" font-weight="bold" fill="#3C3489">Example B  (lower speed):</text>
  <text x="460" y="1265" font-size="12" font-family="Courier New, monospace" fill="#26215C">  100 MHz / 1 / 4  =  25 MHz SCK</text>

  <!-- Explanation -->
  <line x1="40" y1="1308" x2="860" y2="1308" stroke="#D3D1C7" stroke-width="1.5" stroke-dasharray="6 4"/>
  <text x="450" y="1328" text-anchor="middle" font-size="13" font-weight="bold" fill="#26215C">Clock Chain – Explanation</text>
  <rect x="40" y="1338" width="820" height="220" rx="10" fill="#F1EFE8" stroke="#B4B2A9" stroke-width="1"/>
  <text x="60" y="1360" font-size="12" font-weight="bold" fill="#26215C">1. fOSC – Crystal Oscillator (20 MHz)</text>
  <text x="60" y="1378" font-size="11" fill="#444441">  The on-board quartz crystal provides a stable 20 MHz reference clock to the PLL. This is the root of the entire</text>
  <text x="60" y="1393" font-size="11" fill="#444441">  clock tree. The exact frequency depends on the board crystal chosen.</text>
  <text x="60" y="1413" font-size="12" font-weight="bold" fill="#26215C">2. fPLL – System PLL (up to 300 MHz)</text>
  <text x="60" y="1431" font-size="11" fill="#444441">  The PLL multiplies fOSC to generate the high-speed system clock. On TC27x max is 300 MHz. Configured via</text>
  <text x="60" y="1446" font-size="11" fill="#444441">  SCU_PLLCON registers (NDIV, PDIV, KDIV).</text>
  <text x="60" y="1466" font-size="12" font-weight="bold" fill="#26215C">3. fCPU → fSRI / fSPB split</text>
  <text x="60" y="1484" font-size="11" fill="#444441">  fCPU feeds two buses: the SRI bus (same speed, for CPU-to-SRAM/Flash) and the SPB peripheral bus (half speed,</text>
  <text x="60" y="1499" font-size="11" fill="#444441">  100 MHz max), which clocks all peripherals including QSPI.</text>
  <text x="60" y="1519" font-size="12" font-weight="bold" fill="#26215C">4. fQSPI – QSPI Module Clock  |  5. fSCLK – Actual SPI Baud Rate</text>
  <text x="60" y="1537" font-size="11" fill="#444441">  The QSPI prescaler (div 1–4) divides fSPB to give fQSPI. The baud divider register (Q) then gives the final SCK</text>
  <text x="60" y="1552" font-size="11" fill="#444441">  frequency on the physical SCLK pin. Maximum SCK = 50 MHz. Each Job can have a different baud setting.</text>

  <!-- Footer -->
  <rect x="0" y="1580" width="900" height="20" fill="#26215C"/>
  <text x="450" y="1594" text-anchor="middle" font-size="10" fill="#AFA9EC">AURIX TC2xx  |  AUTOSAR SPI / QSPI  |  Clock Chain Reference</text>

</svg>`
  },
];

// Total: 149 flashcards