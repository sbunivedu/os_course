## **Simulating Paging and Virtual Memory with a Page Table**

### **Objective:**
Demonstrate how paging and virtual memory work by designing and implementing a simple page table simulation.

### **Description:**
In this activity, students will implement a simple page table simulation in Python to translate virtual addresses to physical addresses. The program will model how an operating system maps virtual memory pages to physical frames using a page table.

By completing this activity, students will be able to:
1. Understand how an operating system translates virtual addresses to physical addresses.
2. Implement a basic page table that maps virtual pages to physical frames.
3. Handle page faults and simulate a simple page replacement mechanism.

### **Implementation Steps:**

#### **1. Define the System Parameters**
- Define the number of virtual pages (`NUM_VIRTUAL_PAGES`).
- Define the number of physical frames (`NUM_PHYSICAL_FRAMES`).
- Define the size of each page (assumed constant).

#### **2. Create the Page Table Structure**
- Implement a page table as a dictionary or list that maps virtual page numbers to physical frame numbers.
- Implement a **valid bit** to indicate whether the page is loaded in memory.

#### **3. Implement Address Translation**
- Given a virtual address, extract the virtual page number and offset.
- Use the page table to determine the corresponding physical frame.
- Compute the physical address using the frame number and offset.

#### **4. Handle Page Faults**
- If a page is not present (valid bit = 0), simulate a **page fault**.
- If there is a free frame, load the page into memory.
- If memory is full, implement a simple page replacement strategy (e.g., FIFO or LRU).

#### **5. Simulate Memory Accesses**
- Accept a sequence of virtual addresses from the user or generate them randomly.
- Translate each address and track page faults.
- Print the updated page table and memory state.

### **Starter Code (Python)**
```python
import random
from collections import deque

# System parameters
NUM_VIRTUAL_PAGES = 8
NUM_PHYSICAL_FRAMES = 4
PAGE_SIZE = 1024  # Assume each page is 1024 bytes

# Page Table (virtual page -> physical frame mapping)
page_table = {}  # Stores {virtual_page: physical_frame}
valid_bit = {}  # Tracks if a page is in memory
frame_queue = deque()  # FIFO page replacement queue
frame_mapping = {}  # Reverse mapping (physical frame -> virtual page)
page_fault_count = 0  # Counter for page faults

# Function to translate virtual address to physical address
def translate_address(virtual_address):
    global page_fault_count

    # Extract virtual page number and offset
    page_number = virtual_address // PAGE_SIZE
    offset = virtual_address % PAGE_SIZE

    # Check if page is in memory
    if page_number in page_table and valid_bit[page_number]:
        frame_number = page_table[page_number]
        physical_address = (frame_number * PAGE_SIZE) + offset
        print(f"Virtual Address {virtual_address} -> Physical Address {physical_address} (Page Hit)")
    else:
        # Page fault occurs
        page_fault_count += 1
        handle_page_fault(page_number)
        # Retry translation after loading page
        translate_address(virtual_address)

# Function to handle page faults
def handle_page_fault(page_number):
    print(f"Page fault occurred for page {page_number}!")

    if len(frame_queue) < NUM_PHYSICAL_FRAMES:
        # Allocate a new frame if available
        frame_number = len(frame_queue)
        frame_queue.append(page_number)
    else:
        # Page replacement (FIFO strategy)
        evicted_page = frame_queue.popleft()
        del page_table[evicted_page]
        valid_bit[evicted_page] = False
        frame_number = frame_mapping[evicted_page]
        print(f"Evicting page {evicted_page} from frame {frame_number}")

    # Load new page into the available frame
    page_table[page_number] = frame_number
    valid_bit[page_number] = True
    frame_queue.append(page_number)
    frame_mapping[page_number] = frame_number

    print(f"Page {page_number} loaded into frame {frame_number}")

# Simulate memory accesses with random virtual addresses
random.seed(1)  # Ensures reproducibility
virtual_addresses = [random.randint(0, NUM_VIRTUAL_PAGES * PAGE_SIZE - 1) for _ in range(10)]

print("\nSimulating Virtual Address Translation:\n")
for v_addr in virtual_addresses:
    translate_address(v_addr)

print(f"\nTotal Page Faults: {page_fault_count}")
```

---

### **Questions**
1. Run the simulation and observe the output. Pick a "Page Fault" case and a "Page Hit" case and describe step by step what happends behind the scene.
2. Modify the page replacement policy to use LRU (Least Recently Used) instead of FIFO. Increase the number of physical frames and observe its impact on page faults. Track hit rates and miss rates to analyze memory access performance and report your findings.
