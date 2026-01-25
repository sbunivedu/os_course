# Chapter 6: Limited Direct Execution

### *Operating Systems: Three Easy Pieces*

## Big Question of the Chapter

How can the operating system **run programs efficiently** while still **maintaining control** of the CPU?

The answer: **Limited Direct Execution (LDE)**.

## The Core Tension

The OS wants two things:

* **Performance** → programs should run directly on the CPU
* **Control** → programs must not be allowed to:

  * run forever
  * perform I/O directly
  * interfere with other programs or the OS

These goals conflict unless the OS uses **hardware support**.

## From Direct Execution to Limited Direct Execution

### Naïve Direct Execution (Unsafe)

```
OS loads program
OS jumps to program
Program runs forever
(OS never regains control)
```

Problems:

* No protection
* No preemption
* No safe I/O

## Limited Direct Execution (The Solution)

**Key idea:**

> Let programs run directly on the CPU, but *limit* what they can do.

This is achieved using:

1. **Restricted execution**
2. **Controlled entry into the OS**
3. **Timer interrupts**

## User Mode vs Kernel Mode

Modern CPUs provide **two execution modes**:

```
+----------------------+
|      Kernel Mode     |  ← OS runs here
|  (privileged access) |
+----------------------+
          ↑
          | trap / interrupt
          ↓
+----------------------+
|       User Mode      |  ← applications run here
| (restricted access)  |
+----------------------+
```

Rules:

* Applications run in **user mode**
* OS runs in **kernel mode**
* Privileged instructions are **disallowed** in user mode

## Controlled Entry: System Calls

When a user program needs OS services (e.g., I/O):

```
User Program
    |
    | system call
    v
-----------------------
 Trap (hardware)
 Switch to kernel mode
 Jump to OS handler
-----------------------
    |
    | return-from-trap
    v
User Program resumes
```

Key points:

* User programs cannot jump into the OS arbitrarily
* Entry points are predefined and protected

## The Trap Table

The OS initializes a **trap table** at boot time:

```
Trap Number  →  OS Handler Address
--------------------------------
0            →  system call handler
1            →  timer interrupt
2            →  disk interrupt
...
```

Purpose:

* Ensures **safe and controlled transitions**
* Prevents user programs from executing arbitrary kernel code

## Regaining Control: Timer Interrupts

What if a program never makes a system call?

Solution:

* **Timer interrupts**

```
User Program running
        |
        | (timer expires)
        v
-----------------------
 Interrupt
 Switch to kernel mode
 OS regains control
-----------------------
```

This allows the OS to:

* Stop a running process
* Switch to another process
* Enforce **time sharing**

## Context Switching

To switch processes, the OS performs a **context switch**:

```
Save registers of Process A
Load registers of Process B
Switch address space
Return to user mode
```

Effect:

* Each process believes it has its own CPU
* Enables **CPU virtualization**

## Why Limited Direct Execution Works

Limited Direct Execution succeeds because:

* Programs run at **near-native speed**
* The OS always regains control
* Hardware enforces protection
* Timer interrupts enable preemption
* System calls provide safe OS services

This chapter focuses on **mechanisms**, not **policies**
(e.g., *how* to switch vs *which* process to run next).

# Glossary of Key Terms

**Limited Direct Execution (LDE)**
A CPU virtualization technique where programs run directly on the hardware but with enforced restrictions.

**User Mode**
Restricted CPU mode for applications.

**Kernel Mode**
Privileged CPU mode for the operating system.

**Privileged Instruction**
An instruction that can only execute in kernel mode.

**System Call**
A controlled entry point into the OS from a user program.

**Trap**
A hardware mechanism that transfers control to the OS.

**Trap Table**
A table defining valid OS entry points for traps and interrupts.

**Interrupt**
An asynchronous event that transfers control to the OS.

**Timer Interrupt**
A periodic interrupt that allows the OS to regain CPU control.

**Context Switch**
Saving one process’s state and restoring another’s.

**CPU Virtualization**
The illusion that each process has its own CPU.

# Review Questions

### Conceptual Questions

1. Why is pure direct execution unsafe in a multiprogrammed system?
2. How does user mode differ from kernel mode?
3. Why are privileged instructions necessary?
4. How do system calls differ from interrupts?
5. Why must the OS regain control even if a program never makes a system call?

### Diagram-Based / Flow Questions

6. Trace the full control flow of a system call from user program to OS and back.
7. Trace what happens when a timer interrupt occurs.
8. Identify where hardware support is required in limited direct execution.

### Mechanism vs Policy

9. Which parts of limited direct execution are mechanisms?
10. Which decisions are left to scheduling policy (later chapters)?

### Short Answers

11. Explain how limited direct execution balances performance and control.
12. What role does the trap table play in system security?
13. Why are timer interrupts essential for time sharing?
14. What information must be saved during a context switch?
15. Why is limited direct execution considered a “compromise”?
