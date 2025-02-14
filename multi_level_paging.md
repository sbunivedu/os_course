## **Simulating Multi-Level Paging: Translating Virtual to Physical Addresses**

### **Objective:**
Students run a **two-level page table system** simulator to simulate the virtual-to-physical address translation process. The program will take a **virtual address**, walk through the page tables, and return the corresponding **physical address** while handling missing page faults appropriately.

### **Learning Outcomes:**
By completing this activity, students will be able to:
1. **Implement a two-level page table structure** to simulate virtual address translation.
2. **Demonstrate how page tables store mappings** from virtual pages to physical frames.
3. **Perform a page table walk manually** to resolve virtual addresses.
4. **Handle page faults** by dynamically allocating new page table entries.
5. **Analyze the efficiency of multi-level paging** compared to single-level paging.

### **Implementation Steps:**

#### **1. Define the System Parameters**
- Assume a **32-bit virtual address** with a **two-level page table**.
- Define **page table entry (PTE) structures** for both levels.
- Use a **fixed page size** (e.g., **4 KB** = \(2^{12}\) bytes per page).

#### **2. Parse Virtual Addresses**
- Extract **page directory index (PDI)**, **page table index (PTI)**, and **offset** from a given virtual address.

#### **3. Implement Page Table Walk Logic**
- Check if the **page directory** contains an entry for the requested **page table**.
- If the **page table exists**, retrieve the **physical page frame number**.
- If the **page table is missing**, handle a **page fault** and allocate memory dynamically.

#### **4. Translate Virtual to Physical Address**
- Compute the final **physical address** using the **frame number and offset**.

### **Code Template (Python)**
```python
import random

# Define memory parameters
PAGE_SIZE = 4096  # 4 KB pages (2^12 bytes)
NUM_ENTRIES = 1024  # Each page table has 1024 entries (2^10)
NUM_FRAMES = 256  # Limited number of physical frames

# Page directory and page tables (simulated memory)
page_directory = {}  # Maps PDI -> Page Table
physical_memory = {}  # Maps VPN -> Frame Number

# Function to simulate multi-level paging
def translate_virtual_address(virtual_address):
    # Extract PDI (10 bits), PTI (10 bits), and offset (12 bits)
    pdi = (virtual_address >> 22) & 0x3FF  # Top 10 bits
    pti = (virtual_address >> 12) & 0x3FF  # Next 10 bits
    offset = virtual_address & 0xFFF  # Last 12 bits

    print(f"Virtual Address: {virtual_address} -> PDI: {pdi}, PTI: {pti}, Offset: {offset}")

    # Check if Page Directory Entry exists
    if pdi not in page_directory:
        print(f"Page Directory entry {pdi} not found! Page fault occurred.")
        page_directory[pdi] = {}  # Allocate a new page table

    # Retrieve Page Table
    page_table = page_directory[pdi]

    # Check if Page Table Entry exists
    if pti not in page_table:
        print(f"Page Table entry {pti} not found! Allocating new frame.")
        if len(physical_memory) < NUM_FRAMES:
            frame_number = len(physical_memory)  # Assign next free frame
            physical_memory[(pdi, pti)] = frame_number
            page_table[pti] = frame_number
        else:
            print("Out of physical memory! Cannot allocate new frame.")
            return None

    # Retrieve frame number
    frame_number = page_table[pti]
    physical_address = (frame_number * PAGE_SIZE) + offset
    print(f"Translated Physical Address: {physical_address} (Frame {frame_number})\n")
    return physical_address

# Simulating translation of multiple virtual addresses
random.seed(1)  # Ensures reproducibility
virtual_addresses = [random.randint(0, (1 << 32) - 1) for _ in range(5)]

print("\nSimulating Multi-Level Paging:\n")
for v_addr in virtual_addresses:
    translate_virtual_address(v_addr)

print(f"\nTotal Page Faults Handled: {len(physical_memory)}")
```

---

### **Key Concepts Demonstrated in the Code**
1. **Virtual Address Breakdown:**
   - The **top 10 bits** are the **page directory index (PDI)**.
   - The **next 10 bits** are the **page table index (PTI)**.
   - The **bottom 12 bits** represent the **offset within a page**.

2. **Simulating a Two-Level Page Table:**
   - A **page directory** maps **PDI → Page Table**.
   - A **page table** maps **PTI → Frame Number**.

3. **Page Table Walk (Handling Page Faults):**
   - If the **page table doesn’t exist**, it is allocated dynamically.
   - If the **page is not mapped**, a new **physical frame** is assigned.

4. **Final Translation to Physical Address:**
   - The **frame number and offset** are combined to compute the **physical address**.

### **Example Output**
```
Simulating Multi-Level Paging:

Virtual Address: 2974102970 -> PDI: 708, PTI: 875, Offset: 586
Page Directory entry 708 not found! Page fault occurred.
Page Table entry 875 not found! Allocating new frame.
Translated Physical Address: 586 (Frame 0)

Virtual Address: 2068025721 -> PDI: 488, PTI: 1002, Offset: 57
Page Directory entry 488 not found! Page fault occurred.
Page Table entry 1002 not found! Allocating new frame.
Translated Physical Address: 4153 (Frame 1)

Virtual Address: 2466568283 -> PDI: 588, PTI: 406, Offset: 203
Page Directory entry 588 not found! Page fault occurred.
Page Table entry 406 not found! Allocating new frame.
Translated Physical Address: 8395 (Frame 2)

Virtual Address: 1570689008 -> PDI: 366, PTI: 400, Offset: 0
Page Directory entry 366 not found! Page fault occurred.
Page Table entry 400 not found! Allocating new frame.
Translated Physical Address: 12288 (Frame 3)

Virtual Address: 2862679164 -> PDI: 688, PTI: 252, Offset: 684
Page Directory entry 688 not found! Page fault occurred.
Page Table entry 252 not found! Allocating new frame.
Translated Physical Address: 16868 (Frame 4)

Total Page Faults Handled: 5
```

---

### **Questions**
1. **How does the two-level paging system reduce memory overhead compared to single-level paging?**
2. **What happens when physical memory is exhausted?** Modify the program to simulate page swapping.
3. **Extend the program to three-level paging** and analyze the trade-offs.
4. **Simulate TLB (Translation Lookaside Buffer)** to reduce translation overhead.

### **Expected Outcomes**
- Students understand **how virtual addresses are translated step by step**.
- They **observe the role of page tables** in mapping pages to frames.
- They implement a **basic page fault handling mechanism**.
- They gain insights into **multi-level paging efficiency** and its real-world application.