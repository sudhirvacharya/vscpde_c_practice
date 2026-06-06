# STM32 Startup File — Weak & Strong Symbol (SysTick_Handler)

---

## 1. Assembly Directives in Startup File

```asm
.weak   SysTick_Handler
.thumb_set SysTick_Handler, Default_Handler
```

| Directive | Meaning |
|---|---|
| `.weak` | Symbol can be overridden by a strong definition elsewhere |
| `.thumb_set A, B` | Makes A an alias — A and B share the same Flash address |

---

## 2. Equivalent C Code

```c
// Catches any unhandled interrupt — spins forever
void Default_Handler(void) {
    while (1);
}

// Weak alias — linker uses Default_Handler unless you define your own
__attribute__((weak))
void SysTick_Handler(void) __attribute__((alias("Default_Handler")));
```

To override it in your application:

```c
// Your definition — strong symbol, overrides the weak alias
void SysTick_Handler(void) {
    HAL_IncTick();   // your 1 ms tick logic
}
```

---

## 3. Why Not Use `#define` Instead?

```c
// WRONG approach
#define SysTick_Handler Default_Handler
```

This fails because:

- `#define` is **preprocessor text substitution** — runs before compilation
- If you later write `void SysTick_Handler(void) { ... }`, the preprocessor replaces the name → becomes a second `Default_Handler` → **linker error: multiple definition**
- The vector table needs a real symbol named `SysTick_Handler` — `#define` destroys that name entirely
- `#define` scope is per-file; `.weak` is resolved globally by the linker across all object files

| | `#define` | `.weak` + `.thumb_set` |
|---|---|---|
| Works at | Preprocessor (text) | Linker (symbol table) |
| Overridable from another `.c`? | No | Yes |
| Creates real symbol in object file? | No | Yes |
| Vector table can reference it? | No | Yes |

---

## 4. Interrupt Flow

### Strong Symbol (you defined SysTick_Handler)

```
SysTick interrupt fires
        ||
NVIC reads vector table slot [15]
        ||
address = 0x0800 0A24  ← your function's Flash address
        ||
Jumps to your SysTick_Handler()
        ||
HAL_IncTick() / your tick logic runs
```

### Weak Symbol (you did NOT define SysTick_Handler)

```
SysTick interrupt fires
        ||
NVIC reads vector table slot [15]
        ||
address = 0x0800 0198  ← Default_Handler's Flash address
        ||
Jumps to Default_Handler()
        ||
while(1)  — infinite loop (fault visible)
```

> **Key point:** NVIC always fetches slot [15] — it has no knowledge of strong/weak.
> The linker decided which address goes in that slot at build time.

---

## 5. How the Linker Resolves the Symbol

```
startup_stm32.s          your_file.c
  .weak SysTick_Handler    void SysTick_Handler(void) { ... }
  alias → Default_Handler              ↓
              ↓                  strong symbol
              └──────────────────────┘
                        ↓
                    Linker picks strong → your function's address
                    placed in vector table slot [15]
```

If no strong definition exists, the weak alias stands and `Default_Handler`'s address is placed in the slot.

---

## 6. Every IRQ Handler Follows the Same Pattern

All handlers in the startup file use the same weak alias pattern:

```asm
.weak  USART1_IRQHandler
.thumb_set USART1_IRQHandler, Default_Handler

.weak  TIM2_IRQHandler
.thumb_set TIM2_IRQHandler, Default_Handler
```

This means any unhandled peripheral interrupt also safely falls into `Default_Handler`'s infinite loop instead of jumping to a random address.
