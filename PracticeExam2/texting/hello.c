#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

#define PIPEFD_READ 0
#define PIPEFD_WRITE 1
#define MSG_BUFFER_SIZE 1000

/*
the point of this is to create communication across two programs.
create communication across two files...
*/

void write_to(char message[], int fd){
    write(fd, message, MSG_BUFFER_SIZE);
}

int main(){
    int fdp[2];
    int fdc[2];
    if(pipe(fdp) < 0){
        perror("pipe is wrong");
        exit(EXIT_FAILURE);
    }
    if(pipe(fdc) < 0){
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    int childpid = fork();
    if(childpid < 0){
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if(childpid == 0){
        //child writes to fdp, parent reads from fdp
        //parent writes to fdc, child reads from fdc.
        char sendMessage[MSG_BUFFER_SIZE];
        char recieveMessage[MSG_BUFFER_SIZE];

        close(fdp[PIPEFD_READ]); //child doesnt read from this
        close(fdc[PIPEFD_WRITE]); //child doesnt write to this
        int Ethfile = open("ethansText.txt", O_RDWR | O_CREAT, 0644);
        //the file is open for reading
        //i think open returns a file discriptor, i might be tweakin idk
        read(Ethfile, sendMessage, MSG_BUFFER_SIZE);

        write_to(sendMessage, fdp[PIPEFD_WRITE]);

        read(fdc[PIPEFD_READ], &recieveMessage, MSG_BUFFER_SIZE);
        printf("Eduardo Says: %s\n", recieveMessage);
        exit(1);
    }
    //now in parent
    close(fdp[PIPEFD_WRITE]);
    close(fdc[PIPEFD_READ]);
    
    char send[MSG_BUFFER_SIZE];
    char rec[MSG_BUFFER_SIZE];

    read(fdp[PIPEFD_READ], rec, MSG_BUFFER_SIZE);
    printf("Ethan Says: %s\n", rec);

    int eduFile = open("eduardosText.txt", O_RDWR | O_CREAT, 0644);

    read(eduFile, &send, MSG_BUFFER_SIZE);
    write_to(send, fdc[PIPEFD_WRITE]);
}