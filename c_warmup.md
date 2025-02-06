These activities provide a progressive warm-up, helping you get comfortable with **C programming and UNIX tools**.

## **Activity 1: Setting Up the Environment**
### **Step 1: Open a Terminal**

### **Step 2: Navigate the File System**
- `ls` → List files in a directory.
- `cd <directory>` → Change directory.
- `pwd` → Print current working directory.

### **Step 3: Create a Project Folder**
```sh
mkdir os-labs
cd os-labs
```

## **Activity 2: Writing and Compiling a Simple C Program**
### **Step 1: Write a Basic "Hello, World!" Program**
Create a new file with your favoriate editor (vim, nano, or emacs):
```sh
vim hello.c
```
Add this code:
```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc hello.c -o hello
./hello
```

---

## **Activity 3: Using `printf` and `scanf`**
### **Step 1: Write the Code**
Create a file `input.c`:
```c
#include <stdio.h>

int main() {
    int num1, num2, sum;

    printf("Enter two integers: ");
    scanf("%d %d", &num1, &num2);

    sum = num1 + num2;

    printf("Sum: %d\n", sum);

    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc input.c -o input
./input
```
**Expected Output:**
```
Enter two integers: 5 10
Sum: 15
```

---

## **Activity 4: Command-Line Arguments**
### **Step 1: Write the Code**
Create `args.c`:
```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Sum: %d\n", num1 + num2);
    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc args.c -o args
./args 5 10
```
**Expected Output:**
```
Sum: 15
```

---

## **Activity 5: Memory Management with `malloc`**
### **Step 1: Write the Code**
Create `memory.c`:
```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, *arr;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    arr = (int*) malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
        printf("%d ", arr[i]);
    }

    free(arr);
    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc memory.c -o memory
./memory
```

---

## **Activity 6: File I/O in C**
### **Step 1: Write a Program to Read/Write a File**
Create `fileio.c`:
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "This is a test.\n");
    fclose(file);

    file = fopen("output.txt", "r");
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc fileio.c -o fileio
./fileio
cat output.txt
```

---

## **Activity 7: Process Creation with `fork()`**
### **Step 1: Write the Code**
Create `fork.c`:
```c
#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        printf("Child Process (PID: %d)\n", getpid());
    } else {
        printf("Parent Process (PID: %d, Child: %d)\n", getpid(), pid);
    }

    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc fork.c -o fork
./fork
```

---

## **Activity 8: Multi-threading with `pthread`**
### **Step 1: Write the Code**
Create `threads.c`:
```c
#include <stdio.h>
#include <pthread.h>

void *print_message(void *arg) {
    printf("Thread %d: Hello from a thread!\n", *(int*)arg);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int ids[2] = {1, 2};

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, print_message, &ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
```
### **Step 2: Compile and Run**
```sh
gcc -pthread threads.c -o threads
./threads
```

## **Reflections**
- Question 1: What are some ways to check your current directory and recently used commands?
- Quesiton 2: What happens if you forget to include `#include <stdio.h>` in your program?
- Question 3: What does the `-o` flag do in the `gcc` command? What happens if you omit it?
- Questions 4: Why do we use `atoi()` to convert arguments to integers? What issues might arise from using it?
- Questions 5: What would happen if you forgot to call free() after using malloc()?
- Questions 6: How would you modify the program to handle a situation where memory allocation fails?
- Question 7: What happens if `fopen()` fails? How can you handle such errors?
- Question 8: How does the output of the `fork.c` program change between different runs?
- Quesiton 9: Why do we check if `fork()` returns `0` to determine if we are in the child process?
- Question 10: Why do we use `pthread_join()` after creating threads? What would happen if we didn’t?

