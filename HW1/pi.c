#include <stdio.h>
#include <stdlib.h>
//Approximate the value of pi.

double power(int base, int exp){
	double result = 1.0;
	for(int i = 0; i < exp; i++){
		result *= base;
	}
	return result;
}

int main()
{
	int n, i;

	printf("n = ");
	scanf("%d", &n);

	double pi = 0.;
	//TODO
	//add code below 

    for(i = 0; i<n; i++){
        double var1 = 4.0 / (8.0*i + 1.0);
        double var2 = 2.0 / (8.0*i + 4.0);
        double var3 = 1.0 / (8.0*i + 5.0);
        double var4 = 1.0 / (8.0*i + 6.0);
        pi += (var1 - var2 - var3 - var4) / power(16, i);
    }

	printf("PI = %.10f\n", pi);
	return 0;
}