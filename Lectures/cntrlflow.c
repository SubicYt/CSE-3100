#include <stdio.h>
#include <stdbool.h>

bool checkEven(int a){
        if (a%2 == 0){
            return true;
        }
        else{
            return false;
        }
    }

int main(){
    //standard comparison operators used 
    //standard logical operators used
    int a = 4;
    bool check = checkEven(a);
    printf(check);

}