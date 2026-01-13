#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
  int fd = open("test", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  int rc = fork();
  int result = 0;
  if (rc < 0) {
    // fork failed; exit
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    // child (new process)
    for(int i=0; i<10; i++){
      result = write(fd, "C", 1);
    }
    // the next two lines demonstrate that the child process
    // can close its file descriptor without affecting
    // the parent process that has a copy of the descriptor;
    // closing a file descriptor doesn't necessarily close the
    // corresponding file (description).
    fsync(fd);
    close(fd);
  } else {
    // parent goes down this path (original process)
    for(int i=0; i<10; i++){
      result = write(fd, "P", 1);
    }
    int child_status;
    waitpid (rc, &child_status, 0);
    result = write(fd, "\n", 1);
  }
  fsync(fd);
  close(fd);
  return 0;
}
