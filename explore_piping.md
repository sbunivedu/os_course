# Guided Exercise: Understanding Unix Pipes and Named Pipes

* Explain how Unix pipes (`|`) connect processes
* Trace how data flows between commands
* Use standard input/output redirection with pipes
* Create and use **named pipes (FIFOs)**
* Relate these concepts to implementing pipes in a shell

# Part 1: Warm-Up — Standard Input and Output

### Task 1.1 — Observe stdin/stdout

Run:

```bash
echo "Hello OS class"
```

Now try:

```bash
cat
```

Type something and press Enter.

What happens?

### Questions

* Where is `cat` getting its input from?
* How do you stop `cat`?

# Part 2: First Pipe

### Task 2.1 — Basic Pipe

```bash
echo "hello world" | tr a-z A-Z
```

Observe the output.

### Task 2.2 — Break it apart

Run separately:

```bash
echo "hello world"
tr a-z A-Z
```

Why doesn’t this work the same?

### Concept Check

A pipe:

* Takes **stdout of the left command**
* Sends it to **stdin of the right command**

### Task 2.3 — Visualizing the Pipeline

```bash
ls | wc -l
```

What is being counted?

### Reflection Questions

* What would happen if `ls` produced no output?
* Which process runs first? Or do they run concurrently?

# Part 3: Multi-Stage Pipelines

### Task 3.1 — Chain commands

```bash
cat /etc/passwd | grep root | wc -l
```

Try to explain:

* What each stage does
* What flows between them

### Task 3.2 — Reorder the pipeline

Try:

```bash
cat /etc/passwd | wc -l | grep root
```

Why does this behave differently?

### Questions

* Why does **order matter** in pipelines?
* What type of data flows between processes?

# Part 4: Under the Hood (Conceptual)

Your shell must:

* Create a pipe using `pipe()`
* Fork processes
* Redirect:

  * stdout → pipe write end
  * stdin → pipe read end
* Close unused file descriptors

### Thought Question

If you run:

```bash
ls | wc -l
```

How many processes are created?

# Part 5: Debugging with `strace`

### Task 5.1 — Trace a pipeline

```bash
strace -f ls | wc -l
```

Look for:

* `pipe()`
* `fork()`
* `dup2()`

### Questions

* Which system call creates the pipe?
* How does the OS connect the processes?

# Part 6: Named Pipes (FIFOs)

## Task 6.1 — Create a named pipe

```bash
mkfifo mypipe
```

Check it:

```bash
ls -l mypipe
```

Notice the file type (`p`).

## Task 6.2 — Use the named pipe (2 terminals)

### Terminal 1:

```bash
cat > mypipe
```

### Terminal 2:

```bash
cat < mypipe
```

Type something in Terminal 1.

### What you observe

* Data flows through the pipe
* Both processes must be running

### Questions

* What happens if only one side runs?
* Why does the program block?

## Task 6.3 — Replace `cat`

Terminal 1:

```bash
ls > mypipe
```

Terminal 2:

```bash
wc -l < mypipe
```

What result do you get?
