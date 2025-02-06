Check out the simple Linux tool `free` by typing `man free` and read its entire manual page.

1. Now, run `free`, perhaps using some of the arguments that might be useful (e.g., `-m`, to display memory totals in megabytes). How much memory is in your system? How much is free? Do these numbers match your intuition?
2. Next, study the `memory_user.c` program, which take two command-line arguments - the first one is the number of megabytes of memory it will use and the second is how long it will run in seconds. When run, it should allocate an array, and constantly stream through the array, touching each entry till the timer is up.
3. Now, while running your `memory_user` program, also (in a different terminal window, but on the same machine) run the `free` tool. How do the memory usage totals change when your program is running? How about when you kill the `memory_user` program? Do the numbers match your expectations? Try this for different amounts of memory usage. What happens when you use really large amounts of memory?
4. Study the `pmap` tool by studying its manual page.
6. To use `pmap`, you have to know the `processID` of the process you’re interested in. Thus, first run `ps -auxw` to see a list of all processes; then, pick an interesting one, such as a your `memory_user` program (indeed, you can even have that your program call `getpid()` and print out its `PID` for your convenience).Run `pmap` on your process using various flags (like `-X`) to reveal many details about the process. What do you see? How many different entities make up a modern address space, as opposed to our simple conception of `code/stack/heap`?
7. Finally, let’s run `pmap` on your `memory_user` program, with different amounts of used memory. What do you see here? Does the output from pmap match your expectations?

Hint: If you see too many processes listed when you run `ps -auxw`, you can `pipe` the output to the `grep` program to find the lines that contain your userid.

```c
// memory_user.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "unistd.h"

int main(int argc, char *argv[]) {
// argv[1]: memory size in megabytes
// argv[2]: runtime in seconds
  if (argc != 3) {
    exit(EXIT_FAILURE);
  }

  struct timeval tv_begin, now;

  int memory = atoi(argv[1]) * 1024 * 1024;
  int runtime = atoi(argv[2]);

  int length = memory / 4;
  int *arr = malloc(4 * length);
  assert(arr != NULL);
  printf("pid: %d\n", getpid());
  gettimeofday(&tv_begin, NULL);
  while (1) {
    gettimeofday(&now, NULL);
    if (now.tv_sec - tv_begin.tv_sec >= runtime) {
      break;
    }
    for (int i = 0; i < length; i++) {
      arr[i] = i;
    }
  }
  free(arr);
  return 0;
}
```