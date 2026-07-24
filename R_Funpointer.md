# Uses of Function Pointers in C

## 1. Callbacks
The most common use — pass a function to be called later, without hardcoding it.
- Sorting: `qsort()` takes a comparator function pointer so the same sort logic works for any data type or ordering.
- GUI toolkits: `CreateButton(..., onClick)` — the button calls `onClick` when clicked; timer expiry callbacks work the same way.
- Async operations: register a function to run when a HW interrupt fires or a network call completes.
- Thread creation: `pthread_create()` takes a function pointer as the thread's entry point.

## 2. Table-driven code / arrays of function pointers
Replace long `switch`/`if-else` chains with a lookup table.
```c
void (*funcArray[])(void) = {func0, func1, func2, func3, funcX};
funcArray[a]();
```
- Input handlers: e.g. a 26-entry array indexed by `input - 'A'` instead of a switch over letters.
- Shell command tables: macros register each command's function pointer, help text, and options into a struct array placed in a special memory section.
- IR remote / button handling: a table maps input code to the function to call.

## 3. Finite State Machines (FSM)
Each state maps to a handler function via a pointer, often stored in an array indexed by "current state." Stepping the machine = calling the function at the current index, which processes the state and updates the index to the next one.
- Keeps the FSM definition in one place (the array).
- Can be extended to run multiple independent state machines in parallel (array of function pointers, loop over each, no shared state array needed if each function returns/sets its own next-state pointer).
- Real examples: message parsing/comms protocols, a robotic guitar tuner (separating motor-turning states from pitch-detection states to avoid vibration interference).

## 4. Interrupt vectors
Arrays of function pointers used directly by hardware — each vector table entry points to (or encodes, e.g. divided by 4/8 to save bits) the ISR for that interrupt source.

## 5. Dependency injection / dependency inversion
High-level code depends on an abstraction (a function pointer signature) rather than a concrete low-level implementation.
- Example: a UART send function takes a function pointer for the actual transmit; in production it points to the real UART driver, in test it points to a routine that verifies the "sent" data.
- `qsort()` again fits this pattern — the sort algorithm doesn't depend on the data type or comparison logic, only on the abstraction (a compare function).

## 6. Binding separately built components together
Used when one build/project must supply functions to a separately built project, without hard-linking.
- PC BIOS-style function tables (caller knows `writeDisk()` is entry #7, `readDisk()` is entry #8).
- Bootloaders exposing a fixed function table.
- Dynamic Link Libraries (Windows DLL, Linux .so, AmigaOS libraries) — export/import tables of function pointers looked up by name or offset.
- FUSE filesystems in userspace (libfuse) — you supply function pointers for open/read/write/etc.

## 7. Device drivers / OS abstraction layers
The OS doesn't know how to open/close/read/write a specific device — the driver supplies function pointers (open, close, read, write, ISR handler) that conform to a standard interface. The OS/file system calls through these pointers, so any storage device (SD card, USB, HDD) can be used interchangeably as long as it implements the same interface.

## 8. Plugins and extensions
Functions loaded at runtime (e.g. via `GetProcAddress`, `dlsym`) are accessed through function pointers. Essential for APIs like OpenGL, where extension functions are resolved dynamically.

## 9. Feature enable/disable
Instead of cluttering code with `if-else` checks for feature variants, assign a function pointer to the desired variant. Adding/removing a feature means updating the pointer assignment rather than hunting down every conditional branch.

## 10. Backwards compatibility in libraries
When a function is renamed but keeps the same signature, a function pointer with the old name can point to the new function, preserving the old API without duplicating code.

## 11. Switch-like dispatch on non-switchable types (e.g. strings)
Since C's `switch` only works on integral types, an array mapping sorted string keys to function pointers (searched via binary search) can approximate switch-like dispatch on strings — faster than a long chain of `strcmp()` checks in `if-else`.

## 12. Basic OOP / polymorphism in C
Attaching function pointers to a struct lets that struct behave like an object with virtual methods — a common technique for "C with classes" style code, and the mechanism used in many state machine and driver implementations above.

## 13. Recursive tree traversal with a supplied operation
As in your BST example — pass a `void (*func)(int)` into a traversal function so the same traversal logic can perform any operation (print, sum, count, etc.) on each node without modifying the traversal code itself.
