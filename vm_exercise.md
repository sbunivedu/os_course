The exercises allow students to explore the memory API in C, starting with basic concepts and leading to an understanding of virtual address space.

---

# **Memory Virtualization Exploration Exercises**
**Objective:**
These exercises will introduce you to dynamic memory allocation using `malloc`, `free`, and related functions in C. You will also explore how memory is structured in a process's virtual address space.

**Prerequisites:**
- Basic understanding of C programming (variables, functions, pointers)
- Access to a Linux machine with `gcc` installed
- Ability to use `man` pages (`man malloc`, `man free`)

---

## **Exercise 1: Warm-up – Understanding `malloc` and `free`**
### **Task 1: Allocating and Freeing Memory**
1. Write a C program that:
   - Allocates memory for an integer using `malloc`
   - Stores a value in the allocated memory
   - Prints the value and the address of the allocated memory
   - Frees the allocated memory

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int)); // Allocate memory for an integer
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    *ptr = 42; // Store a value
    printf("Value: %d, Address: %p\n", *ptr, (void *)ptr);

    free(ptr); // Free allocated memory
    return 0;
}
```
### **Questions:**
- What is a simpler way to store an `int` value? (`int myint`)
- What happens if you don’t call `free(ptr);`?
- Try running `valgrind` (if installed) to check for memory leaks:
  ```
  valgrind --leak-check=full ./a.out
  ```
- Use `man malloc` and `man free` to understand these functions.

---

## **Exercise 2: Allocating Arrays and Exploring Memory Addresses**
### **Task 2: Allocating an Array**
1. Modify the previous program to allocate an array of 5 integers using `malloc`.
2. Assign values to the array and print their addresses.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(5 * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
        printf("arr[%d] = %d, Address: %p\n", i, arr[i], (void *)&arr[i]);
    }

    free(arr);
    return 0;
}
```
### **Questions:**
- Are the addresses printed contiguous?
- What happens if you access an index beyond the allocated size?
- Try using `calloc` instead of `malloc`. What differences do you observe?
  **Hint:** `man calloc`

---

## **Exercise 3: Exploring Virtual Address Space**
### **Task 3: Comparing Stack and Heap Addresses**
1. Modify the program to also declare a local (stack) variable and compare its address with a dynamically allocated (heap) variable.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int stack_var = 100; // Stack variable
    int *heap_var = (int *)malloc(sizeof(int)); // Heap variable

    if (heap_var == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    *heap_var = 200;
    printf("Stack variable: Address = %p, Value = %d\n", (void *)&stack_var, stack_var);
    printf("Heap variable: Address = %p, Value = %d\n", (void *)heap_var, *heap_var);

    free(heap_var);
    return 0;
}
```
### **Questions:**
- Are the addresses of the stack and heap variables close to each other?
- Run the program multiple times. Do the heap addresses change? Why?
- Use `man sbrk` to learn how memory is allocated for heap.

---

## **Exercise 4: Observing Memory Segmentation**
### **Task 4: Using `brk` and `sbrk`**
1. Write a program that prints the current program break (`brk` value), then allocates memory using `malloc`, and prints the `brk` value again.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    void *initial_brk = sbrk(0); // Get current program break
    printf("Initial brk: %p\n", initial_brk);

    int *ptr = (int *)malloc(1000 * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    void *after_malloc_brk = sbrk(0);
    printf("After malloc brk: %p\n", after_malloc_brk);

    free(ptr);

    return 0;
}
```
### **Questions:**
- How does the `brk` value change after `malloc`?
- What happens if you allocate a large amount of memory?

---

