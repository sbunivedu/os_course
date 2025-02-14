Q1: Use pwd to print the current directory. Use history to see recently used commands or press the Up arrow key to cycle through them.
Q2: The program will fail to compile because the printf function is undefined.
Q3: The -o flag names the output file (e.g., gcc hello.c -o hello). Without it, the compiler produces a default a.out executable.
Q4: atoi() converts strings to integers, but it lacks error handling. A better alternative is strtol, which detects invalid inputs.
Q5: Memory leaks occur, gradually consuming memory and potentially leading to program failure.
Q6: Check if malloc returns NULL and print an error message before exiting
Q7: fopen() returns NULL, indicating an issue (e.g., missing file, permissions). Always check the return value before proceeding.
Q8: The execution order varies because process scheduling by the OS is unpredictable.
Q9: fork() returns 0 for the child process and the child's PID for the parent. This helps differentiate between parent and child behavior.
Q10: pthread_join() ensures the main thread waits for others to finish. Without it, the main thread may exit before child threads complete.