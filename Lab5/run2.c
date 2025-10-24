#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child;
    int exitStatus;
    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command

    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }
    
    child = fork();

    if(child <0){
        perror("fork() fail");
        exit(EXIT_FAILURE);
    }
    
    if(child == 0){
        execlp(argv[1], argv[1], argv[2], (char *) NULL);
        //this line is reached if execlp failts;
        perror("execlp failed, boohooo");
        exit(1);
    }
    else{
        waitpid(child, &exitStatus, 0);
        //correct usage?=
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
    }

    child = fork(); //the second child process for the rest of the command lines.
    
    if (child < 0){
        perror("fork failed for child 2");
    }

    if(child == 0){
        //second child process
        //run the rest of the cmd line
        execvp(argv[3], &argv[3]);
        exit(1);
    }
    else{
        waitpid(child, &exitStatus, 0);
        //correct usage?=
        printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
    }

    return 0;
}