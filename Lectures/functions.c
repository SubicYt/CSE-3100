#include <stdio.h>

int add(int x, int y){
    return x + y;
}

int main(){
    int x = add(6,6);
    printf("%d", x);
    
    int foo();
    printf("%d", foo());
}

int foo(){
    return 4;
}