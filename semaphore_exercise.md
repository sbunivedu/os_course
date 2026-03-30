# Implementing a Semaphore in Java Using Monitors

We will implement a simple **counting semaphore** in Java using the built-in monitor mechanism:

* `synchronized`
* `wait()`
* `notifyAll()`

The Core idea:

* A semaphore keeps track of how many permits are available.
* `acquire()` waits until a permit is available, then takes one.
* `release()` returns a permit and wakes up waiting threads.

## Background

A **semaphore** is a synchronization tool that controls access to a shared resource.

You can think of it as a box containing a certain number of “permits.”

* If a thread wants to enter, it must take a permit.
* If no permit is available, the thread must wait.
* When a thread leaves, it puts a permit back.

### Example

If a semaphore starts with value `2`, then:

* the first thread can enter
* the second thread can enter
* the third thread must wait until one of the first two releases a permit


## Templete

Please use this class as a template:

```java
public class SimpleSemaphore {
  private int permits;

  public SimpleSemaphore(int initialPermits) {
    // TODO
  }

  public synchronized void acquire() throws InterruptedException {
    // TODO
  }

  public synchronized void release() {
    // TODO
  }
}
```

## Part 1: Understand the behavior

Before writing code, answer these questions.

### Q1

What should happen if `acquire()` is called when `permits > 0`?

**Answer:** The thread should decrease `permits` by 1 and continue.

### Q2

What should happen if `acquire()` is called when `permits == 0`?

<details>
<summary>answer</summary>

The thread should wait until a permit becomes available.
</details>

### Q3

What should happen in `release()`?

<details>
<summary>answer</summary>

Increase `permits` by 1 and wake up waiting threads.
</details>

## Part 2: Why use a monitor?

In Java, every object can act as a **monitor**.

When a method is marked `synchronized`:

* only one thread at a time can execute that method on the same object
* the shared state is protected
* threads can call `wait()` to sleep
* another thread can call `notifyAll()` to wake waiting threads

This makes Java monitors a natural way to build a semaphore.

## Part 3: Fill in the template step by step

## Step 1: Store the number of permits

This variable is the semaphore state - the number of permits:

```java
private int permits;
```

## Step 2: Write the constructor

The constructor should set the initial number of permits.

### Guiding question

Why might we reject a negative initial value?

<details>
<summary>answer</summary>

Because a semaphore should not start with a negative number of available permits.
</details>

### Suggested code

```java
public SimpleSemaphore(int initialPermits) {
  if (initialPermits < 0) {
    throw new IllegalArgumentException("permits cannot be negative");
  }
  permits = initialPermits;
}
```

## Step 3: Write `acquire()`

### Core idea

If no permit is available, the thread must wait.

But the check must be done with a `while`, not an `if`.

### Guiding question

Why use `while` instead of `if`?

<details>
<summary>answer</summary>

Because after waking up, the thread must check the condition again. Another thread may have taken the permit first, or the wake-up may have happened spuriously.
</details>

### Template

```java
public synchronized void acquire() throws InterruptedException {
  while (permits == 0) {
    wait();
  }
  permits--;
}
```

### What this means

* The method is synchronized, so only one thread can check/change `permits` at a time.
* If `permits == 0`, the thread calls `wait()`.
* Calling `wait()` temporarily releases the monitor lock and sleeps.
* When awakened, the thread re-acquires the lock and checks again.
* When a permit exists, it decrements `permits`.

## Step 4: Write `release()`

### Core idea

Returning a permit should wake up waiting threads.

### Template

```java
public synchronized void release() {
  permits++;
  notifyAll();
}
```

Why use `notifyAll()` instead of `notify()`?

<details>
<summary>answer</summary>

Because multiple threads may be waiting, and `notifyAll()` is safer in simple monitor designs. Each awakened thread will re-check the condition, and only one will proceed if only one permit is available.
</details>

## Part 4: Test program

Use this small driver to see the semaphore in action.

