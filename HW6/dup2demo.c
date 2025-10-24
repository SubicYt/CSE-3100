#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

int main(){
    printf("before dup2\n");
    printf("Can you see this on the screen?\n");
    printf("hey there...\n");
    
    int fd = open("demo.txt", O_WRONLY);

    if(fd < 0){
        perror("couldnt get file desc");
        return -1;
    }
    
    printf("before dup2 happens");
    fflush(stdout);
    dup2(fd, 1); //fd is replacing the output to stdout (1)
    close(fd);
    printf("can you this this on the screen?\n");
    return 0;
}