## **Exercise 5: Demonstrating Virtual Address Space with `getpid` and `pmap`**
### **Task 5: Printing Process Memory Layout**
1. Modify the program to print its own process ID (`PID`).
2. Use `pmap` to inspect its memory layout.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Process ID: %d\n", getpid());
    getchar(); // Pause the program to inspect memory
    return 0;
}
```
### **Steps:**
1. Compile and run the program:
   ```
   gcc -o mem_layout mem_layout.c
   ./mem_layout
   ```
2. Open another terminal and run:
   ```
   pmap $(pgrep mem_layout)
   ```
3. Observe the memory segments (`heap`, `stack`, `text`, `data`).

### **Questions:**
- Which segment contains dynamically allocated memory?
- Does the heap start at the same address every time?

---

# **Conclusion**
These exercises introduce students to fundamental memory management concepts in operating systems. By experimenting with `malloc`, `free`, `sbrk`, and process memory layout tools like `pmap`, students will gain an intuitive understanding of virtual memory and how user-space programs interact with the OS.

Here are additional exercises on **memory leaks** and **mmap**, building on the previous activities. These exercises will help students understand **memory management pitfalls** and **advanced memory mapping techniques**.

# **Additional Exercises: Detecting Memory Leaks & Exploring `mmap`**
## **Exercise 6: Detecting Memory Leaks with `valgrind`**
### **Task 6: Introducing a Memory Leak**
1. Write a program that intentionally forgets to free allocated memory.
2. Use `valgrind` to detect the leak.

```c
#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    int *ptr = (int *)malloc(10 * sizeof(int)); // Memory allocated but not freed
    for (int i = 0; i < 10; i++) {
        ptr[i] = i * 2;
    }
    printf("Memory allocated but not freed.\n");
}

int main() {
    allocate_memory();
    return 0;
}
```
### **Steps:**
1. Compile and run:
   ```
   gcc -g -o mem_leak mem_leak.c
   ./mem_leak
   ```
2. Use `valgrind` to check for leaks:
   ```
   valgrind --leak-check=full ./mem_leak
   ```

### **Questions:**
- What does `valgrind` report?
- Modify the program to free the memory. Does `valgrind` still detect a leak?

---

## **Exercise 7: Dangling Pointers & Use-After-Free**
### **Task 7: Understanding Dangling Pointers**
1. Modify the previous program to **free** memory, but still **use** it afterward.
2. Observe what happens.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    *ptr = 42;
    printf("Before free: %d\n", *ptr);

    free(ptr);
    // Uncommenting this line may cause unpredictable behavior!
    // printf("After free: %d\n", *ptr);

    return 0;
}
```

### **Questions:**
- What happens when you try to access `*ptr` after `free(ptr);`?
- Use `valgrind` to detect **use-after-free** issues.

---

## **Exercise 8: Memory Mapping with `mmap`**
### **Task 8: Allocating Memory with `mmap`**
Instead of using `malloc`, use `mmap` to allocate memory and compare behaviors.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    size_t size = 4096; // Allocate 4KB (one page)

    void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    int *arr = (int *)mem;
    arr[0] = 100; // Store a value
    printf("Value stored using mmap: %d, Address: %p\n", arr[0], arr);

    munmap(mem, size); // Free memory

    return 0;
}
```

### **Questions:**
- How is `mmap` different from `malloc`?
- What happens if you try to access `arr[0]` after calling `munmap(mem, size);`?
- Use `pmap $(pgrep mmap_test)` to inspect memory while the program is running.

---

## **Exercise 9: Shared Memory with `mmap`**
### **Task 9: Using `mmap` for Inter-Process Communication**
1. Create a file-backed shared memory region.
2. Map it in two different processes.
3. Write to memory in one process and read in another.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SHARED_MEM_FILE "/tmp/mmap_test"

int main() {
    int fd = open(SHARED_MEM_FILE, O_RDWR | O_CREAT, 0666);
    ftruncate(fd, 4096); // Set size of shared memory

    void *mem = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    strcpy((char *)mem, "Hello from process 1");
    printf("Message written: %s\n", (char *)mem);

    munmap(mem, 4096);
    close(fd);

    return 0;
}
```

**Now, open a second terminal and run this program to read the shared memory:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SHARED_MEM_FILE "/tmp/mmap_test"

int main() {
    int fd = open(SHARED_MEM_FILE, O_RDONLY);
    void *mem = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    printf("Message read: %s\n", (char *)mem);

    munmap(mem, 4096);
    close(fd);

    return 0;
}
```

### **Questions:**
- What happens when one process writes to memory?
- Can you use `mmap` as an alternative to traditional inter-process communication methods?

---

# **Conclusion**
These exercises introduce students to **memory leaks**, **use-after-free issues**, and **advanced memory allocation with `mmap`**. They will gain hands-on experience in **detecting memory issues** and **managing memory efficiently**.
