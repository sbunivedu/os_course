## **Implementing a Memory Manager with Swapping on Page Faults**

### **Objective**
Students will design and implement a simple **memory manager** that simulates **demand paging with swapping**. The memory manager should:
- Maintain a **limited number of physical memory frames**.
- **Trigger swapping** when a **page fault** occurs by replacing an old page using a **FIFO or LRU page replacement policy**.
- Load the required page from **swap storage** into RAM.

## **Implementation Details**
- **Virtual memory size**: Assume a large addressable space (e.g., 64 pages).
- **Physical memory size**: Assume a small number of frames (e.g., 4 frames).
- **Page replacement policy**: Implement **FIFO (First-In, First-Out)** or **LRU (Least Recently Used)**.
- **Swap storage**: Use a dictionary or list to store pages that are not in RAM.

### **Define Memory Structures**
- **Page Table**: Maps virtual pages to physical frames.
- **Physical Memory (RAM)**: Holds currently loaded pages.
- **Swap Storage**: Holds pages that are not in RAM.
- **Page Replacement Algorithm**: Determines which page to evict when memory is full.

---

### **Python Solution**
```python
import random
from collections import deque, OrderedDict

# Constants
NUM_VIRTUAL_PAGES = 64   # Virtual memory has 64 pages
NUM_PHYSICAL_FRAMES = 4  # Only 4 physical frames available (simulating limited RAM)
PAGE_SIZE = 4096         # Each page is 4 KB

# Simulated swap storage (disk)
swap_storage = {i: f"Page Data {i}" for i in range(NUM_VIRTUAL_PAGES)}

# Page Table: Maps virtual pages to physical frames
page_table = {}  # {Virtual Page Number -> Physical Frame Number}

# Physical memory representation
physical_memory = {}  # {Frame Number -> Virtual Page Number}

# Page Replacement Queue (FIFO Policy)
page_queue = deque()  # Stores the order of pages in RAM

# Function to simulate page access
def access_page(vpn):
    global page_table, physical_memory, page_queue

    print(f"\nAccessing Virtual Page {vpn}")

    # Check if the page is already in memory
    if vpn in page_table:
        frame_number = page_table[vpn]
        print(f"Page {vpn} is already in RAM at Frame {frame_number}. No page fault.")
        return

    # PAGE FAULT OCCURS
    print(f"PAGE FAULT! Page {vpn} is not in RAM.")

    # If there is space in RAM, load page without replacement
    if len(physical_memory) < NUM_PHYSICAL_FRAMES:
        frame_number = len(physical_memory)  # Assign next free frame
    else:
        # RAM is full; Perform page replacement (FIFO)
        evicted_vpn = page_queue.popleft()  # Remove the oldest page (FIFO)
        frame_number = page_table.pop(evicted_vpn)  # Free its frame
        del physical_memory[frame_number]  # Remove from memory
        print(f"Swapping out Page {evicted_vpn} from Frame {frame_number} to disk.")

    # Load new page into the selected frame
    physical_memory[frame_number] = vpn
    page_table[vpn] = frame_number
    page_queue.append(vpn)

    print(f"Loaded Page {vpn} into Frame {frame_number}.")

# Simulating a sequence of page accesses
random.seed(42)  # For reproducibility
virtual_page_accesses = [random.randint(0, NUM_VIRTUAL_PAGES - 1) for _ in range(12)]

print("\nSimulating Memory Management with Swapping:")
for vpn in virtual_page_accesses:
    access_page(vpn)

# Print final memory state
print("\nFinal RAM State:")
for frame, vpn in physical_memory.items():
    print(f"Frame {frame}: Virtual Page {vpn}")
```

---

### **Comments on Code**
1. **Simulated Memory**
   - We assume **64 virtual pages** but only **4 physical frames**.
   - Virtual pages not in RAM are stored in **swap storage** (disk).

2. **Page Fault Handling**
   - If a page is **not in RAM**, a **page fault** occurs.
   - If RAM has free space, the page is simply loaded.
   - If RAM is **full**, a page is **evicted (swapped out)** using **FIFO**.
   - The evicted page is removed from RAM and stored back in **swap storage**.

3. **FIFO Page Replacement**
   - When RAM is full, **the oldest page is evicted**.
   - This mimics **real-world swapping**, where **inactive pages** are replaced first.

4. **Simulation of Page Access**
   - The script randomly generates **12 virtual page accesses**.
   - It prints whether the page is **already in RAM** or **causes a page fault**.
   - It tracks the **RAM state** after each access.

### **Example Output**
```
Simulating Memory Management with Swapping:

Accessing Virtual Page 40
PAGE FAULT! Page 40 is not in RAM.
Loaded Page 40 into Frame 0.

Accessing Virtual Page 7
PAGE FAULT! Page 7 is not in RAM.
Loaded Page 7 into Frame 1.

Accessing Virtual Page 1
PAGE FAULT! Page 1 is not in RAM.
Loaded Page 1 into Frame 2.

Accessing Virtual Page 47
PAGE FAULT! Page 47 is not in RAM.
Loaded Page 47 into Frame 3.

Accessing Virtual Page 17
PAGE FAULT! Page 17 is not in RAM.
Swapping out Page 40 from Frame 0 to disk.
Loaded Page 17 into Frame 0.

Accessing Virtual Page 15
PAGE FAULT! Page 15 is not in RAM.
Swapping out Page 7 from Frame 1 to disk.
Loaded Page 15 into Frame 1.

Accessing Virtual Page 14
PAGE FAULT! Page 14 is not in RAM.
Swapping out Page 1 from Frame 2 to disk.
Loaded Page 14 into Frame 2.

Accessing Virtual Page 49
PAGE FAULT! Page 49 is not in RAM.
Swapping out Page 47 from Frame 3 to disk.
Loaded Page 49 into Frame 3.

Accessing Virtual Page 17
Page 17 is already in RAM at Frame 0. No page fault.

Accessing Virtual Page 7
PAGE FAULT! Page 7 is not in RAM.
Swapping out Page 17 from Frame 0 to disk.
Loaded Page 7 into Frame 0.

Accessing Virtual Page 31
PAGE FAULT! Page 31 is not in RAM.
Swapping out Page 15 from Frame 1 to disk.
Loaded Page 31 into Frame 1.

Accessing Virtual Page 38
PAGE FAULT! Page 38 is not in RAM.
Swapping out Page 14 from Frame 2 to disk.
Loaded Page 38 into Frame 2.

Final RAM State:
Frame 0: Virtual Page 7
Frame 1: Virtual Page 31
Frame 2: Virtual Page 38
Frame 3: Virtual Page 49
```

---

## **Questions**
1. **Explain how swapping improves memory efficiency.**
2. **What is the downside of using FIFO for page replacement?**
3. **Modify the code to implement the LRU (Least Recently Used) policy.**
4. **What happens if the swap space is full? How does a real OS handle it?**
