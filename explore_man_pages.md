These activities helping you get familiar with the `man` pages. Please follow the instructions and
answer the questions.

Please watch this tutorial [Mastering Linux Man Pages - A Definitive Guide](https://youtu.be/RzAkjX_9B7E?si=O857Mw03UIgHC67P), which offers a comprehensive overview of the man pages.

## **Activity 1: Exploring the `man` Pages**
### **Objective:**
Get familiar with the `man` command for looking up Linux commands, system calls, and library functions.

### **Instructions:**
1. Open a terminal.
2. Run the following command to see the manual page for the `ls` command:
   ```sh
   man ls
   ```
3. Navigate through the manual using:
   - **Arrow keys** (Up/Down) to scroll.
   - **Spacebar** to go down a page.
   - **q** to exit.

4. Now, look up the `fork()` system call:
   ```sh
   man 2 fork
   ```
5. Look up the `printf()` function:
   ```sh
   man 3 printf
   ```
6. Explain the **sections of the `man` pages**:
   - **Section 1**: User commands (e.g., `ls`, `cat`)
   - **Section 2**: System calls (e.g., `fork()`, `execve()`)
   - **Section 3**: Library functions (e.g., `printf()`, `malloc()`)

### **Exercise:**
- Please look up the **`open()` system call** and answer:
  - What header file is required?
  - What are the possible flags for opening a file?

  ```sh
  man 2 open
  ```

---

## **Activity 2: Using `apropos` to Find Commands**
### **Objective:**
Learn how to find relevant commands or functions when they don't know the exact name.

### **Instructions:**
1. Run:
   ```sh
   apropos process
   ```
   - This will list all commands, system calls, and functions related to **process management**.

2. Now try:
   ```sh
   apropos memory
   ```
   - Find a function related to **memory allocation**.

3. Reflections:
   - What function is used for allocating dynamic memory?
   - Find its manual page and check the return type.

   ```sh
   man 3 malloc
   ```

---

## **Activity 3: Understanding System Calls with `strace`**
### **Objective:**
Observe system calls used by a running process.

### **Instructions:**
1. Run a simple `ls` command with `strace`:
   ```sh
   strace ls
   ```
2. Notice the system calls (`open()`, `read()`, `write()`) made by `ls`.

3. Redirect output to a file:
   ```sh
   strace -o trace_output.txt ls
   cat trace_output.txt
   ```

4. Reflections:
   - How does `ls` read directory contents?
   - Find the **system call** responsible for listing files.

5. Try running `strace` on another command:
   ```sh
   strace cat /etc/passwd
   ```

---

## **Activity 4: Exploring Library Functions with `ldd`**
### **Objective:**
Understand which shared libraries a program depends on.

### **Instructions:**
1. Run:
   ```sh
   ldd /bin/ls
   ```
   - This shows the shared libraries `ls` is linked to.

2. Reflections:
   - What library provides `printf()`?
   - Find its path using:
     ```sh
     ldd /usr/bin/echo | grep libc
     ```

---

## **Activity 5: Exploring `getconf` for System Limits**
### **Objective:**
Find system limits related to files, processes, and memory.

### **Instructions:**
1. Run:
   ```sh
   getconf ARG_MAX
   ```
   - This gives the **maximum length of arguments** for a process.

2. Find the **maximum number of open files**:
   ```sh
   getconf OPEN_MAX
   ```

3. Reflections:
   - What is the page size of memory in the system?
     ```sh
     getconf PAGE_SIZE
     ```

---

## **Activity 6: Using `proc` Filesystem for System Information**
### **Objective:**
Learn how to check process information using `/proc`.

### **Instructions:**
1. Find the process ID of the current shell:
   ```sh
   echo $$
   ```

2. Check process details:
   ```sh
   cat /proc/$$/status
   ```

3. Find the number of CPUs:
   ```sh
   cat /proc/cpuinfo | grep "processor"
   ```

4. Reflections:
   - What is the total memory in your system?
     ```sh
     cat /proc/meminfo | grep MemTotal
     ```

---

## **Activity 7: Debugging with `gdb`**
### **Objective:**
Learn to debug using `gdb`.

### **Instructions:**
1. Write a simple buggy program (`buggy.c`):
   ```c
   #include <stdio.h>

   int main() {
       int *ptr = NULL;
       *ptr = 42;  // This will cause a segmentation fault
       return 0;
   }
   ```
2. Compile with debugging symbols:
   ```sh
   gcc -g buggy.c -o buggy
   ```

3. Run under `gdb`:
   ```sh
   gdb ./buggy
   ```
   - Inside `gdb`, type:
     ```
     run
     bt  (to get the backtrace)
     ```

4. Reflections:
   - What caused the segmentation fault?
   - How can you fix it?

---

## **Final Reflection and Discussion**
- What are three useful ways to find information about Linux commands?
- How can you debug a program that crashes due to a segmentation fault?
- What tools will you use when you encounter an unknown error in a system call?