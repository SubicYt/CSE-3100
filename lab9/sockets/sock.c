#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>

  //a socket descriptor is just an int, kind of like a file descripto

int main(argc, argv[]){
    int status;
    struct addrinfo hints; //
    struct addrinfo *servinfo; //will point to the results. 
    
    
}