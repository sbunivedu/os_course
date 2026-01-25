Below is a **combined summary of Chapter 4 (*Processes*) and Chapter 5 (*Process API*)** from *Operating Systems: Three Easy Pieces*, written in the same **clear, student-friendly style** you approved for the previous chapter. Diagrams and a glossary are included, plus **review questions** at the end.

---

# *Processes* & *Process API* Summary

### Based on *OSTEP Chapters 4 & 5*

---

## Big Ideas Covered

### **1) What Is a Process?**

A **process** is a *running program* — not just the code on disk, but something with:

* its own **address space**
* CPU **registers**
* **open files** and I/O state
* a *unique identity* in the system

Processes let the operating system **manage multiple programs** safely and efficiently.

---

## Chapter 4 — Processes: Key Concepts

### The Illusion of Concurrency

Even on a single CPU, the OS can make programs **appear to run simultaneously** by:

* interleaving execution (time sharing)
* switching rapidly between processes (context switching)

**Time sharing** increases utilization and responsiveness, but can reduce individual performance.

---

### What Defines a Process?

A process includes:

* **Address space** (code + data + stack)
* **CPU registers** (program counter, stack pointer, general registers)
* **Open files and I/O state**
* **Process state** (running, ready, blocked)

---

### Process States

A process moves between:

```
       +--------+
       | Running|   (CPU)
       +--------+
           ^
           | context switch
           |
   +-------|--------+
   | Ready |        |
   +------+         |
      | blocked     |
      v             v
  +--------+    +--------+
  |Blocked |    |Blocked |
  +--------+    +--------+
(waiting for      (waiting for
 I/O or event)     something else)
```

The basic transitions are:

* **Ready → Running** (scheduler picks a process)
* **Running → Blocked** (waiting for I/O)
* **Running → Ready** (preemption)
* **Blocked → Ready** (I/O completes)

---

### Process Control Block (PCB)

The OS keeps per-process information in the **Process Control Block**:

* register state
* memory mappings
* open file descriptors
* scheduling information
* process ID (PID)

This is how the OS **remembers where to resume** a process later.

---

### How the OS Views Processes

Tools like `top` or `ps` display the OS’s view of current processes and their resource usage.

---

## Chapter 5 — Process API: How Processes Are Managed

The **Process API** lets programs create and control processes.

---

## Creating Processes: `fork()`

The key system call for creating a new process is:

```
pid = fork();
```

**What `fork()` does:**

* creates a *new process* (child)
* child is a nearly identical copy of parent
* both continue execution after `fork()`

Return values:

* `0` in the **child**
* child’s PID in the **parent**
* negative on failure

This lets parent and child take different actions after creation.

---

## Running New Programs: `exec()`

To replace a process’s address space with a new program:

```
exec("/path/to/program", args);
```

`exec()` does *not* create a new process — it **replaces the current one** with another program image.

Together with `fork()`, you get the classic model:

```
fork();
exec(...);
```

Commonly used in shells to launch programs.

---

## Waiting for Children: `wait()`

After `fork()`, the parent can wait for the child to finish:

```
wait(&status);
```

This:

* blocks the parent until the child terminates
* allows the parent to retrieve the exit status
* avoids “zombie processes”

---

## Exit and Termination

Processes terminate by calling:

```
exit(status);
```

This releases most resources, but the **parent must call `wait()`** to fully reap the child.

If the parent never calls `wait()`, the child becomes a **zombie** — terminated but still recorded in the process table.

---

## Signals

Processes can send asynchronous notifications to each other using **signals** (e.g., `kill(pid, SIGTERM)`).

Signals can:

* request termination
* interrupt blocking calls
* deliver user-defined notifications

---

## Combining the Pieces

Processes start via `fork()`, may use `exec()` to run new programs, and can wait for children via `wait()` while `exit()` ends execution. Signals provide asynchronous control.

This API gives programmers precise control over process creation, execution, and termination.

---

# Diagrams

---

## Process Lifecycle

```
+--------+
|Running |<------------------+
+--------+                   |
     | preempt or block      |
     v                       |
+--------+                   |
| Ready  |                   |
+--------+                   |
     ^                       |
     | I/O done              |
     +-----------------------+
```

---

## Parent-Child Interaction

```
Parent calls fork()
     |
     +-----------------------------+
     |                             |
Child (fork returns 0)     Parent (fork returns child PID)
     |                             |
exec() often used here     maybe wait() for child
     |
child runs new program
```

---

## Fork & Exec in Shells

```
shell process
     |
    fork()
     |
 child
     |
   exec("/bin/ls")
     |
 ls runs in child
```

---

# Glossary of Key Terms

**Process**
A running instance of a program with its own resources.

**Process ID (PID)**
A unique identifier assigned to each process.

**PCB (Process Control Block)**
OS data structure containing process state and metadata.

**fork()**
System call that creates a new process, copying the caller.

**exec()**
System call that replaces a process’s image with a new program.

**wait()**
System call that waits for a child process to finish.

**exit()**
System call that terminates a process.

**Zombie Process**
A terminated child process that has not yet been reaped by its parent.

**Signal**
Asynchronous notification sent to a process.

**Parent Process**
The process that called `fork()` to create a new process.

**Child Process**
The newly created process from `fork()`.

---

# Review Questions

### Conceptual

1. Why does `fork()` return twice? What are the implications of its return values?
2. How is a child process’s address space similar to and different from the parent’s right after `fork()`?
3. Why do we typically see `fork()` followed by `exec()` in shells?

---

### Mechanism vs. Observation

4. What role does the Process Control Block play in context switching?
5. Why must the parent call `wait()` to avoid zombie processes?

### API Usage

6. What is the difference between `exit()` and returning from `main()`?
7. How do signals fit into process control? Give an example.

### Diagram-Based

8. Draw the process state transitions for a process that blocks on I/O and later resumes.
9. Show the path from shell → fork → exec → program execution.

### Synthesis

10. Explain how the OS provides the illusion of parallel execution on a single CPU using processes.

