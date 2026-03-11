# Exploring Threads and Race Conditions in Java

By the end of this exercise, students should be able to:

* create and run multiple Java threads
* observe nondeterministic behavior in concurrent programs
* explain what a race condition is
* see why `count++` is not safe when shared across threads
* fix a race condition using synchronization

# Warm-up — creating threads

## Create a simple threaded program

Create a file named `ThreadWarmup.java`.

```java
public class ThreadWarmup {
  static class MyTask extends Thread {
    private String taskName;

    public MyTask(String taskName) {
      this.taskName = taskName;
    }

    @Override
    public void run() {
      for (int i = 1; i <= 5; i++) {
        System.out.println(taskName + " is running: step " + i);
      }
    }
  }

  public static void main(String[] args) {
    MyTask t1 = new MyTask("Thread-A");
    MyTask t2 = new MyTask("Thread-B");

    t1.start();
    t2.start();

    System.out.println("Main thread finished launching worker threads.");
  }
}
```

## Run it several times

Compile and run:

```bash
javac ThreadWarmup.java
java ThreadWarmup
```

Run it at least 3 times.

## What to notice

Look at the order of the printed lines.

Question 1:
* Does `Thread-A` always finish before `Thread-B`?
* Is the output order exactly the same every time?

## Key idea

Thread scheduling is not fully under your control. Even if the code is the same, the output order can change from run to run.

# Shared data without protection

Lets write a program where multiple threads update the same variable.

## Create a counter program

Create a file named `RaceConditionDemo.java`.

```java
public class RaceConditionDemo {
  static int counter = 0;

  static class CounterTask extends Thread {
    private int numIncrements;

    public CounterTask(int numIncrements) {
      this.numIncrements = numIncrements;
    }

    @Override
    public void run() {
      for (int i = 0; i < numIncrements; i++) {
        counter++; // not thread-safe
      }
    }
  }

  public static void main(String[] args) throws InterruptedException {
    int incrementsPerThread = 100000;

    Thread t1 = new CounterTask(incrementsPerThread);
    Thread t2 = new CounterTask(incrementsPerThread);

    t1.start();
    t2.start();

    t1.join();
    t2.join();

    System.out.println("Expected counter value: " + (2 * incrementsPerThread));
    System.out.println("Actual counter value:   " + counter);
  }
}
```

## Predict before running

Question 2:

* What value do you expect `counter` to have at the end?
* Why?

## Run it multiple times

Compile and run:

```bash
javac RaceConditionDemo.java
java RaceConditionDemo
```

Run it several times.

## What to notice

The final result may sometimes be less than `200000`.

Question 3:

* Did you always get the expected answer?
* If not, why might some increments be “lost”?

# Understanding the race condition

## Break down `counter++`

This line:

```java
counter++;
```

is not one indivisible operation.

It is roughly:

1. read `counter`
2. add 1
3. write the new value back

If two threads do this at the same time, both may read the same old value and both may write back the same new value.

### Example interleaving

Suppose `counter = 5`.

* Thread A reads `5`
* Thread B reads `5`
* Thread A computes `6`
* Thread B computes `6`
* Thread A writes `6`
* Thread B writes `6`

Expected result after two increments: `7`
Actual result: `6`

One increment was lost.

That is a **race condition**: the result depends on the timing of the threads.

# Fixing the race condition with synchronization

## Create a synchronized increment method

Replace the code with this version:

```java
public class RaceConditionDemo {
  static int counter = 0;

  static class CounterTask extends Thread {
    private int numIncrements;

    public CounterTask(int numIncrements) {
      this.numIncrements = numIncrements;
    }

    @Override
    public void run() {
      for (int i = 0; i < numIncrements; i++) {
        counter++; // not thread-safe
      }
    }
  }

  public static void main(String[] args) throws InterruptedException {
    int incrementsPerThread = 100000;

    Thread t1 = new CounterTask(incrementsPerThread);
    Thread t2 = new CounterTask(incrementsPerThread);

    t1.start();
    t2.start();

    t1.join();
    t2.join();

    System.out.println("Expected counter value: " + (2 * incrementsPerThread));
    System.out.println("Actual counter value:   " + counter);
  }
}
```

Compile and run:

```bash
javac RaceConditionDemoFixed.java
java RaceConditionDemoFixed
```

## What to notice

The final value should now consistently match the expected value.

# Why synchronization works

Explain:

* `synchronized` allows only one thread at a time to execute that method on the shared object/class monitor
* this creates a **critical section**
* the read-modify-write sequence is now protected from interference by other threads

Question 4:
* Why is `counter++` not thread-safe?
* What is a race condition in your own words?
* Why does the final value sometimes end up smaller than expected rather than larger?

## Experimentation

What happened when you increased the number of threads? Did the bug appear every time? Why or why not? Why does testing a concurrent program only once give false confidence?

Question 5:
* Why are concurrency bugs often hard to reproduce?

## Main concepts reinforced

* thread creation
* start vs run
* join
* shared memory
* interleaving
* nondeterminism
* race conditions
* mutual exclusion with `synchronized`

## Common misunderstandings

* thinking `counter++` is a single atomic machine action
* forgetting to call `start()` and calling `run()` directly instead
* forgetting `join()`, causing the main thread to print before workers finish
* assuming “it worked once” means “it is correct”