```java
public class SemaphoreTest {
  public static void main(String[] args) {
    SimpleSemaphore sem = new SimpleSemaphore(2);

    Runnable task = () -> {
        String name = Thread.currentThread().getName();
        try {
            System.out.println(name + " wants to enter");
            sem.acquire();
            System.out.println(name + " entered");

            Thread.sleep(2000);

            System.out.println(name + " leaving");
            sem.release();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    };

    for (int i = 1; i <= 5; i++) {
        Thread t = new Thread(task);
        t.setName("Thread-" + i);
        t.start();
    }
  }
}
```

## Part 5: Observations

Since the semaphore starts with `2` permits:

* only two threads should print `entered` at first
* the others should wait
* as threads call `release()`, waiting threads should proceed

### Reflection

Watch the output carefully.

1. Do all five threads enter immediately?
2. How many can be inside at the same time?
3. What changes if the semaphore starts with 1 permit instead of 2?
4. What changes if it starts with 3 permits?

## Part 7: Trace the semaphore state

Complete a trace like this for a semaphore with 1 permit.

| Event            | permits before | permits after | Waiting threads? |
| ---------------- | -------------: | ------------: | ---------------- |
| Start            |              1 |             1 | No               |
| T1 calls acquire |              1 |             0 | No               |
| T2 calls acquire |              0 |             0 | Yes              |
| T1 calls release |              0 |             1 | T2 can wake      |
| T2 continues     |              1 |             0 | No               |

### Discussion question

Why does `T2` not continue immediately when it first calls `acquire()`?

<details>
<summary>answer</summary>

Because it must wait until some other thread releases a permit.
</details>

## Part 8: Important ideas to highlight

### 1. Semaphore state is shared state

The variable `permits` is shared by multiple threads, so access must be protected.

### 2. `synchronized` provides mutual exclusion

Only one thread at a time can execute `acquire()` or `release()` on the same semaphore object.

### 3. `wait()` suspends the thread

A waiting thread gives up the monitor lock so another thread can enter and change the state.

### 4. `while` is essential

Always re-check the condition after waking up.

### 5. `release()` signals possible progress

When a permit is returned, waiting threads should be notified.

## Part 9: Guided questions

Use these during the exercise.

### Concept check 1

Why is a semaphore useful?
<details>
<summary>answer</summary>

It controls how many threads may access a resource at once.
</details>

### Concept check 2

What does the value of `permits` represent?

<details>
<summary>answer</summary>

The number of available permits.
</details>

### Concept check 3

Why must `acquire()` be synchronized?

<details>
<summary>answer</summary>

To prevent race conditions when threads check and update `permits`.
</details>

### Concept check 4

Why does `wait()` need to be called inside synchronized code?

<details>
<summary>answer</summary>

Because a thread must own the monitor lock before calling `wait()` on that object.
</details>

### Concept check 5

Why can’t we write this?

```java
if (permits == 0) {
    wait();
}
permits--;
```

<details>
<summary>answer</summary>

Because after waking up, the condition may no longer be true. The thread must check again with `while`.
</details>

## Part 10: Optional small extensions

Once students finish the core version, give one or two simple extensions.

### Extension A: Add a getter for debugging

```java
public synchronized int availablePermits() {
    return permits;
}
```

Why should this also be synchronized?

<details>
<summary>answer</summary>

Because it reads shared state.
</details>

### Extension B: Make a binary semaphore

What happens if the semaphore is only supposed to have values 0 or 1?

This helps connect semaphores to locks.

## Part 11: Common mistakes

### Mistake 1

Using `if` instead of `while`

### Mistake 2

Forgetting `synchronized`

### Mistake 3

Calling `wait()` or `notifyAll()` on the wrong object

### Mistake 4

Decrementing `permits` before waiting

Bad idea:

```java
permits--;
if (permits < 0) {
    wait();
}
```

This mixes the logic and makes the design harder for beginners to reason about.

## Part 12: Short wrap-up

A semaphore is built from two simple ideas:

* keep track of available permits
* make threads wait when no permit is available

Using Java monitors:

* `synchronized` protects the shared state
* `wait()` blocks when progress is impossible
* `notifyAll()` wakes waiting threads when the state changes

That is the core of semaphore behavior.
