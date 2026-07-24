call --> push bas ptr, copy stack point 
interupt->push base ptr, copy stack pointer, return pc
contex swithc->copy all r0-13 regter

## interrupt

well nested interrupt means while you are servicing a low priority interrupt another high priority fires so now you stop what you are doing and service the higher priority one .

## Contex switching


context switching is simply pushing the current frame(r4- r11 and link register so u can return) onto stack then switch to different frame (some interrupt or function call )


## call
well call is simple branching the pc to different section of code (some function or you can even call interrupt as function ) during branching it subtracts stack pointer to reserve space for pushing registers and lr (context switching ).