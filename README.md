# vscpde_c_practice
all programs available
## C Question

# ascii table
    ascii value table decimal
    '0' = 48
    'A' = 65
    'a' = 97

    convert lower case to upper case  97-65=32 , do -32 each ascii value
    str[i] = str[i] - 32;   // or str[i] - ('a' - 'A')

    convert upper case to lower case           , do +32 each asci value
    str[i] = str[i] + 32;   // or str[i] + ('a' - 'A')


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
    |       BSS         |
    +-------------------+
    |       Data        |
    +-------------------+
    |       Text        |
    +-------------------+

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

---

# Sequence
Power ON / Reset → Reset Vector → Startup Code → SystemInit() → main()

## asm

# assembler directive







