#include<stdio.h>
#include<stdlib.h>

void counter() {
    static int c = 0;
    c++;
    printf("%d ", c);
}

int foo(int a, int b){
    return a + b;
}
int main(){

    int x = 2;

    char a[] = "abc";
    char s[] = "abc";
    if(&a == &s){
        printf("is equal");
    }else{
        printf("nah");
    }

    counter();
    counter();
    counter();

    int *p = calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++)
    printf("%d ", p[i]);
        free(p);
    return 0;

    return 0;
}