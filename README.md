Author : Sudhir Acharya
### what are interview Interview Structure?
- Basic C Questions
- Programming
  - Bit Manipulation
  - DSA / Array
- Project Explanation
- Problems You Have Faced

### What is my Professional Summary",
Senior Embedded Software Engineer with 11+ years of experience in automotive embedded systems, specializing in
device driver development, AUTOSAR MCAL, and low-level firmware engineering.`


### What are my Technical Skills",
Device Drivers: ADC, SPI, I2C, UART, PORT, GPIO, DMA & AUTOSAR MCAL
AUTOSAR Stack: MCAL, RTE, BSW configuration using EB Tresos; Vector DaVinci
Microcontrollers / SoCs: Infineon AURIX TriCore TC2xx, NXP MCU, ARM Cortex architecture
Protocols / Interfaces: SPI, I2C, UART, CAN
RTOS: OSEK-based RTOS, task/ISR scheduling, interrupt handling
Debugging & Test Tools: TRACE32 (JTAG), Oscilloscope, Logic Analyzer, USB Analyzer, CANoe, HIL setups
Programming Languages: Embedded C, Python, MATLAB, MISRA-C guidelines
Build & DevOps: Linux, Docker, cross-compilation, CI/CD pipelines, GitHub, Makefile, ARM GCC toolchain
Requirements & SCM: IBM DOORS (traceability), MKS/PTC Integrity, SW-E5 process compliance`


### What is my Experience",
Continental Automotive, Bangalore
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
• Developed drivers for ADC and DAC modules to support sensor data acquisition and signal conversion`


### What are my Projects",
ADC and Timer/Watchdog Driver Development | Infineon AURIX TC2xx, EB Tresos, TRACE32
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
• Performed rigorous unit testing to validate functionality


### ADC Project
![ADC SW and HW Group Block Diagram](doc/adc_block_diagram.svg)

## QSPI Project
![QSPI](doc/qspi.svg)

## DMA Example using 6 channel ADC
![DMA Channel](doc/6CHADC1DMA.svg)


### what is prmitive data types
    Type       Size      Range (signed)
    -------    ------    ----------------------------
    char       1 byte    -128 to 127
    int        4 bytes   -2,147,483,648 to 2,147,483,647
    float      4 bytes   ~6-7 decimal digits
    double     8 bytes   ~15-16 decimal digits

### what are the Storage classes:
    Keyword     Lifetime     Scope          Stored In
    ---------   ----------   ------------   -----------
    1.auto        Block        Local          Stack
    2.static      Program      Local/File     .data / .bss
    3.extern      Program      Global         .data
    4.register    Block        Local          CPU Register (hint only)

### what is qualifiers ?
    qualifiers are keywords that modify the behavior of variables and data types
    volatile
    const

### what are the type modifier in c
    short, long, signed, unsigned

### Derived dataypes
    Structure
    Union

### wha are the Userdefined data types 
    Enum
    Typedef

## what is typecasting and type conversion
    implicit->autoatically done by compiler for two compatiable data types
    explicit ->done by programmer using typecast operator to make sure no valuble data los
    type promotion-> smaller data to large one

### what is Identifier: 
identifier is simply the name used to identify variables, functions, arrays, structures, 
or any other user-defined element in a program. It’s how you give a meaningful label to entities in your code.
    int a;
    void add()

### Volatile Keyword in C
    Volatile is a qualifier that is applied to a variable when it is declared.
    It tells the compiler that the value of the variable may change at any time-without any action being taken by the code the compiler finds nearby.

    volatile uint32_t *TIMER_REG = (uint32_t *)0x40000000;

    while (*TIMER_REG == 0) {
        // Without volatile: compiler reads once, caches value
        //                   --> loop never exits (wrong!)
        // With volatile:    reads from HW register every iteration (correct)
    }

## what is the use of const keyword in c
    The const (constant) qualifier is a type qualifier in C and C++ programming languages 
    used to declare that a variable's value is fixed, read-only, 
    and cannot be modified after initialization. 
    It acts as a compiler-enforced constraint to prevent accidental modifications,
     enhancing code security and allowing optimization. 

### What is const volatile — does it make sense?

    const volatile uint32_t *STATUS_REG = (uint32_t *)0x40000010;

    YES — makes perfect sense for read-only hardware status registers:
    const    --> value cannot change, compiler enforces read-only
    volatile --> value can change outside compiler's knowledge,
                 prevents compiler optimization
    
    example:
    const volatile int  var

# Declaration vs Definition in C

> **Key rule:** Every definition is also a declaration, but not every declaration is a definition.

| Aspect | Declaration | Definition |
|--------|-------------|------------|
| **What it does** | Tells the compiler the name and type — no memory allocated | Actually creates the entity — memory is allocated |
| **Memory** | No storage allocated | Storage allocated |
| **Can repeat?** | Yes — multiple declarations are fine | No — only one definition per translation unit (ODR) |
| **Variable** | `extern int x;` | `int x = 5;` or `int x;` |
| **Function** | `int add(int a, int b);` (prototype) | `int add(int a, int b) { return a+b; }` |
| **Struct** | `struct Point;` (forward decl) | `struct Point { int x; int y; };` |
| **Typical location** | Header file `.h` | Source file `.c` |
| **Linker sees?** | No — compiler only | Yes — linker resolves symbols to this |
| **typedef** | `typedef struct Node Node;` | `typedef struct { int val; } Node;` |
| **Key rule** | Declaration is a promise to the compiler | Definition is the fulfillment of that promise |

---

## Edge Cases

- `int x;` at file scope is **both** a declaration and a definition (implicit `= 0`).
- `extern int x;` is purely a declaration — if no `.c` file defines `x`, you get a linker error.
- Function prototypes in headers are declarations; the body in `.c` is the definition.
- `struct Point;` is a forward declaration — useful to break circular header dependencies.

---

## Quick Example

```c
/* header: foo.h */
extern int counter;          /* declaration only */
int add(int a, int b);       /* function declaration (prototype) */
struct Node;                 /* forward declaration */

