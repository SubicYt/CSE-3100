
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

#define PIPEFD_READ 0
#define PIPEFD_WRITE 1
#define MSG_BUFFER_SIZE 1000

void write_to(int value, int fd){
    write(fd, &value, sizeof(int));
}

int main(){
   //setup communication between parent and child
   //requires 2 pipes.
   int fdp[2];
   int fdc[2];

   if(pipe(fdp) < 0){
    perror("pipe failed");
    exit(EXIT_FAILURE);
   }

   if(pipe(fdc) < 0){
    perror("pipe failed");
    exit(EXIT_FAILURE);
   }

   //okay garmin video schizen
   /*
   how we are going to do this
   child writes to fdp and parent reads from fdp
   parent writes to fdc and child reads from fdc.
   */
   int childpid = fork();
   if(childpid < 0){
    perror("fork");
    exit(EXIT_FAILURE);
   }

   if(childpid == 0){
    int childValue;
    close(fdp[PIPEFD_READ]); //writing to fdp only
    close(fdc[PIPEFD_WRITE]);//reading from fdc only
    write_to(5, fdp[PIPEFD_WRITE]);
    read(fdc[PIPEFD_READ], &childValue, sizeof(int));
    printf("This is the parent value written to child (shoudl be 33) %d\n", childValue);
   }
   else{
    int parent_value;
    close(fdp[PIPEFD_WRITE]);
    close(fdc[PIPEFD_READ]);
    read(fdp[PIPEFD_READ], &parent_value, sizeof(int));
    printf("This is the child value written to parent (should be 5) %d\n", parent_value);
    write_to(33, fdc[PIPEFD_WRITE]);
   }
}