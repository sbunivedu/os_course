## **Implementing a Simple Page Table Simulation**

### **Objective**
Students will **design and implement a simple page table simulator** to demonstrate how an operating system **translates virtual addresses to physical addresses** using **paging and virtual memory**.

The simulation should:
- Use **fixed-size pages and frames**.
- Map **virtual page numbers (VPNs) to physical frame numbers (PFNs)** using a **page table**.
- Handle **page faults** when accessing an unmapped page.
- Simulate **paging with a limited number of physical frames** and use a **FIFO page replacement policy** when memory is full.

### **Implementation Details**
- **Virtual Memory**: Assume a process has **16 virtual pages** (numbered 0 to 15).
- **Physical Memory**: Only **4 physical frames** are available.
- **Page Size**: Each page is **4 KB** (not directly simulated).
- **Page Table**: A dictionary mapping **virtual pages to physical frames**.
- **Page Replacement**: Implement **FIFO** to swap out old pages when memory is full.

### **Step-by-Step Implementation**
1. **Define page table structure** for mapping virtual pages to physical frames.
2. **Implement page translation**: Convert a virtual address to a physical address.
3. **Handle page faults**: If a page is not in memory, allocate a frame or swap out an old page.
4. **Simulate virtual memory accesses** and print results.

### **Python Solution**
```python
from collections import deque

# Constants
NUM_VIRTUAL_PAGES = 16   # Virtual memory has 16 pages
NUM_PHYSICAL_FRAMES = 4  # Only 4 physical frames available (simulating limited RAM)
PAGE_SIZE = 4096         # Each page is 4 KB

# Page Table (VPN -> PFN)
page_table = {}  # {Virtual Page Number -> Physical Frame Number}

# Physical Memory Representation
physical_memory = {}  # {Frame Number -> Virtual Page Number}

# Page Replacement Queue (FIFO Policy)
page_queue = deque()  # Stores the order of pages in RAM

def translate_address(virtual_address):
    """ Translates a virtual address to a physical address using paging. """
    vpn = virtual_address // PAGE_SIZE  # Get virtual page number
    offset = virtual_address % PAGE_SIZE  # Offset within the page

    if vpn in page_table:
        pfn = page_table[vpn]
        physical_address = (pfn * PAGE_SIZE) + offset
        print(f"Virtual Address {virtual_address} -> Physical Address {physical_address} (VPN {vpn} -> PFN {pfn})")
        return physical_address
    else:
        print(f"PAGE FAULT! Virtual Page {vpn} not in memory.")
        handle_page_fault(vpn)
        return translate_address(virtual_address)  # Retry after handling page fault

def handle_page_fault(vpn):
    """ Handles a page fault by loading a page into RAM, using FIFO replacement if full. """
    global page_table, physical_memory, page_queue

    # If there is space in RAM, allocate a frame
    if len(physical_memory) < NUM_PHYSICAL_FRAMES:
        pfn = len(physical_memory)  # Assign next free frame
    else:
        # RAM is full; Perform FIFO page replacement
        evicted_vpn = page_queue.popleft()  # Remove the oldest page
        pfn = page_table.pop(evicted_vpn)  # Free its frame
        del physical_memory[pfn]  # Remove from memory
        print(f"Swapping out Virtual Page {evicted_vpn} from Frame {pfn}.")

    # Load new page into the selected frame
    physical_memory[pfn] = vpn
    page_table[vpn] = pfn
    page_queue.append(vpn)
    print(f"Loaded Virtual Page {vpn} into Frame {pfn}.")

# Simulating memory accesses
virtual_addresses = [0, 8192, 16384, 4096, 20480, 0, 8192, 32768, 49152, 65536]

print("\nSimulating Virtual Memory Paging System:")
for vaddr in virtual_addresses:
    translate_address(vaddr)

# Print final memory state
print("\nFinal Page Table Mapping (VPN -> PFN):", page_table)
```

### **Comments on the Code**
1. **Memory Representation**
   - **Virtual memory** has **16 pages** but only **4 physical frames** (simulating real memory constraints).
   - A **page table** maps virtual pages (VPNs) to physical frames (PFNs).

2. **Address Translation**
   - Given a **virtual address**, the program extracts:
     - **VPN (Virtual Page Number)**: `virtual_address // PAGE_SIZE`
     - **Offset** within the page: `virtual_address % PAGE_SIZE`
   - If the **page is mapped**, it computes the **physical address**.
   - If not, a **page fault occurs**, and the missing page is **loaded into memory**.

3. **Page Fault Handling & FIFO Replacement**
   - If a **free frame is available**, it is assigned to the new page.
   - If RAM is **full**, it **evicts the oldest page (FIFO)** and loads the new one.

4. **Simulation of Virtual Memory Access**
   - The program **randomly accesses virtual addresses**.
   - It prints the **mapping of virtual to physical addresses**, highlighting **page faults and swaps**.

### **Expected Output**
```
Simulating Virtual Memory Paging System:

PAGE FAULT! Virtual Page 0 not in memory.
Loaded Virtual Page 0 into Frame 0.
Virtual Address 0 -> Physical Address 0 (VPN 0 -> PFN 0)

PAGE FAULT! Virtual Page 2 not in memory.
Loaded Virtual Page 2 into Frame 1.
Virtual Address 8192 -> Physical Address 8192 (VPN 2 -> PFN 1)

PAGE FAULT! Virtual Page 4 not in memory.
Loaded Virtual Page 4 into Frame 2.
Virtual Address 16384 -> Physical Address 16384 (VPN 4 -> PFN 2)

PAGE FAULT! Virtual Page 1 not in memory.
Loaded Virtual Page 1 into Frame 3.
Virtual Address 4096 -> Physical Address 4096 (VPN 1 -> PFN 3)

PAGE FAULT! Virtual Page 5 not in memory.
Swapping out Virtual Page 0 from Frame 0.
Loaded Virtual Page 5 into Frame 0.
Virtual Address 20480 -> Physical Address 0 (VPN 5 -> PFN 0)

Virtual Address 0 -> Physical Address 0 (VPN 0 -> PFN 0) [Reaccessed, now swapped out]

Virtual Address 8192 -> Physical Address 8192 (VPN 2 -> PFN 1)

PAGE FAULT! Virtual Page 8 not in memory.
Swapping out Virtual Page 2 from Frame 1.
Loaded Virtual Page 8 into Frame 1.
Virtual Address 32768 -> Physical Address 8192 (VPN 8 -> PFN 1)

PAGE FAULT! Virtual Page 12 not in memory.
Swapping out Virtual Page 4 from Frame 2.
Loaded Virtual Page 12 into Frame 2.
Virtual Address 49152 -> Physical Address 16384 (VPN 12 -> PFN 2)

PAGE FAULT! Virtual Page 16 not in memory.
Swapping out Virtual Page 1 from Frame 3.
Loaded Virtual Page 16 into Frame 3.
Virtual Address 65536 -> Physical Address 4096 (VPN 16 -> PFN 3)

Final Page Table Mapping (VPN -> PFN): {5: 0, 8: 1, 12: 2, 16: 3}
```

## **Questions**
1. **How does paging improve memory management?**
2. **Why does a page fault occur?**
3. **(Optional) Modify the code to implement the LRU page replacement strategy.**
4. **What would happen if the swap space is full in a real OS?**

## **Expected Learning Outcomes**
- **Understand paging concepts and virtual-to-physical address translation.**
- **Simulate page faults and page replacement policies.**
- **Experience real-world challenges of memory management.**
- **Analyze how different page replacement policies affect system performance.**
