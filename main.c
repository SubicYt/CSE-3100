#include <stdio.h>

int main(){

    printf("Hello world\n");
    int indexer = 0;
    int sum;
    while(indexer < 200){
        sum += indexer;
        indexer++;
    }

    printf("%d", sum);
    return 0;
}