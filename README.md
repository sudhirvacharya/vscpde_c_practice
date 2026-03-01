# vscpde_c_practice
all programs available

# Storage classes:
    extern
    auto
    reg
    static

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

# compilation state

[ Preprocessor ] --> .i --> [ Compiler ] --> .s --> [ Assembler ] --> .o --> [ Linker ] --> .exe / .bin / .hex / .mot
                                                                                           +
                                                                                           + DLL files (runtime linking)






