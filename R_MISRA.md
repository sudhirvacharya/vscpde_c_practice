# MISRA C Violation Examples — Q&A

**Q: What are common MISRA C violations, with non-compliant and compliant code examples?**

**A:**

**1. Integer Overflow / Implicit Type Conversion (Rule 10.1 / 10.3 / 10.4)**
```c
// Non-Compliant
int a, b, c;
a = b + c;   // overflow risk if b+c exceeds int range

float fl = 10.0f;
uint32_t sum;
sum = (uint32_t)((fl + 100.0f) / 50.0f);   // implicit conversions hidden

// Compliant
sum = (uint32_t)((float)(fl + 100.0f) / 50.0f);   // explicit cast at every step
```
Implicit conversions between essentially different types (float/int, signed/unsigned) must be explicit, and results must fit the target type's range.

---

**2. Side Effects / Undefined Order of Evaluation (Rule 13.2)**
```c
// Non-Compliant
val = n++ + arr[n];   // undefined behavior: n read and modified, no sequence point

// Compliant
val = n + arr[n];
n = n + 1;
```
The value of an expression and its side effects shall be the same under all permitted evaluation orders.

---

**3. No Recursion (Rule 17.2)**
```c
// Non-Compliant
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);   // calls itself
}

// Compliant
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result = result * i;
    }
    return result;
}
```
Functions shall not call themselves, directly or indirectly — recursion has unbounded/hard-to-verify stack usage, unacceptable in safety-critical embedded systems.

---

**4. No Dynamic Memory Allocation (Rule 21.3)**
```c
// Non-Compliant
int *ptr = malloc(sizeof(int) * 10);
int *ptr2 = calloc(10, sizeof(int));
free(ptr);

// Compliant
static int buffer[10];
int *ptr = buffer;
```
malloc/calloc/realloc/free are disallowed — dynamic allocation risks heap fragmentation, non-deterministic timing, and runtime allocation failure. Use static or pool allocation instead.

---

**5. No Unions (Rule 19.2)**
```c
// Non-Compliant
union Data {
    int i;
    float f;
    char c[4];
};

// Compliant
struct Data {
    int i;
    float f;
};
```
Unions allow type-punning that bypasses the type system and can produce undefined/implementation-defined behavior.

---

**6. Every `if` Must Have a Matching `else` (Rule 15.7)**
```c
// Non-Compliant
if (x == 1) {
    doSomething();
}
// no else -- unstated behavior when x != 1

// Compliant
if (x == 1) {
    doSomething();
} else {
    /* explicitly handle the alternative, even if a no-op with a comment */
}
```
All if...else if constructs shall be terminated with an else statement, ensuring every branch condition is explicitly considered.

---

**7. No Unreachable Code After `break` (Rule 2.1)**
```c
// Non-Compliant
switch (state) {
    case 0:
        doWork();
        break;
        i++;         // unreachable
    case 1:
        doOtherWork();
        break;
}

// Compliant
switch (state) {
    case 0:
        doWork();
        break;
    case 1:
        doOtherWork();
        break;
}
```
A project shall not contain unreachable code. Code after break/return/goto (before the next label) can never execute and typically indicates a logic error.
