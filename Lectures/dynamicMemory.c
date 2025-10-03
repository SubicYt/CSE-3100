//malloc keyword
#include <stdlib.h>
#include <stdio.h>

//malloc(10) -- returns 10 bytes of memory.
//calloc() -- initializes content to zero
//free() -- takes a pointer to the block to some free memory. 


//every malloc should have an associated free.
int main(){
    char* p = malloc(10); // request 10 bytes
    p = realloc(p, 20); // p may change. 

}