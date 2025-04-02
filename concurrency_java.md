### **Synchronization in Java with Monitors and Semaphores**

#### **Objective:**
Students will experiment with **multi-threading** in Java to understand **synchronization mechanisms** such as **monitors** and **semaphores**. They will solve **classic inter-process communication (IPC) problems**, including the **Bounded Buffer** (Producer-Consumer) and **Reader-Writer** problems, ensuring correct concurrent behavior.

## Activity I: Implementing the Bounded Buffer (Producer-Consumer) Problem Using Semaphores

### **Instructions:**
1. **Understand the Problem:** The bounded buffer problem models a scenario where producers generate data and place it into a shared buffer, while consumers retrieve data. The buffer has a fixed capacity, and synchronization is required to prevent race conditions and deadlocks.
2. **Implement a Shared Buffer Using Semaphores:**
   - Use a **semaphore** to track the number of available slots (`empty`).
   - Use a **semaphore** to track the number of filled slots (`full`).
   - Use a **mutex semaphore** to ensure mutual exclusion when accessing the buffer.
3. **Create Producer and Consumer Threads:**
   - The **producer** should wait if the buffer is full and then produce an item.
   - The **consumer** should wait if the buffer is empty and then consume an item.
4. **Run the Program and Observe Behavior:** Execute the program with multiple producers and consumers. Ensure correctness by verifying that items are consumed in the correct order without corruption.

### **Sample Code (Bounded Buffer with Semaphores)**

```java
import java.util.concurrent.Semaphore;
import java.util.LinkedList;

class BoundedBuffer {
    private final int capacity;
    private final LinkedList<Integer> buffer = new LinkedList<>();
    private final Semaphore empty; // Tracks empty slots
    private final Semaphore full;  // Tracks filled slots
    private final Semaphore mutex; // Ensures mutual exclusion

    public BoundedBuffer(int capacity) {
        this.capacity = capacity;
        this.empty = new Semaphore(capacity);
        this.full = new Semaphore(0);
        this.mutex = new Semaphore(1);
    }

    public void produce(int item) throws InterruptedException {
        empty.acquire(); // Wait for an empty slot
        mutex.acquire(); // Ensure mutual exclusion

        buffer.add(item);
        System.out.println("Produced: " + item);

        mutex.release();
        full.release(); // Signal that an item is available
    }

    public int consume() throws InterruptedException {
        full.acquire(); // Wait for an available item
        mutex.acquire(); // Ensure mutual exclusion

        int item = buffer.removeFirst();
        System.out.println("Consumed: " + item);

        mutex.release();
        empty.release(); // Signal that a slot is available
        return item;
    }
}

class Producer extends Thread {
    private final BoundedBuffer buffer;

    public Producer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            for (int i = 1; i <= 5; i++) {
                buffer.produce(i);
                Thread.sleep(100); // Simulate time taken to produce
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Consumer extends Thread {
    private final BoundedBuffer buffer;

    public Consumer(BoundedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        try {
            for (int i = 1; i <= 5; i++) {
                buffer.consume();
                Thread.sleep(150); // Simulate time taken to consume
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class ProducerConsumerTest {
    public static void main(String[] args) {
        BoundedBuffer buffer = new BoundedBuffer(3);
        new Producer(buffer).start();
        new Consumer(buffer).start();
    }
}
```

### **Predict and Analyze Questions:**
1. **Prediction:** What do you expect to happen if multiple producer and consumer threads are running simultaneously?
2. **Scenario Analysis:** What would happen if the `mutex` semaphore was removed from the program?
3. **Comparison:** Implement an **unsynchronized version** of the producer-consumer problem (remove the semaphores) and compare its output with the synchronized version. What kind of inconsistencies or race conditions do you observe?
4. **Prediction:** What if we add more producers and consumers? Would the program behave correctly? Why?

## **Activity II: Solving the Reader-Writer Problem Using Java Monitors**

### **Instructions:**
1. **Understand the Problem:** In the **Reader-Writer problem**, multiple **readers** can read simultaneously, but a **writer** must have exclusive access. The sample code shows a solution using Java’s **synchronized keyword (monitors)**.
2. **Implement a Shared Resource:**
   - Use **counters** to track active readers and writers.
   - Ensure that multiple readers can access the resource simultaneously.
   - Ensure that **writers have exclusive access** and block readers if writing is in progress.
3. **Implement Reader and Writer Threads:**
   - A **reader** should read if no writer is writing.
   - A **writer** should write only if no reader or writer is active.
4. **Run the Program and Observe Behavior:** Check that no two writers execute simultaneously and that multiple readers can execute concurrently.

### **Sample Code (Reader-Writer with Monitors)**

```java
class ReadWriteLock {
    private int readers = 0;
    private boolean isWriting = false;

    public synchronized void startRead() throws InterruptedException {
        while (isWriting) {
            wait(); // Wait if a writer is active
        }
        readers++;
    }

    public synchronized void endRead() {
        readers--;
        if (readers == 0) {
            notifyAll(); // Allow a waiting writer to proceed
        }
    }

    public synchronized void startWrite() throws InterruptedException {
        while (readers > 0 || isWriting) {
            wait(); // Wait if there are active readers or a writer
        }
        isWriting = true;
    }

    public synchronized void endWrite() {
        isWriting = false;
        notifyAll(); // Allow waiting readers/writers to proceed
    }
}

class Reader extends Thread {
    private final ReadWriteLock lock;

    public Reader(ReadWriteLock lock) {
        this.lock = lock;
    }

    public void run() {
        try {
            lock.startRead();
            System.out.println(Thread.currentThread().getName() + " is reading...");
            Thread.sleep(100);
            System.out.println(Thread.currentThread().getName() + " finished reading.");
            lock.endRead();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Writer extends Thread {
    private final ReadWriteLock lock;

    public Writer(ReadWriteLock lock) {
        this.lock = lock;
    }

    public void run() {
        try {
            lock.startWrite();
            System.out.println(Thread.currentThread().getName() + " is writing...");
            Thread.sleep(200);
            System.out.println(Thread.currentThread().getName() + " finished writing.");
            lock.endWrite();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class ReaderWriterTest {
    public static void main(String[] args) {
        ReadWriteLock lock = new ReadWriteLock();

        Reader r1 = new Reader(lock);
        Reader r2 = new Reader(lock);
        Writer w1 = new Writer(lock);
        Writer w2 = new Writer(lock);

        r1.start();
        r2.start();
        w1.start();
        w2.start();
    }
}
```

### **Predict and Analyze Questions:**
1. **Prediction:** If two reader threads and one writer thread start simultaneously, what will happen? Will the writer be able to execute first?
2. **Scenario Analysis:** Suppose there are many readers and writers competing for access. Could **starvation** (e.g., a writer waiting indefinitely due to many readers) happen? If yes, how could this implement prevent starvation.
3. **Comparison:** Modify the program to **remove the synchronized blocks** and run multiple reader-writer threads. What happens when synchronization is removed?
4. **Optimization:** How can you modify this program to give priority to writers over readers?
