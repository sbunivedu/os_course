## `exit()` vs `_exit()`

* **`exit()`** performs **full process cleanup** (including user-space cleanup).
* **`_exit()`** terminates the process **immediately**, with **no user-space cleanup**.

In a **child process after `fork()`**, you almost always want **`_exit()`**, not `exit()`.

---

## What `exit()` Does

When you call:

```c
exit(status);
```

the C library performs **user-level cleanup** before the process terminates:

1. Calls functions registered with `atexit()`
2. Flushes and closes **stdio buffers** (`printf`, `stdout`, etc.)
3. Cleans up library state
4. Finally invokes the kernel system call `_exit(status)`

So:

```
exit()
  ├─ flush stdio buffers
  ├─ run atexit handlers
  └─ call _exit()
```

---

## What `_exit()` Does

When you call:

```c
_exit(status);
```

the process:

* **immediately enters the kernel**
* **terminates without any user-space cleanup**

No:

* stdio flushing
* `atexit()` handlers
* C library cleanup

Just:

```
_exit() → kernel → process dies
```

---

## Why This Matters After `fork()`

After `fork()`:

* Parent and child **share copies of stdio buffers**
* Those buffers may contain **unflushed output**

### ❌ Buggy behavior (using `exit()` in child)

```c
printf("hello ");
fork();
exit(0);
```

Possible output:

```
hello hello
```

Why?

* The buffer containing `"hello "` exists in **both parent and child**
* Both processes flush it when calling `exit()`

---

### ✅ Correct behavior (using `_exit()` in child)

```c
printf("hello ");
fork();
_exit(0);
```

Output:

```
hello
```

The child exits immediately without flushing buffers.

---

## Correct Rule of Thumb (Very Important)

### ✔ Use `exit()` when:

* You are in a **normal process**
* You want clean shutdown
* You are **not in a forked child that failed exec**

### ✔ Use `_exit()` when:

* You are in a **child process after `fork()`**
* `exec()` failed
* You want to avoid flushing parent buffers

---

## Typical Shell Pattern

```c
pid_t pid = fork();

if (pid == 0) {
    execvp(args[0], args);
    perror("execvp");  // only runs if exec fails
    _exit(127);        // NOT exit()
}
```

---

## Comparison Table

| Feature                  | `exit()`           | `_exit()`             |
| ------------------------ | ------------------ | --------------------- |
| Runs `atexit()` handlers | ✅                  | ❌                     |
| Flushes stdio buffers    | ✅                  | ❌                     |
| Safe after `fork()`      | ❌                  | ✅                     |
| Calls kernel directly    | ❌                  | ✅                     |
| Intended use             | Normal termination | Low-level termination |

---

## Exam-Ready One-Liner

> `exit()` performs user-level cleanup before terminating a process, whereas `_exit()` immediately terminates the process without flushing stdio buffers or running cleanup handlers, which is why `_exit()` must be used in a child process after `fork()`.
