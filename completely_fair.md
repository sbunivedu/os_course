## Summary: *CFS: Completely Fair process scheduling in Linux*

The article describes how Linux uses the **Completely Fair Scheduler (CFS)** as its **default** process scheduler for normal (non-real-time) tasks. CFS was introduced in the Linux 2.6.23 kernel in 2007 and represents a modern approach to allocating CPU time fairly among competing processes.

### What CFS Aims to Do

Rather than using fixed timeslices or strict priority queues like traditional preemptive schedulers, CFS strives to give **each runnable task a fair share of the processor**. The scheduler approximates an “ideal processor” where all tasks could execute simultaneously and divides CPU time so that each task’s share is **proportional** to its weight (e.g., nice value) and **inversely proportional** to the number of tasks running at a given moment.

### How CFS Works

* CFS maintains a **virtual runtime (vruntime)** for each task, which tracks how much CPU time the task **has consumed** relative to others.
* Smaller `vruntime` means the task has received less CPU time and should be scheduled sooner.
* CFS uses a **red-black tree** (a self-balancing binary search tree) called the **runqueue**. Tasks are ordered by their `vruntime`, so the scheduler can quickly find the task that has received the least CPU time.

#### Fair Time Division

CFS defines a **target latency**, roughly the period over which all runnable tasks should ideally get a chance to execute. If there are *N* tasks, each gets approximately `1/N` of that latency **before being preempted**. This value adapts **dynamically** as tasks block or wake up, ensuring fairness. ([Opensource.com][1])

#### No Fixed Timeslices

Unlike classic schedulers that give fixed time quanta (e.g., 50 ms), CFS computes time slices dynamically based on the number of tasks and their priorities; there is **no static timeslice for every task**. ([Opensource.com][1])

### Efficiency and Design

* CFS avoids rigid priority queues and fixed timeslices, reducing artificial bias.
* The **red-black tree** allows scheduling decisions and updates (insertion/removal) to occur in **O(log n)** time, where *n* is the number of runnable tasks.
* CFS is designed to be efficient while maintaining **fairness** and **responsiveness**, whether on desktops, servers, or multiprocessor systems. ([Opensource.com][1])

### Why CFS Matters

CFS illustrates how a relatively simple idea—**give every task a fair share of CPU resources**—can be implemented efficiently in a general-purpose OS without relying on traditional scheduler constructs like fixed timeslices or rigid priorities. The article emphasizes that while research continues into even better scheduling algorithms, CFS remains the dominant and practical scheduler for general CPU workloads in Linux. ([Opensource.com][1])

## Core takeaways

* Linux replaced its older scheduler with CFS in kernel 2.6.23. ([Opensource.com][1])
* CFS avoids fixed timeslices and explicit priority queues. ([Opensource.com][1])
* It uses **virtual runtime** and a **red-black tree** to schedule tasks fairly. ([Opensource.com][1])
* Scheduling operations are efficient (O(log n)). ([Opensource.com][1])


# Bullet Notes

## What problem CFS solves

* Traditional schedulers use **fixed time slices**
* Fixed slices introduce bias and unfairness
* Linux wanted a scheduler that **shares CPU fairly** across tasks

## Core idea of CFS

* CFS models an **ideal multitasking CPU**
* In the ideal world:
  * all runnable tasks execute **simultaneously**
  * each task gets an equal share of CPU
* Reality:
  * one (or a few) CPUs
  * scheduler **approximates** this ideal

## Key abstraction: **Virtual Runtime (vruntime)**

* `vruntime` = how much processor time a task has *effectively* received
* Increases while the task runs
* Increases **faster** for lower-priority tasks
* Smaller `vruntime` ⇒ task has received **less CPU time**

👉 Scheduler always picks the task with the **smallest vruntime**

## Data structure: **Red-Black Tree**

* All runnable tasks stored in a **balanced BST**
* Ordered by `vruntime`
* Leftmost node = task that should run next

Properties:

* Insert: O(log n)
* Delete: O(log n)
* Pick next task: O(log n)

## No fixed time slices

* CFS does **not** use static quanta like Round Robin
* Instead:
  * defines a **target latency**
  * divides latency among runnable tasks
* More tasks ⇒ smaller per-task runtime
* Fewer tasks ⇒ longer runtime per task

## Priority handling (nice values)

* Linux priorities are implemented via **weights**
* Higher priority:
  * slower vruntime growth
  * runs more often
* Lower priority:
  * faster vruntime growth
  * runs less often

## Why CFS works well
* Avoids starvation
* Scales to many tasks
* Fair by design
* Efficient enough for production systems

## Key comparisons

| Scheduler | Key idea         | Selection cost |
| --------- | ---------------- | -------------- |
| FIFO      | arrival order    | O(1)           |
| RR        | fixed time slice | O(1)           |
| SJF       | shortest job     | ≥ O(log n)     |
| **CFS**   | minimum vruntime | **O(log n)**   |

---

# Diagrammatic Explanation

## A. Ideal Processor Model (Conceptual)

```
Ideal CPU (imaginary)
--------------------
Task A   Task B   Task C
  |        |        |
  |        |        |
  |        |        |
(all run at the same time)
```

CFS tries to **approximate this illusion** on real hardware.

---

## B. vruntime Timeline

```
Time →
---------------------------------------
Task A: |====|====|====|====|
Task B: |====|====|
Task C: |====|====|====|

vruntime increases only while running
```

* Task B has smaller vruntime → scheduled sooner
* Task C has larger vruntime → scheduled later

---

## C. Red-Black Tree Runqueue (Conceptual)

![Image](https://miro.medium.com/1%2AhuX4DV2SwJ7wBkbpXX9fKQ.gif)

![Image](https://miro.medium.com/v2/da%3Atrue/resize%3Afit%3A459/1%2AhuX4DV2SwJ7wBkbpXX9fKQ.gif)

ASCII version:

```
            [vr=30]
           /        \
       [vr=10]     [vr=50]
         |
      [vr=5]
```

**Leftmost node (vr=5) runs next**

---

## D. Scheduling Loop (Simplified)

```
while (CPU available):
    pick task with smallest vruntime
    run task for computed slice
    update vruntime
    reinsert into tree
```

---

## E. Target Latency Visualization

```
**Target latency** = 20 ms
Runnable tasks = 4

Each task ≈ 5 ms
```

If tasks drop to 2:

```
Each task ≈ 10 ms
```

Time slices adjust dynamically.

---

## F. Priority Effect on vruntime

```
Same real time running
---------------------
High priority task  → vruntime +1
Low priority task   → vruntime +3
```

Lower vruntime growth ⇒ more CPU over time.

> “Why doesn’t CFS need fixed time slices?”

Expected answer:

* Because fairness is enforced by **vruntime ordering**, not by quanta.

[1]: https://opensource.com/article/19/2/fair-scheduling-linux "CFS: Completely fair process scheduling in Linux | Opensource.com"
