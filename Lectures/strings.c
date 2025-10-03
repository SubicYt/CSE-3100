#include <stdio.h>

int main(){
    char s[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
    char c[6] = "hello";
    printf("%s\n", s);
    printf("%s", c);
}