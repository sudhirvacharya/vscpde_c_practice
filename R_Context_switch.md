call --> push bas ptr, copy stack point 
interupt->push base ptr, copy stack pointer, return pc
contex swithc->copy all r0-13 regter

## interrupt
Something signals hardware (peripheral flag, timer, external pin) → interrupt controller marks it pending.
CPU finishes current instruction (mostly), then instead of fetching the next instruction in your program, it pushes context onto the stack (like a call would push a return address, but more of it).
CPU loads PC from the vector table (indexed by which interrupt fired) — this is the "jump to new function."
ISR executes — just a normal function from the CPU's point of view.
ISR ends with a return instruction → CPU pops the saved context back off the stack and resumes exactly where it left off — like returning from a call.

## Contex switching


context switching is simply pushing the current frame(r4- r11 and link register so u can return) onto stack then switch to different frame (some interrupt or function call )


## call
well call is simple branching the pc to different section of code (some function or you can even call interrupt as function ) during branching it subtracts stack pointer to reserve space for pushing registers and lr (context switching ).