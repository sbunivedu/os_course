# Standard Output Redirection

Below is a **step-by-step illustration** of how **standard output redirection (`>` )** works inside the OS at the **data-structure level**, not just the shell syntax.

* the **per-process file descriptor table**
* the **system-wide open file table**
* what actually changes when redirection happens

---

## 1. The Key Data Structures

### Per-Process File Descriptor Table

Each process has its **own** table:

```
FD Table (per process)
---------------------
fd 0 → ?
fd 1 → ?
fd 2 → ?
fd 3 → ?
...
```

Each entry points to an **open file object** in the system-wide table.

---

### Global Open File Table (System-Wide)

This table is shared by all processes:

```
Open File Table (system-wide)
-----------------------------
entry A: file=/dev/tty, offset=123, refcount=1
entry B: file=/dev/tty, offset=456, refcount=1
entry C: file=output.txt, offset=0, refcount=1
```

Each entry contains:

* file inode (or vnode)
* current file offset
* access mode
* reference count

---

## 2. Normal Execution (No Redirection)

Suppose a shell runs:

```bash
ls
```

### Before `ls` runs

The shell has already set up:

```
FD Table (ls process)
---------------------
fd 0 → /dev/tty  (stdin)
fd 1 → /dev/tty  (stdout)
fd 2 → /dev/tty  (stderr)
```

Diagram:

```
fd 1 ───▶ OpenFile(/dev/tty)
```

When `ls` writes to `stdout`:

```c
write(1, buffer, size);
```

The output goes to the **terminal**.

---

## 3. Shell Command with Output Redirection

Now consider:

```bash
ls > out.txt
```

Important point:

> **The shell sets this up, not `ls`.**

---

## 4. What the Shell Does (Step by Step)

### Step 1: `fork()`

The shell creates a child process:

```
Parent (shell)
Child (future ls)
```

Initially, the child inherits the same FD table.

---

### Step 2: `open("out.txt", O_WRONLY | O_CREAT | O_TRUNC)`

The shell (in the child) opens the file:

```c
int fd = open("out.txt", ...);
```

Assume `open()` returns **fd 3**.

```
FD Table (child)
----------------
fd 0 → /dev/tty
fd 1 → /dev/tty
fd 2 → /dev/tty
fd 3 → out.txt
```

Global table now has a new entry:

```
Open File Table
---------------
entry D: file=out.txt, offset=0, refcount=1
```

---

### Step 3: `dup2(fd, STDOUT_FILENO)`

This is the **core redirection step**:

```c
dup2(3, 1);
```

Meaning:

> Make `fd 1` point to the **same open file object** as `fd 3`.

#### After `dup2`

```
FD Table (child)
----------------
fd 0 → /dev/tty
fd 1 → out.txt
fd 2 → /dev/tty
fd 3 → out.txt
```

But **both fd 1 and fd 3 point to the same open file entry**:

```
fd 1 ─┐
      ├──▶ OpenFile(out.txt, offset=0, refcount=2)
fd 3 ─┘
```

Reference count increases.

---

### Step 4: `close(fd)`

The shell closes fd 3:

```c
close(3);
```

Now:

```
FD Table (child)
----------------
fd 0 → /dev/tty
fd 1 → out.txt
fd 2 → /dev/tty
```

Global table:

```
OpenFile(out.txt, offset=0, refcount=1)
```

---

### Step 5: `exec("ls")`

The child replaces itself with `ls`.

**Important:**

* The FD table **survives `exec()`**
* The code and memory image do not

So `ls` starts with:

```
fd 1 → out.txt
```

---

## 5. What Happens When `ls` Writes Output

Inside `ls`:

```c
printf("file1\n");
```

Which becomes:

```c
write(1, "file1\n", 6);
```

The OS follows:

```
fd 1
 ↓
Open File Table entry
 ↓
inode for out.txt
 ↓
disk
```

➡️ Output goes to **`out.txt`**, not the terminal.

---

## 6. Final Picture (Key Insight)

### Before Redirection

```
fd 1 ───▶ OpenFile(/dev/tty)
```

### After Redirection

```
fd 1 ───▶ OpenFile(out.txt)
```

**Nothing in `ls` changes.**
The program blindly writes to fd 1.

---

## 7. Why This Design Is So Powerful

1. **Programs don’t need to know about redirection**
2. Redirection works for *any* program that uses standard I/O
3. The mechanism is simple:

   * manipulate file descriptor tables
   * reuse existing system calls (`open`, `dup2`, `close`)

This is a perfect example of **mechanism vs. policy**:

* **Mechanism:** file descriptors and open file objects
* **Policy:** shell decides how to wire them up

---

## 8. One-Sentence Summary

> Standard output redirection is implemented by having the shell modify the child process’s file descriptor table so that file descriptor 1 points to a different open file table entry, causing all writes to standard output to be redirected to a file without the program’s knowledge.

