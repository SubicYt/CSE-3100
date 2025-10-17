#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int pd[2];
  
  if (pipe(pd) == -1) {
    perror("Error.");
    return -1;
  }

  pid_t pid = fork();
  if (pid == 0) {
    dup2(pd[1], 1);
    close(pd[1]);
    close(pd[0]);
    char *argv_list[] = {"cat", "pipe2.c", NULL};
    execvp("cat", argv_list);
  }

  close(pd[1]);

  pid_t pid1 = fork();
  if (pid1 == 0) {
    close(pd[1]);
    dup2(pd[0], 0);
    close(pd[0]);
    char *argv_list[] = {"tr", "[a-z]", "[A-Z]", NULL};
    execvp("tr", argv_list);
  }

  close(pd[1]);
  close(pd[0]);

  waitpid(pid, NULL, 0);
  waitpid(pid1, NULL, 0);
  return 0;
}