# Process API

The purpose of this assignment is to practice using the Linux process API and to look up information using "Linux man pages".

Please read or reread [chapter 5 on process API](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf). You can compile and run the code examples as follows:
```
gcc -o p1 p1.c
./p1
```

## Step 1
Experiment with `p2.c` and use the built-in Linux man page (e.g. on cisone) or online at https://man7.org/linux/man-pages/index.html to look up the `fork` system call.

Question 1: What is the return value of `wait` system call? What is a "zombie" process?

## Step 2
Experiment with `p3.c` and look up the `exec` system call.

Question 2: The `exec()` system call is called once but never returns. How come?

## Step 3
Experiment with `p4.c` and look up `open` system call.

Question 3: What is the type and the meaning of the return value from `open`? What does `O_TRUNC` mean as a "file creation flag"?

## Step 4
Look up `fork` system call in the man pages again.

Question 4: What happens to a process's open file descriptors when the process is forked?

## Step 5
Experiment with `sharefile.c` and look up `write` system call.

Question 5: What does `write` return? What happens if it fails?