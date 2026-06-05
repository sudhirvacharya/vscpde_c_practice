
//tcb: task coontrol block
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* --- Task states (like uC/OS-III) --- */
typedef enum {
    TASK_READY   = 0,
    TASK_RUNNING,
    TASK_BLOCKED,
    TASK_SUSPENDED,
    TASK_DELETED,
} TaskState;

/* --- TCB structure (simplified uC/OS-III style) --- */
typedef struct TCB {
    uint32_t    *stack_ptr;          /* saved stack pointer (top of stack)  */
    char         name[32];           /* task name                           */
    uint8_t      priority;           /* 0 = highest in most RTOS            */
    TaskState    state;              /* current task state                  */
    uint32_t     stack_size;         /* stack size in bytes                 */
    uint32_t     cpu_usage;          /* CPU usage % (runtime metric)        */
    uint32_t     ctx_switch_count;   /* number of context switches          */
    struct TCB  *next;               /* pointer to next TCB in ready queue  */
} TCB;

/* --- Dummy stack space --- */
static uint32_t stack_a[256], stack_b[256];

/* --- Helper: print a TCB --- */
void tcb_print(const TCB *t)
{
    static const char *state_names[] = {
        "READY", "RUNNING", "BLOCKED", "SUSPENDED", "DELETED"
    };
    printf("------------------------------\n");
    printf("Task Name        : %s\n",   t->name);
    printf("Priority         : %u\n",   t->priority);
    printf("State            : %s\n",   state_names[t->state]);
    printf("Stack Size       : %u B\n", t->stack_size);
    printf("CPU Usage        : %u%%\n", t->cpu_usage);
    printf("Context Switches : %u\n",   t->ctx_switch_count);
    printf("Stack Ptr (top)  : %p\n",   (void *)t->stack_ptr);
    printf("Next TCB         : %p\n",   (void *)t->next);
}

int main(void)
{
    /* --- Create two TCBs --- */
    TCB tcb_a, tcb_b;
    memset(&tcb_a, 0, sizeof(TCB));
    memset(&tcb_b, 0, sizeof(TCB));

    /* --- Initialise TCB A --- */
    strncpy(tcb_a.name, "SensorTask", sizeof(tcb_a.name));
    tcb_a.priority         = 2;
    tcb_a.state            = TASK_RUNNING;
    tcb_a.stack_size       = sizeof(stack_a);
    tcb_a.stack_ptr        = &stack_a[255];  /* top of stack */
    tcb_a.cpu_usage        = 35;
    tcb_a.ctx_switch_count = 120;
    tcb_a.next             = &tcb_b;

    /* --- Initialise TCB B --- */
    strncpy(tcb_b.name, "CommTask", sizeof(tcb_b.name));
    tcb_b.priority         = 5;
    tcb_b.state            = TASK_READY;
    tcb_b.stack_size       = sizeof(stack_b);
    tcb_b.stack_ptr        = &stack_b[255];
    tcb_b.cpu_usage        = 10;
    tcb_b.ctx_switch_count = 44;
    tcb_b.next             = NULL;

    /* --- Walk the TCB linked list (like a real kernel would) --- */
    TCB *cur = &tcb_a;
    while (cur) {
        tcb_print(cur);
        cur = cur->next;
    }

    return 0;
}