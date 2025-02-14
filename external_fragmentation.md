## **External Fragmentation and Optimization Strategies**

### **Objective:**
Develop a program that simulates external fragmentation in memory allocation and evaluates different strategies for minimizing it.

### **Overview:**
In this activity, students will build a **memory allocation simulator** that models how dynamic memory allocation can lead to **external fragmentation**. The program will then implement and compare different strategies to **reduce fragmentation**, such as compaction, best-fit allocation, and paging.

By completing this activity, students will be able to:
1. **Simulate memory allocation and deallocation** to observe the formation of external fragmentation.
2. **Implement and compare different memory allocation strategies** (First-Fit, Best-Fit, Worst-Fit).
3. **Analyze fragmentation and memory utilization** based on allocation strategy.
4. **Apply compaction or paging as a technique to minimize fragmentation** and evaluate its effectiveness.

### **Implementation Steps:**

#### **1. Define the Memory Model**
- Represent memory as a **fixed-size array or list** where each element is a memory block (e.g., 100 MB total, divided into 10 MB blocks).
- Track allocated and free memory blocks.

#### **2. Implement Memory Allocation Strategies**
- **First-Fit:** Assign the first available block that is large enough.
- **Best-Fit:** Assign the smallest free block that fits the requested size.
- **Worst-Fit:** Assign the largest free block available.

#### **3. Simulate External Fragmentation**
- Randomly allocate and deallocate memory blocks to create fragmented free space.
- Track and display external fragmentation after several allocation-deallocation cycles.

#### **4. Implement Fragmentation Minimization Strategies**
- **Compaction:** Shift allocated blocks to eliminate fragmented free spaces.
- **Paging:** Simulate breaking memory into fixed-size pages to avoid external fragmentation.

#### **5. Evaluate the Results**
- Compare **memory utilization and fragmentation** across different allocation strategies.
- Measure **performance impact** of compaction and paging.

### **Starter Code (Python)**
```python
import random

# Define memory size (in MB) and block size
MEMORY_SIZE = 100
BLOCK_SIZE = 10
NUM_BLOCKS = MEMORY_SIZE // BLOCK_SIZE

# Memory representation (1 = allocated, 0 = free)
memory = [0] * NUM_BLOCKS

# Function to allocate memory using First-Fit strategy
def allocate_memory(size, strategy="first-fit"):
    num_blocks_needed = size // BLOCK_SIZE
    best_index = -1

    if strategy == "first-fit":
        for i in range(NUM_BLOCKS - num_blocks_needed + 1):
            if all(memory[i:i + num_blocks_needed] == [0] * num_blocks_needed):
                best_index = i
                break

    elif strategy == "best-fit":
        min_size = float('inf')
        for i in range(NUM_BLOCKS - num_blocks_needed + 1):
            if all(memory[i:i + num_blocks_needed] == [0] * num_blocks_needed):
                free_size = sum(memory[i:i + num_blocks_needed])
                if free_size < min_size:
                    min_size = free_size
                    best_index = i

    elif strategy == "worst-fit":
        max_size = -1
        for i in range(NUM_BLOCKS - num_blocks_needed + 1):
            if all(memory[i:i + num_blocks_needed] == [0] * num_blocks_needed):
                free_size = sum(memory[i:i + num_blocks_needed])
                if free_size > max_size:
                    max_size = free_size
                    best_index = i

    if best_index != -1:
        for j in range(best_index, best_index + num_blocks_needed):
            memory[j] = 1
        return best_index
    else:
        return None  # No suitable block found

# Function to deallocate memory
def deallocate_memory(start_index, size):
    num_blocks = size // BLOCK_SIZE
    for i in range(start_index, start_index + num_blocks):
        memory[i] = 0

# Function to calculate external fragmentation
def calculate_external_fragmentation():
    free_blocks = [sum(1 for _ in group) for key, group in groupby(memory) if key == 0]
    if free_blocks:
        largest_free_block = max(free_blocks)
        total_free_memory = sum(free_blocks)
        fragmentation = (total_free_memory - largest_free_block) / total_free_memory * 100
        return round(fragmentation, 2)
    return 0

# Function to compact memory (defragmentation)
def compact_memory():
    allocated_blocks = [block for block in memory if block == 1]
    free_space = [0] * (NUM_BLOCKS - len(allocated_blocks))
    global memory
    memory = allocated_blocks + free_space  # Shift allocated blocks to the left

# Simulation: Allocate and deallocate memory randomly
random.seed(1)
for _ in range(5):
    size = random.choice([10, 20, 30])  # Allocate random block sizes
    start_index = allocate_memory(size, strategy="first-fit")
    if start_index is not None:
        print(f"Allocated {size}MB at block {start_index}")
    else:
        print("Memory allocation failed due to fragmentation")

print(f"External Fragmentation: {calculate_external_fragmentation()}%")

# Compact memory and check fragmentation again
compact_memory()
print(f"After Compaction - External Fragmentation: {calculate_external_fragmentation()}%")
```

### **Questions**
1. **Analyze Fragmentation Before and After Compaction**
   - Observe the fragmentation percentage before and after compaction.

2. **Compare Memory Allocation Strategies**
   - Modify the allocation strategy (`first-fit`, `best-fit`, `worst-fit`). Compare their impact on fragmentation and report your findings.