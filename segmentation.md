## **Simulating Simple Memory Segmentation**

### **Objective**
Students will study and modify a **simple memory segmentation simulator** to understand how an operating system manages memory using **variable-sized segments**. The simulator should:
- Represent a **process's memory layout** using **segments**.
- Support **dynamic allocation and deallocation** of segments.
- Simulate **external fragmentation** and the **first-fit allocation strategy**.

### **Implementation Details**
- **Memory size**: Assume a fixed total **physical memory** (e.g., 1000 units).
- **Segments**: Processes can request memory as **variable-sized segments**.
- **Allocation Strategy**: Use **first-fit** (allocate memory in the first available free block).
- **Deallocation**: Freeing memory should **merge adjacent free blocks** to minimize fragmentation.
- **Visualization**: Print memory layout before and after allocations and deallocations.

### **Step-by-Step Implementation**
1. **Define memory as a list of allocated/free blocks.**
2. **Implement first-fit allocation** to assign memory to processes.
3. **Implement deallocation** with memory compaction (merging adjacent free blocks).
4. **Simulate segment allocation, deallocation, and fragmentation.**

### **Python Solution**
```python
class Segment:
    def __init__(self, pid, start, size):
        self.pid = pid  # Process ID (None if free)
        self.start = start
        self.size = size

    def __repr__(self):
        status = f"Process {self.pid}" if self.pid is not None else "Free"
        return f"[{status}: {self.start}-{self.start + self.size - 1}]"

class Memory:
    def __init__(self, total_size):
        self.total_size = total_size
        self.segments = [Segment(None, 0, total_size)]  # Entire memory is initially free

    def allocate(self, pid, size):
        """ Allocates a segment using the First-Fit strategy """
        for segment in self.segments:
            if segment.pid is None and segment.size >= size:
                start = segment.start
                segment.pid = pid
                if segment.size > size:
                    new_segment = Segment(None, start + size, segment.size - size)
                    self.segments.insert(self.segments.index(segment) + 1, new_segment)
                segment.size = size
                print(f"Allocated {size} units to Process {pid} at {start}.")
                return True
        print(f"Allocation failed for Process {pid} (Not enough space).")
        return False

    def deallocate(self, pid):
        """ Frees the memory segment for a process and merges adjacent free blocks """
        for segment in self.segments:
            if segment.pid == pid:
                segment.pid = None
                print(f"Deallocated memory for Process {pid}.")
                break
        self.compact_memory()

    def compact_memory(self):
        """ Merge adjacent free segments to minimize fragmentation """
        i = 0
        while i < len(self.segments) - 1:
            if self.segments[i].pid is None and self.segments[i + 1].pid is None:
                self.segments[i].size += self.segments[i + 1].size
                del self.segments[i + 1]  # Remove merged segment
            else:
                i += 1

    def display(self):
        """ Prints the current memory layout """
        print("\nMemory Layout:")
        for segment in self.segments:
            print(segment)
        print("-" * 50)

# Simulating memory allocation and deallocation
memory = Memory(1000)

# Allocate segments
memory.allocate(1, 200)
memory.allocate(2, 300)
memory.allocate(3, 150)
memory.display()

# Deallocate process 2 to create fragmentation
memory.deallocate(2)
memory.display()

# Allocate a new segment (should reuse freed space)
memory.allocate(4, 250)
memory.display()
```

### **Comment on the Code**
1. **Memory Representation**
   - Memory is a **list of segments**, each representing either an **allocated process** or a **free block**.
   - Each segment has a **starting address, size, and process ID**.

2. **First-Fit Allocation Strategy**
   - The **first available free block** large enough for the request is selected.
   - If the free block is **larger than needed**, it is **split into allocated and free segments**.

3. **Deallocation & Memory Compaction**
   - When a process releases memory, the segment becomes **free**.
   - The **compaction function** merges adjacent **free segments** to **reduce fragmentation**.

4. **Simulation Example**
   - Processes are allocated memory sequentially.
   - A process is deallocated, creating **external fragmentation**.
   - A new allocation demonstrates **reusing fragmented space**.

---

### **Expected Output**
```
Allocated 200 units to Process 1 at 0.
Allocated 300 units to Process 2 at 200.
Allocated 150 units to Process 3 at 500.

Memory Layout:
[Process 1: 0-199]
[Process 2: 200-499]
[Process 3: 500-649]
[Free: 650-999]
--------------------------------------------------

Deallocated memory for Process 2.

Memory Layout:
[Process 1: 0-199]
[Free: 200-499]
[Process 3: 500-649]
[Free: 650-999]
--------------------------------------------------

Allocated 250 units to Process 4 at 200.

Memory Layout:
[Process 1: 0-199]
[Process 4: 200-449]
[Free: 450-499]
[Process 3: 500-649]
[Free: 650-999]
--------------------------------------------------
```

### **Questions**
1. **Create a scenario in which there is enough (total) memory but no single free block is large enough for the allocation. Report the actual output of your scenario.**
2. **What are the advantages and disadvantages of first-fit allocation?**
3. **(Optional) Modify the code to implement the best-fit and worst-fit allocation strategies. Create a few test scenarios and report the actual output of the scenarios.**

### **Expected Learning Outcomes**
- **Understand how memory segmentation works** in an OS.
- **Simulate memory allocation, deallocation, and fragmentation** through code.
- **Gain hands-on experience with dynamic memory management.**
- **Analyze and discuss real-world OS memory allocation challenges.**
