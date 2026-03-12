# vscpde_c_practice
all programs available
## C Question

# ascii table
    ascii value table decimal
    '0' = 0x30
    'A' = 0x41
    'a' = 0x61

    convert lower case to upper case  97-65=32 , do -32 each ascii value
    str[i] = str[i] - 32;   // or str[i] - ('a' - 'A')

    convert upper case to lower case           , do +32 each asci value
    str[i] = str[i] + 32;   // or str[i] + ('a' - 'A')

# prmitive data types
    In C, the primitive (basic) data types are the built-in types provided by the language itself: int, char, float, and double

# Storage classes:
    extern
    auto
    reg
    static

# Volatile Keyword in C

    The **`volatile`** keyword is a type qualifier in C that tells the compiler:
    > "This variable may change at any time, outside the control of the program."

    ---

    ## Key Points
    - **Prevents optimization**: The compiler must always fetch the variable’s value directly from memory, not assume it stays constant.
    - **External changes**: Useful when values can be modified by hardware, interrupts, or other threads.
    - **Instruction ordering**: The compiler must not reorder reads/writes of volatile variables.

    ---

    ## Example
    ```c
    volatile int status;

    while (status == 0) {
        // Wait until hardware or interrupt changes 'status'
    }


# qualifiers :are keywords that modify the behavior of variables and data types
    const
    volatile

# Identifier: identifier is simply the name used to identify variables, functions, arrays, structures, or any other user-defined element in a program. It’s how you give a meaningful label to entities in your code.
    int a;
    void add()

# memor layout
    +-------------------+
    |       Stack       |  ← grows downward
    +-------------------+
    |       Heap        |  ← grows upward
    +-------------------+
    |       .BSS         |
    +-------------------+
    |       .Data        |
    +-------------------+
    |       .Text        |
    +-------------------+

    .txt, .data is Assembler directives are commands for the assembler
     to control how data and code are organized, processed, or stored

# compilation stage

    [ Preprocessor ] --> .i --> [ Compiler ] --> .s --> [ Assembler ] --> .o --> [ Linker ] --> .exe / .bin / .hex / .mot
                                                                                           +
                                                                                           + DLL files (runtime linking)



# Embedded System Startup Flow or reset to main or power on

When an embedded system powers on:

- **Reset Vector**: CPU fetches the reset vector, which points to the startup code (written in assembly).
- **Startup Code**:
  - Sets up the **stack pointer**.
  - Copies initialized variables from **FLASH to RAM** (`.data` section).
  - Zeros out uninitialized variables (`.bss` section).
- **SystemInit()**: Configures system clocks and hardware setup.
- **main()**: Application entry point.  
  - In embedded systems, `main()` should **never return**.


# Dynamic memoy allocation 
    malloc:
     used for dynamic memory allocation, reserving a block of memory on the heap at runtime
     this will allocated osme bytes called book keppeing, it holeds how many bytes its taken

    int *ptr =malloc(sizeof(int));

    calloc:
    Allocates and initializes memory to zero.
       int *ptr =calloc(10, (sizeof(int));

    realloc:
    Resizes existing memory blocks
    ptr = (int *)realloc(ptr, 10 * sizeof(int));

    free:
     Releases memory

   # google interview
    how to create our own malloc, my malloc?
        simply create statci int char[500] --> this will exceeds data segment and cross heap section

        we cant use pointer like assigning heap adress to ptr, next moment if we use malloca this adress wil be occupied

---



## asm

# assembler directive
 commands in assembly language source code that instruct the assembler software how to process the program, rather than being translated into machine code instructions
 in Linker we have .bss, .data, .txt this are assebler directiver


## Micro Controller related 
 # Sequence
Power ON / Reset → Reset Vector → Startup Code → SystemInit() → main()


## Bit Manipulation

Checking if a number is power of 2

Counting set bits

XOR tricks (finding unique element)

## Data structure algorithm (DSA)
    Two Pointers Technique:
        Sliding Window Problems 







