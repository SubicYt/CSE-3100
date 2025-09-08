#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main()
{
	int n;

	printf("n = ");
	scanf("%d", &n);

	int m = n;
	//TODO
	//add code below

    int total;

    while(m!=1 && m !=4){
        total = 0;
        while(m > 0){
            total += (m%10 * m%10);
            m /= 10;
        }
       m = total;
    }

	if(n==1) printf("%d is a happy number.\n", m);
	else printf("%d is NOT a happy number.\n", m);
	return 0;
}