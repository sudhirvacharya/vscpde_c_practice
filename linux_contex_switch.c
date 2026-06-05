#include <stdio.h>
#include <ucontext.h>

#define STACK_SIZE 65536

static ucontext_t ctx_main, ctx_t1, ctx_t2;
static char stack1[STACK_SIZE], stack2[STACK_SIZE];

void task1(void)
{
    printf("Task1: started\n");
    printf("Task1: switching to Task2\n");
    swapcontext(&ctx_t1, &ctx_t2);      /* save Task1 state, run Task2 */

    printf("Task1: resumed after context switch\n");
    swapcontext(&ctx_t1, &ctx_main);    /* return to main */
}

void task2(void)
{
    printf("Task2: started\n");
    printf("Task2: switching back to Task1\n");
    swapcontext(&ctx_t2, &ctx_t1);      /* save Task2 state, resume Task1 */
}

int main(void)
{
    /* --- set up Task1 context --- */
    getcontext(&ctx_t1);
    ctx_t1.uc_stack.ss_sp   = stack1;
    ctx_t1.uc_stack.ss_size = STACK_SIZE;
    ctx_t1.uc_link          = &ctx_main;   /* return here when task1 exits */
    makecontext(&ctx_t1, task1, 0);

    /* --- set up Task2 context --- */
    getcontext(&ctx_t2);
    ctx_t2.uc_stack.ss_sp   = stack2;
    ctx_t2.uc_stack.ss_size = STACK_SIZE;
    ctx_t2.uc_link          = &ctx_main;
    makecontext(&ctx_t2, task2, 0);

    printf("Main: starting Task1\n");
    swapcontext(&ctx_main, &ctx_t1);    /* save main state, run Task1 */

    printf("Main: all tasks done\n");
    return 0;
}