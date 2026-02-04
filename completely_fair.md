## 📌 Summary: *CFS: Completely Fair process scheduling in Linux*

The article describes how Linux uses the **Completely Fair Scheduler (CFS)** as its default process scheduler for normal (non-real-time) tasks. CFS was introduced in the Linux 2.6.23 kernel in 2007 and represents a modern approach to allocating CPU time fairly among competing processes. ([Opensource.com][1])

### 🧠 What CFS Aims to Do

Rather than using fixed timeslices or strict priority queues like traditional preemptive schedulers, CFS strives to give **each runnable task a fair share of the processor**. The scheduler approximates an “ideal processor” where all tasks could execute simultaneously and divides CPU time so that each task’s share is proportional to its weight (e.g., nice value) and inversely proportional to the number of tasks running at a given moment. ([Opensource.com][1])

### ⚙️ How CFS Works

* CFS maintains a **virtual runtime (vruntime)** for each task, which tracks how much CPU time the task has consumed relative to others.
* Smaller `vruntime` means the task has received less CPU time and should be scheduled sooner.
* CFS uses a **red-black tree** (a self-balancing binary search tree) called the runqueue. Tasks are ordered by their `vruntime`, so the scheduler can quickly find the task that has received the least CPU time. ([Opensource.com][1])

#### Fair Time Division

CFS defines a **target latency**, roughly the period over which all runnable tasks should ideally get a chance to execute. If there are *N* tasks, each gets approximately `1/N` of that latency before being preempted. This value adapts dynamically as tasks block or wake up, ensuring fairness. ([Opensource.com][1])

#### No Fixed Timeslices

Unlike classic schedulers that give fixed time quanta (e.g., 50 ms), CFS computes time slices dynamically based on the number of tasks and their priorities; there is **no static timeslice for every task**. ([Opensource.com][1])

### 📈 Efficiency and Design

* CFS avoids rigid priority queues and fixed timeslices, reducing artificial bias.
* The **red-black tree** allows scheduling decisions and updates (insertion/removal) to occur in **O(log n)** time, where *n* is the number of runnable tasks. ([Opensource.com][1])
* CFS is designed to be efficient while maintaining fairness and responsiveness, whether on desktops, servers, or multiprocessor systems. ([Opensource.com][1])

### 💡 Why CFS Matters

CFS illustrates how a relatively simple idea—**give every task a fair share of CPU resources**—can be implemented efficiently in a general-purpose OS without relying on traditional scheduler constructs like fixed timeslices or rigid priorities. The article emphasizes that while research continues into even better scheduling algorithms, CFS remains the dominant and practical scheduler for general CPU workloads in Linux. ([Opensource.com][1])

---

## 📚 Core takeaways

* Linux replaced its older scheduler with CFS in kernel 2.6.23. ([Opensource.com][1])
* CFS avoids fixed timeslices and explicit priority queues. ([Opensource.com][1])
* It uses **virtual runtime** and a **red-black tree** to schedule tasks fairly. ([Opensource.com][1])
* Scheduling operations are efficient (O(log n)). ([Opensource.com][1])

[1]: https://opensource.com/article/19/2/fair-scheduling-linux "CFS: Completely fair process scheduling in Linux | Opensource.com"