/* source: foo.c */
int counter = 0;             /* definition — memory allocated */
int add(int a, int b) {      /* function definition */
    return a + b;
}
struct Node {                /* struct definition */
    int val;
    struct Node *next;
};
```
    
## What is  directrives in C
    pre-prcoessor directive: #include, #ifdef
    assembler Directive: .data , .bss, .section
    Compiler directive: #pragma pack

## what is Pre-prcoessor direcive
    #include <stdio.h>       // include system header
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
    #warning "message"       // compile warning (GCC extension)

## what is assembler directive
 commands in assembly language source code that instruct the assembler software how to process the program,
 rather than being translated into machine code instructions
 in Linker we have .bss, .data, .txt this are assebler directiver

### what is compiler Directive
    Instructions to the compiler during compilation. Tells it how to compile, optimize, or handle specific code.

    #pragma is a compiler-specific directive.
    It gives special instructions to the compiler that are not part of standard C syntax.

    #pragma pack(n)Set structure member alignment to n bytes

###  Error in embedded C

| Error Type        | When Detected      | Tool                  | Output                       |
|-------------------|--------------------|-----------------------|------------------------------|
| Compiler Error    | Compile time       | GCC / armcc           | No .o file generated         |
| Linker Error      | Link time          | LD / armlink          | No .elf / .hex generated     |
| Runtime Error     | Execution on target| Debugger / TRACE32    | HardFault / wrong behavior   |
| Warning           | Compile time       | GCC                   | Binary generated (risky)     |
| Logical Error     | Testing/Validation | Logic analyser / CANoe| Wrong output                 |
| Preprocessor Error| Pre-compile        | CPP                   | No .o file generated         |

segmentaion fault:
Access memory you don't own — NULL deref, out-of-bounds array, stack overflow, use-after-free

### what is inline fucntion
“Inline” Function is a provision or feature provided by the compiler. Inline is a request made to the compiler to replace the inline function call with the function definition.


inline void fun(/*fun argument */)
{
    /* Function source Code */
}
When a normal function call happens function creates its stack in the main stack and initializes all local variables. After completion of function call return value is given back if any and stack is destroyed. Much time is consumed in stack operation. Hence for small functions, Inline function is beneficial as the call is replaced by definition, so no external stack is created and operations are much faster for small, commonly-used functions.

### Undefined Behavior in C

Undefined Behavior (UB) refers to program operations for which the C standard imposes **no requirements**.  
When UB occurs, the compiler is free to do anything: produce correct output, wrong output, crash, or even behave unpredictably.  
The standard literally says: *"anything can happen."*

#### Causes and Examples

| **[Cause](ca://s?q=Causes_of_Undefined_Behavior_in_C)** | **Example Code** |
|-----------------|------------------|
| **[Null pointer dereference](ca://s?q=Null_pointer_dereference_in_C)** | `int *p = NULL; *p = 5;` |
| **[Out-of-bounds array access](ca://s?q=Out_of_bounds_array_access_in_C)** | `int a[3]; a[5] = 1;` |
| **[Use of uninitialized variable](ca://s?q=Uninitialized_variable_in_C)** | `int x; printf("%d", x);` |
| **[Signed integer overflow](ca://s?q=Signed_integer_overflow_in_C)** | `int x = INT_MAX; x++;` |
| **[Multiple modifications without sequence point](ca://s?q=Sequence_point_in_C)** | `i = i++ + ++i;` |
| **[Dereferencing freed memory](ca://s?q=Dereferencing_freed_memory_in_C)** | `free(p); *p = 1;` |
| **[Returning pointer to local variable](ca://s?q=Returning_pointer_to_local_variable_in_C)** | `int* f() { int x=1; return &x; }` |
| **[Strict aliasing violation](ca://s?q=Strict_aliasing_violation_in_C)** | `float *f; int *i = (int*)f; printf("%d", *i);` |
| **[Invalid shift operations](ca://s?q=Invalid_shift_operations_in_C)** | `x = 1 << 32; // on 32-bit int` |
| **[Stack overflow](ca://s?q=Stack_overflow_in_C)** | Deep recursion or very large local arrays |



### Inline Function vs Macro

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

### what is side of MACRO instead of using inline function?
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

### what is the diffrence between Structure vs Union
    Feature           struct                              union
    -----------       ------------------------------      ------------------------------
    Memory            Sum of all member sizes             Size of largest member only
    Storage           Each member has its own memory      All members share same memory
    Access            All members accessible anytime      Only last-written member valid
    Use case          Group related data fields            Memory-efficient variant types
    Padding           Yes — compiler may add padding      Yes — based on largest member

### what is the diffrence between typedef vs #define

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

    Example:
    int add(int a, int b) {
        int c = a + b;   // c is on the stack, local to this call
        return c;
    }

    what is the use?
      That’s why you can call add(2,3) and add(5,7) at the same time FROM DIFFRENT THREAD— each call has its own c.

### Polymorphism in C++
     Polymorphism means **one interface, multiple behaviors**.
    Two types: Compile time and Runtime.

   
### Whats  Function Overloading — Compile Time Polymorphism
        Same function name, different parameter types or count.
        Compiler decides which function to call at **compile time**.

        int add(int a, int b)         { return a + b; }
        float add(float a, float b)   { return a + b; }

### Whatis  Function Overriding — Runtime Polymorphism

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

#### what is  array vs pointer

    int main() {
        int a[] = {1, 2, 3};
        int *p = a;
        printf("%d", *(p + 2));
         printf("%d", p[2]);
        return 0;
    }

    result : 03

### ASCII & Characters

    '0' = 0x30 = 48
    'A' = 0x41 = 65
    'a' = 0x61 = 97
    Difference between upper and lower case = 32

    Lowercase to Uppercase:   str[i] = str[i] - 32
    Uppercase to Lowercase:   str[i] = str[i] + 32


### What are th Pointers declartion and meaning?

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

### VIP Pinter question"
1.typedef char *charp;
const charp *p;  // which one is const here?
	const charp *p` → rewrites to `char * const p` — the **ADDRESS** is const, not the `char`
	typedef` is not text substitution


2.int *ptr1, ptr2; // what does this mean?
		 `ptr1` is pointer to `int`, `ptr2` is plain `int`
		 
3.typedef char *charp;
  charp p1, p2;    // are both pointers?
	`charp p1, p2` — yes, both are `char*`
	typedef` carries pointer-ness to all variables
    
### what is the Difference between *ptr++, (*ptr)++, and *++ptr?

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

### what are the Pointer Types?
    1.Null pointer
    2.wild pointer
    3.dangling pointer
    4.double pointer
    5.void pointer

## what is null nul, wild, dangling pointer

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

### what double, void pointer
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

### Array Pointer vs Function Pointer

    | Aspect      | Array Pointer          | Function Pointer         |
    |-------------|------------------------|--------------------------|
    | Points to   | Data (RAM)             | Code (Flash / .text seg) |
    | Memory seg  | Stack / Heap / BSS     | .text segment            |
    | Operation   | Read / write the value | Call / execute only      |
    | Arithmetic  | Valid                  | Not meaningful           |
### array vs pointer
| Aspect              | Case 1: Pointer + malloc        | Case 2: Fixed Array        |
|---------------------|---------------------------------|-----------------------------|
| Declaration         | `int *a = NULL;`                | `int a[] = {20};`           |
| Memory location     | Heap (dynamic allocation)       | Stack (automatic allocation)|
| Allocation          | `malloc(sizeof(int))` → manual | Compiler allocates automatically |
| Size                | Decided at runtime (here 1 int) | Fixed at compile time (here 1 int) |
| Initialization      | Must assign after malloc        | Initialized with `{20}`     |
| Flexibility         | Can allocate any size, resize   | Size fixed, cannot change   |
| Cleanup             | Must call `free(a)`             | No manual cleanup needed    |
| Lifetime            | Persists until `free()` or program ends | Persists until function scope ends |
| Syntax for access   | `a[0]` via pointer arithmetic   | `a[0]` via direct indexing  |

### what is the diffrence *a[10] vs (*a)[10]
    *a[10]   -> [] first, array of pointers
    (*a)[10] -> *  first, pointer to an array

    /* array of pointers */
    int x = 1, y = 2, z = 3;
    int *a[3] = {&x, &y, &z};
    printf("%d\n", *a[1]);       /* 2 */

    /* pointer to array */
    int arr[10] = {0};
    int (*p)[10] = &arr;
    printf("%d\n", (*p)[3]);     /* 0 */

### how to type caste pointer adress
    (void *) ptr
    (char *)ptr

### Explain memory layout in C

    High Address
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
    Low Address

### Explain startup code task?
    in startup  .ro data copied to .data section

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

### What is a Reset Vector?

    Fixed memory address the CPU fetches and jumps to after reset.
    On ARM Cortex-M:
        0x00000000 = initial Stack Pointer value
        0x00000004 = Reset Handler address (start of startup code)

### Embedded System Startup Flow or reset to main or power on

- **Reset Vector**: CPU fetches the reset vector, which points to the startup code (written in assembly).
- **Startup Code**:
  - Sets up the **stack pointer**.
  - Copies initialized variables from **FLASH to RAM** (`.data` section).
  - Zeros out uninitialized variables (`.bss` section).
- **SystemInit()**: Configures system clocks and hardware setup.
- **main()**: Application entry point.  
  - In embedded systems, `main()` should **never return**.

### Dynamic Memory Allocation

    malloc(size)        allocate, memory is UNINITIALIZED (garbage)
    calloc(n, size)     allocate n items, memory is ZERO-INITIALIZED
    realloc(ptr, size)  resize existing allocation (may move memory)
    free(ptr)           release -- always set ptr = NULL after!

### how to create our own malloc, my malloc?
    simply create statci int char[500] --> this will exceeds data segment and cross heap section
    we cant use pointer like assigning heap adress to ptr, next moment if we use malloca this adress wil be occupied

### What is a memory leak? How to detect?

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

### Why is malloc avoided in safety-critical embedded?

    - Non-deterministic timing (MISRA C rule violation)
    - Heap fragmentation over time
    - Memory leaks cause silent failure
    - Limited RAM on MCU gets exhausted unpredictably

    Alternative -- static memory pool:

        uint8_t pool[NUM_BUFS][BUF_SIZE];
        uint8_t inUse[NUM_BUFS] = {0};

### what are the MISRA-C Violations

1.  Recursion                   --> not allowed (Rule 17.2)
                                    unbounded stack usage, unpredictable depth

2.  Dynamic memory allocation   --> not allowed (Rule 21.3)
    malloc / calloc / realloc      heap fragmentation, non-deterministic timing
    free                           use static arrays or memory pools instead

3.  Unbounded loops             --> not allowed (Rule 15.4)
    while(1), for(;;)              every loop must have a fixed upper bound
                                    so termination can be proven


5.  Multiple return             --> not allowed (Rule 15.5)
    (multiple return in func)      one entry, one exit per function

6.  Pointer arithmetic          --> restricted (Rule 18.4)
    ptr++, ptr+n                   use array indexing [] instead



8.  Union                       --> restricted (Rule 19.2)
                                    undefined behaviour on type-punning

9.  Implicit type conversion    --> not allowed (Rule 10.1 / 10.3)
    int + char, etc                always cast explicitly

### What is interrupt latency?
    Time from interrupt signal assertion to first ISR instruction executing.
    Factors: CPU pipeline flush, saving context (stacking registers), priority.
    ARM Cortex-M3: typically 12 clock cycles minimum latency.

### What is a race condition between ISR and main? How to fix?
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


### What is interrupt priority and nesting?

    Higher priority interrupts can preempt lower priority ISRs.
    ARM Cortex-M: lower number = higher priority (0 = highest).
    Configured via NVIC (Nested Vectored Interrupt Controller).

        NVIC_SetPriority(UART1_IRQn, 1);   // high priority
        NVIC_SetPriority(TIM2_IRQn,  5);   // lower priority


### divide and multiply
x = x >> 1;   // x / 2
x = x >> 2;   // x / 4
x = x >> 3;   // x / 8
x = x >> 4;   // x / 16
x = x >> n;   // x / 2^n


x = x << 1;   // x * 2
x = x << 2;   // x * 4
x = x << 3;   // x * 8
x = x << 4;   // x * 16
x = x << n;   // x * 2^n


### What is a string literal and example?",
int main()

    // This is a string literal
    // Stored in read-only memory
    // You cannot modify it

    char *p = "hello";

    // Undefined behavior (modifying string literal)
    p[0] = 'y';
    p[5] = 'w';

    std::cout << p;
}


# C Constants — Decision Table
	const int var =5
	#define var 5
	ennum{ var =5}

| Need | Use |
|------|-----|
| Pass a pointer | `static const` (1) |
| Array dimension (global/static scope) | `#define` or `enum` |
| Switch case / static initializer | `#define` or `enum` |
| Debugger symbol visibility | `static const` or `enum` |
| `#ifdef` / preprocessor detection | `#define` only |
| Avoid macro side-effects | `static const` or `enum` |


## Whats is NVIC Table

    | Letter | Full Word  | What It Does                                           |
    |--------|------------|--------------------------------------------------------|
    | N      | Nested     | Higher priority IRQ can interrupt a lower priority ISR |
    | V      | Vectored   | Each interrupt has a fixed address in the vector table |
    | I      | Interrupt  | Handles hardware interrupt signals from peripherals    |
    | C      | Controller | Hardware block that manages priorities, enabling, pending |

### Dynamic memory allocation

    // 1. malloc — allocates raw uninitialized memory
    int *ptr = malloc(sizeof(int));          // contents are garbage

    // 2. calloc — allocates AND zero-initializes
    int *ptr = calloc(100, sizeof(int));     // 100 ints, all set to 0

    // 3. realloc — resize an existing allocation
    ptr = realloc(ptr, 200 * sizeof(int));   // grow/shrink, may move ptr

    // 4. free — release back to heap
    free(ptr);                               // how does it know the size? ↓

    Note:When you call malloc(100), the allocator doesn't just give you 100 bytes. 
        It secretly allocates a metadata block just before your pointer:


##  Watchdog Timer

    Hardware timer that resets the MCU if not kicked within a timeout.
    Detects software hangs and crashes.
    Essential for unattended and safety-critical systems.

## RTOS Concepts

    RTOS = Real-Time Operating System
    Schedules multiple tasks with deterministic timing.
    Guarantees response within a deadline.

## stack, que, ring buffer

| Property      | Stack                          | Queue                          | Ring Buffer                        |
|---------------|--------------------------------|--------------------------------|------------------------------------|
| Concept       | Abstract data structure        | Abstract data structure        | Concrete implementation            |
| Order         | LIFO - Last In First Out       | FIFO - First In First Out      | FIFO - First In First Out          |
| Insert        | Push - adds to TOP             | Enqueue - adds to REAR         | Write at head pointer              |
| Remove        | Pop - removes from TOP         | Dequeue - removes from FRONT   | Read at tail pointer               |
| Access        | Top only                       | Front only                     | Head and tail pointers             |
| Size          | Dynamic or fixed               | Dynamic or fixed               | Always fixed                       |
| When full     | Stack overflow                 | Queue full error               | Overwrites old data                |
| Memory        | Array or linked list           | Array or linked list           | Fixed array only                   |
| Wrap around   | No                             | No                             | Yes - index % SIZE                 |
| Time O(n)     | Push O(1) / Pop O(1)           | Enqueue O(1) / Dequeue O(1)    | Read O(1) / Write O(1)             |
| Use case      | Function calls, undo, recursion| Task scheduling, BFS           | UART, audio, DMA, sensor logging   |
| Embedded use  | Call stack, ISR nesting        | Message queues in RTOS         | UART, SPI, CAN buffers in drivers  |
| RTOS example  | FreeRTOS task stack            | FreeRTOS xQueue                | DMA circular mode, UART ring buf   |
| Your code     | Implicit call stack in main()  | Concept used in USART IRQ      | rx_buff[] in USART2_IRQHandler     |

### type castr, protmotion
| Expression               | Result    | Rule                        | Reason                                                              |
|--------------------------|-----------|-----------------------------|---------------------------------------------------------------------|
| `1 > 0`                  | 1 (true)  | basic                       | straightforward signed comparison                                   |
| `1U > -1`                | 0 (false) | unsigned wins               | -1 cast to unsigned → UINT_MAX, so 1U > UINT_MAX is false          |
| `(unsigned short)1 > -1` | 1 (true)  | integer promotion           | unsigned short fits in signed int → both sides signed → 1 > -1 true|
| `-1L > 1U` (x86-64)      | 0 (false) | long > int, promote to long | uint fits in long → signed compare → -1L > 1L is false             |
| `-1L > 1U` (x86)         | 1 (true)  | long == int, no promotion   | uint cannot promote → unsigned compare → UINT_MAX > 1U is true     |
| `SCHAR_MAX == CHAR_MAX`  | 1 (true)  | impl-defined                | x86/x86-64 ABI defines char as signed; not guaranteed by standard  |
| `UINT_MAX + 1`           | 0         | unsigned wraparound         | defined by C standard, always wraps mod 2^N                        |
| `INT_MAX + 1`            | UB        | signed overflow             | signed overflow is undefined behavior, compiler can do anything    |
| `-INT_MIN`               | UB        | signed overflow             | two's complement has no representable positive inverse for INT_MIN |
| `INT_MIN % -1`           | UB        | signed overflow             | result would be INT_MAX+1 which overflows                          |
| `x << 0` (x negative)   | UB        | left shift rule             | negative values cannot be left-shifted even by zero                |
| `x << 1` (large x)      | UB        | left shift rule             | shifting 1 into or past sign bit is UB in C99                      |
| `x << 31` (x != 0)      | UB        | left shift rule             | only x=0 is safe; any other value risks hitting sign bit           |
| `x << 32`               | UB        | left shift rule             | shift amount >= bit width of promoted type is always UB            |



## what is inheritance
Inheritance   = child gets parent's properties and methods

## MCU
Diffrenc between timer and counter
Timer   = counts internal clock pulses  (measures TIME)
Counter = counts external event pulses  (measures EVENTS)

### Embedded systems worst practices?
Uninitialized exception vectors (you know, for the ones that "will never be reached")
Say it with me: Global variables. Especially ones shared between ISRs and tasks (or foreground loops) without protection.
Failure to use "volatile" where necessary.
Having routines that DisableInterrupts() and then EnableInterrupts() paired up. Got that? Not RestoreInterrupts(), but ENABLE. Yeah, nesting.
No GPIOs to toggle when testing.
No testpoints on board.
No LEDs or serial port for viewing run-time system status.
No measurement of how busy/idle the CPU is.
Use of inline assembly for all but the most dire of cases. Write a quick callout.
Using for (i = 0; i < 1000; i++) { } to "delay a bit". Yeah, that's not gonna bite you in a hundred different ways....
Not using const everywhere possible to preserve RAM and reduce boot time (no copying / init of variables)






