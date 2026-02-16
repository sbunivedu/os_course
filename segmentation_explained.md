# How Does Segmentation Work

Machine code is **not generated with physical segment addresses embedded in it**.

Instead:

> The compiler generates code assuming a logical layout (code, data, stack), and the hardware segmentation mechanism translates virtual addresses at runtime using segment base and bounds registers set up by the OS.

# Step 1 — What the compiler does

When compiling:

```c
int x = 5;

int main() {
    return x;
}
```

The compiler:

* Generates instructions like:

  ```
  mov eax, [x]
  ```
* Uses **symbolic addresses** (relative to the program’s logical address space)

It does **not** know:

* Where the program will live in physical memory
* What the segment base will be

It assumes:

* The program starts at virtual address 0 (or some fixed logical base)


# Step 2 — What the linker does

The linker:

* Combines `.text`, `.data`, `.bss`
* Assigns **logical (virtual) offsets**

Example layout (logical):

```
0x0000  → code (.text)
0x2000  → data (.data)
0x3000  → heap
...
0xFFFF  → stack
```

Still:

* These are **virtual addresses**
* Not physical addresses

# Step 3 — What the OS does (segmentation setup)

When the program runs:

The OS sets:

* Code segment base register
* Data segment base register
* Stack segment base register

Example:

```
Process A
---------
Code base  = 0x800000
Data base  = 0x900000
Stack base = 0xA00000
```

# Step 4 — What happens at runtime (hardware translation)

Suppose the instruction references virtual address:

```
0x00001000
```

Hardware:

1. Determines which segment this address belongs to
2. Checks bounds
3. Computes physical address:

```
physical = segment_base + offset
```

Example:

```
physical = 0x800000 + 0x1000
         = 0x801000
```

The machine code itself never changes.


# Important Insight

Machine code contains:

* Logical addresses (offsets)
* Not physical addresses

Segmentation hardware makes this work by:

* Adding the base register value dynamically

# Why this works

This enables:

### 1. Relocation

The same binary can run:

* At physical address 0x100000
* Or 0x900000

No recompilation needed.

### 2. Protection

If offset > bounds:

* CPU raises exception
* Segmentation fault

# How does the CPU know which segment?

In simple segmentation models (like OSTEP Chapter 16):

The virtual address format may be:

```
[ segment bits | offset bits ]
```

Example:

* Top 2 bits select segment
* Remaining bits are offset

So hardware:

* Extracts segment ID
* Uses corresponding base/bounds

# Visual Summary

```
Compiler produces:
    mov eax, [0x1200]    (virtual offset)

Hardware at runtime:
    physical = base + 0x1200
```

# Key Concept

> The compiler generates code using virtual addresses relative to segments, and the hardware performs dynamic relocation at runtime using base and bounds registers set by the OS.

❌ “The compiler generates different machine code depending on where the program is loaded.”

✅ No — relocation is done by hardware using segment base registers.

# Deep Insight

Segmentation is essentially:

* **Hardware-supported relocation**
* Combined with **hardware-supported bounds checking**

It solves:

* Isolation
* Relocation
* Protection

But introduces:

* External fragmentation

