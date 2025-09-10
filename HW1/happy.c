#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main()
{

    /*
    Replace the number by the sum of the squares of its digits, 
    and repeat the process until the number either equals 1
    (where it will stay), or it loops endlessly in a cycle which does not include 1

    It can be shown that if a number is an unhappy number, 
    it will reach 4 in the above process. This can be
    used to check whether a number is an unhappy number.
        */
    
	int n;
    //user input number
	printf("n = ");
	scanf("%d", &n);

    //number we do operations with
    //passing n to m as value, not reference
	int m = n;
    //sum of squares.
    int total;

    while(m != 1 && m != 4){
        total = 0;
        int temp = m;
        while(temp > 0){
            int digit_to_square = temp % 10;
            total += digit_to_square * digit_to_square;
            temp /= 10;
        }
       m = total; //update m to be the sum of squares
    }

	if(m==1) printf("%d is a happy number.\n", n);
	else printf("%d is NOT a happy number.\n", n);
	return 0;
}
