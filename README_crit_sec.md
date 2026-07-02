how to safegurard criitalsection

1. Disabling Interrupts (Bare-metal / Low-level)The most common method for simple or single-core MCUs is disabling global interrupts before accessing the shared resource and re-enabling them immediately after.For example, on ARM Cortex-M microcontrollers:cuint32_t primask_state;

// 1. Save current interrupt state
primask_state = __get_PRIMASK();

// 2. Disable global interrupts
__disable_irq(); 

// --- CRITICAL SECTION START ---
shared_resource++; 
// --- CRITICAL SECTION END ---

// 3. Restore previous interrupt state
__set_PRIMASK(primask_state); 
Use code with caution.2. Using Interrupt Masking (BASEPRI)Disabling all global interrupts blocks everything, which can delay critical real-time tasks. On ARM Cortex-M chips, you can mask only lower-priority interrupts using the BASEPRI (Base Priority Mask) register, leaving high-priority ISRs fully operational.cuint32_t basepri_state = __get_BASEPRI();

// Mask interrupts of lower priority (e.g., priorities 6-15)
__set_BASEPRI(6 << (8 - __NVIC_PRIO_BITS)); 

// --- CRITICAL SECTION ---

// Restore original BASEPRI
__set_BASEPRI(basepri_state);
Use code with caution.3. RTOS Synchronization PrimitivesIf you are running a Real-Time Operating System (like FreeRTOS or Zephyr), using global interrupt disables across task switches is heavily discouraged. Instead, use OS-provided tools:Mutexes: Best for protecting long sections where tasks might need to sleep or wait.Semaphores: Best for signaling between tasks or managing multiple resource instances.Task-specific Enter/Exit Macros: Use OS primitives like taskENTER_CRITICAL() and taskEXIT_CRITICAL() to safely handle scheduler states.4. Atomic OperationsIf your critical section involves a simple mathematical operation or flag toggle, you can use built-in compiler atomic operations (e.g., GCC's __sync_fetch_and_add) or MCU-specific atomic bit-banding features. This eliminates the need for large lock blocks by forcing the hardware to do the operation in one indivisible cycle.Best PracticesKeep it short: Only wrap the exact lines accessing the shared resource. Long sections can cause your system to miss hardware events.Never use return or break inside a critical block: Doing so will leave interrupts permanently disabled or locks held, which will freeze the MCU.