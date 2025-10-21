# Process API

The Process API describes how the kernel interfaces with user programs for process creation, control, and lifecycle. Please read relevant chapters and answer the following questions:

1. Explain how `fork()` works from a high level: what information of the parent process is replicated in the child, and what distinctions remain (e.g., return value, PID).

2. Describe how `exec()` changes the process's address space, program counter, stack, and other runtime state. What remains the same (e.g., PID, some file descriptors) and why?