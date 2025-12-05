#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
/*
Mutexes and semaphores allow us to lock access to critical sections, but they do not differentiate between reading and writing.

This can be important since we can read data from multiple threads at the same time, but can’t write at the same time as a read or write.

If we protect a piece of data with a mutex, it will not allow multiple reads in parallel.
*/
int count = 0;
#define MAX 200

void* counter(){
    for(int i = 0; i < MAX; i++){
        count++;
    }
    printf("count is %d\n", count);
}

int main(int argc, char * argv[]){
    pthread_t th[2];
    for(int i = 0; i < 2; i++){
        if(pthread_create(&th[i], NULL, &counter, NULL) != 0){
            return 1;
        }
    }

    for(int i =0; i < 2; i++){
        if(pthread_join(th[i], NULL) !=0){
            return 1;
        }
    }
    return 0;
}