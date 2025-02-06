Write a C program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Try to "print" some text to this open file from both the parent and the child processes.

Please explain what happens using the actual output from the commandline and answer the following questions:
* Can both the child and parent access the file descriptor returned by `open()`?
* What happens when they are writing to the file concurrently, i.e., at the same time?

