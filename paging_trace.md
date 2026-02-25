## Paging
Please answer the concept questions and perform the numerical trace of address translations.

Consider a system with:
* 64-byte virtual address space
* 16-byte page size

1. How many virtual pages are there? How many bits are used for the virtual page number (VPN)? How many bits are used for the offset?
2. Given a virtual address of 45, determine the VPN and offset.

### Page Table Mechanics
1. What is the purpose of a page table in a paging system?
2. What information is typically stored in a page table entry (PTE)?
> A page table entry typically contains the physical frame number along with status and protection bits such as valid, read/write permissions, and possibly dirty and reference bits.
3. Why must the page table be stored in physical memory?

### Numerical trace

Use the chapter’s tiny system: 64-byte VA space, 16-byte pages, and the example page table:

* VP0→PF3, VP1→PF7, VP2→PF5, VP3→PF2
* Page size 16 ⇒ offset = 4 bits; VA size 64 ⇒ VA = 6 bits; thus VPN = top 2 bits.

#### Trace 1
VA = 21 (decimal). Find VPN, offset, PFN, and final physical address (decimal).

Example answer:

21 in binary (6 bits) = 010101

VPN = 01 (=1), offset = 0101 (=5)

VP1→PF7

Physical address = PF716 + 5 = 716 + 5 = 112 + 5 = 117

#### Trace 2

VA = 0.

Example Answer: VPN=0, offset=0; VP0→PF3 ⇒ PA=3*16+0=48.

#### Trace 3

VA = 15.

#### Trace 4

VA = 16.

#### Trace 5

VA = 63.
