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

void write_to(char message[], int pd){
    write(pd, message, MSG_BUFFER_SIZE);
}

int main(){
    //setup the pipes

    int fdp[2];
    int fdc[2];
    if(pipe(fdp) < 0){
        //something wrong
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    if(pipe(fdc) < 0){
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    int childpid = fork();

    if(childpid < 0){
        //fork failed;
        perror("fork fails");
        exit(EXIT_FAILURE);
    }
    /*
    Child writes to fdp and parent reads from fdp
    Child reads from fdc, and parent writes to fdc.
    */
    if(childpid == 0){
        /*
        we know that we are in the child process
        */
        close(fdp[PIPEFD_READ]);
        close(fdc[PIPEFD_WRITE]);
        char Recieve_Message[MSG_BUFFER_SIZE];
        char Send_Message[MSG_BUFFER_SIZE];

        //instead of std out this writes to the file.
        dup2(fdp[PIPEFD_WRITE], STDOUT_FILENO);

        int ethansFile = open("ethan.txt", O_RDWR | O_CREAT, 0644);
        read(ethansFile, Send_Message, MSG_BUFFER_SIZE);
         write_to(Send_Message, fdp[PIPEFD_WRITE]);
        read(fdc[PIPEFD_READ], Recieve_Message, MSG_BUFFER_SIZE);
        
        printf("%s\n", Recieve_Message);

        close(fdc[PIPEFD_READ]);
        close(fdp[PIPEFD_WRITE]);
    }
    else{

        close(fdc[PIPEFD_READ]);
        close(fdp[PIPEFD_WRITE]);

        char rec_message[MSG_BUFFER_SIZE];
        char snd_message[MSG_BUFFER_SIZE];

        int eduardosFile = open("eduardo.txt", O_RDWR | O_CREAT, 0644);

        read(eduardosFile, snd_message, MSG_BUFFER_SIZE);
        write_to(snd_message, fdc[PIPEFD_WRITE]);
        read(fdp[PIPEFD_READ], rec_message, MSG_BUFFER_SIZE);

        printf("%s\n", rec_message);

        close(fdp[PIPEFD_READ]);
        close(fdc[PIPEFD_WRITE]);
    }   
}
//read()
