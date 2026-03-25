//"Same function call, different behavior — decided at RUNTIME"
//Achieved by Virtual Functions + Inheritance
//g++ runtime_poly.cpp -o a   ----------> run with this cmd

// this is also called funtion over riding

#include <stdio.h>

class Animal {
public:
    virtual void sound() {        // virtual keyword is key!
        printf("Some sound\n");
    }
};

class Dog : public Animal {
public:
    void sound() {
        printf("Dog: Woof!\n");
    }
};

class Cat : public Animal {
public:
    void sound() {
        printf("Cat: Meow!\n");
    }
};

int main() {
    Animal *ptr;          // base class pointer

    Dog d;
    Cat c;

    ptr = &d;
    ptr->sound();         // calls Dog's sound at RUNTIME

    ptr = &c;
    ptr->sound();         // calls Cat's sound at RUNTIME

    return 0;
}

/*

```

## Output:
```
Dog: Woof!
Cat: Meow!
```

---

## Why RUNTIME?

Because `ptr` is a **base class pointer** — compiler does NOT know at compile time which object it will point to. It decides **while program is running** via **vtable**.

---

## How vtable works:
```
Animal *ptr = &d;
ptr->sound()
      |
      ↓
  vtable of Dog
      |
      ↓
  Dog::sound()  ← resolved at runtime!

*/