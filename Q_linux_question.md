# Linux Kernel and Driver Interview Questions

*Prepared by EmbeddedShiksha (www.embeddedshiksha.com)*

## Process Management
1. How to manipulate the current process states?
2. What are kernel threads?
3. How are threads implemented in the Linux kernel?
4. What are the different states of a process in Linux?
5. What is the difference between a process and a thread?
6. What resources are generally shared between threads?
7. What is a process descriptor?
8. What is task_struct?
9. What is thread_info structure for?
10. What was the need for the thread_info structure?
11. Difference between fork() and vfork()?
12. What is process context?
13. What is a zombie process?
14. How is a parentless process handled in Linux?

## Process Scheduling
1. What is process scheduling?
2. What is cooperative multitasking and pre-emptive multitasking?
3. What is yielding?
4. What is the limitation of cooperative multitasking?
5. I/O bound versus processor bound process?
6. What is process priority?
7. What kind of priority is maintained in Linux?
8. What is nice value?
9. What is virtual run time?
10. What are the available scheduling classes in Linux?
11. Which type of scheduling is used in Linux?
12. How is the next task picked for scheduling?
13. What is the scheduler entry point in Linux?
14. What is a waitqueue?
15. How is context switching handled in Linux?
16. What is user preemption and kernel preemption?

## Syscalls
1. What are syscalls?
2. How are system calls implemented in Linux?
3. What happens when a process in userspace calls a syscall?
4. What is the need for verifying parameters in the definition of a syscall?
5. What is system call context?
6. Why is it not recommended to write new syscalls?

## Interrupt Handling
1. What is an interrupt?
2. What is an interrupt handler or ISR?
3. What are top halves and bottom halves?
4. How is an interrupt registered?
5. What are the different interrupt handler flags?
6. How are interrupts freed?
7. What considerations should be taken care of while writing an interrupt handler?
8. What is interrupt context?
9. How to disable and enable interrupts?
10. What are the different bottom half techniques in Linux?
11. What are tasklets, softirqs, and workqueues, and the difference among them?
12. When to choose which bottom half?
13. How to implement softirqs, tasklets, and workqueues?
14. How to schedule a tasklet?
15. What is ksoftirqd?
16. How to disable bottom halves?
17. How is locking between bottom halves handled?

## Kernel Synchronization
1. What is synchronization?
2. What is a critical section?
3. What is a race condition?
4. Why do we need to take care of synchronization?
5. What are the various synchronization techniques in Linux?
6. What is a deadlock?
7. What is an atomic operation?
8. What is a spinlock?
9. What is a reader-writer spin lock?
10. What is a semaphore?
11. What is a binary semaphore?
12. What is the difference between semaphore and spinlock?
13. When to choose between spinlock and semaphore?
14. What is the difference between semaphore and mutex?
15. What is preemption disabling and what is its use?

## Memory Management
1. How is memory managed in Linux?
2. What are pages?
3. What are the different memory zones in Linux?
4. How to allocate pages?
5. How to free pages?
6. What is kmalloc, and what are its action modifiers?
7. What is a zone modifier in Linux?
8. What is vmalloc?

## Virtual File System
1. What is the virtual file system, and what is the need for it in Linux?
2. What are the different object types in VFS?
3. What operations are possible on inode and superblock objects?

## Process Address Space
1. What is process address space?
2. What is the memory descriptor in Linux, and which structure represents it?
3. How to allocate and destroy a memory descriptor?
4. Does a kernel thread have any association with mm_struct?
5. What is a VMA, and what VMA operations are possible in the Linux kernel?
6. How to manipulate a memory area in Linux?
7. What is mmap and do_mmap()?
8. What is a page table?

## Device Driver Questions
1. What is a device driver, and what is the need for it?
2. What are the different kinds of devices?
3. What is a module in Linux?
4. How are modules loaded in Linux?
5. Difference between insmod and modprobe?
6. How are parameters shared between driver modules?
7. What are IOCTLs?
8. What are syscalls?
9. What are the benefits of syscalls?
10. How is a character driver registered in Linux?
11. What are the init and exit functions of a driver?
12. How and when are the init and exit functions of a driver called?
13. What is a probe function?
14. When is probe called?
15. What is a platform device?
16. What is a device tree?
17. What are the benefits of a device tree over board files?
18. What are sysfs and procfs?
19. How are logs printed in the Linux kernel, and what are the log levels?
20. What are copy_to_user and copy_from_user?
21. What do you mean by kernel configuration, and what are the ways of configuring the kernel?
22. What is menuconfig?
23. What is ioremap?
24. What is a segmentation fault?
25. What are the various ways of debugging the Linux kernel?
26. How does the Linux kernel boot?
27. What are zImage and bzImage?
28. What are the different boot arguments in Linux?
29. How are parameters passed from the bootloader to the kernel?
30. What is ATAGs?
31. From which file does kernel execution start?
32. What is a bootloader?
33. What are primary and secondary bootloaders?
34. Why do we need two bootloaders?
35. Difference between poll and select?
36. What is priority inheritance and priority inversion?
37. What are the different types of kernel?
38. What is DMA?
39. What is cache coherency?
40. What is copy-on-write?
41. What are highmem and lowmem?
42. What happens if we pass an invalid address from userspace using ioctl?
43. What are the different IPC mechanisms in Linux?
44. What are sockets?
45. How is a page fault handled in Linux?
46. Difference between memory-mapped IO and port-mapped IO?
47. What are I2C and SPI?
48. How does physical-to-virtual translation work in Linux?
49. What are thrashing, segmentation, and fragmentation?
50. What is preempt_count, and what is its need?
