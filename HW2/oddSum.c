#include <stdio.h>
#include <stdlib.h>

int oddSumHelp(int count, int bound, int value)
{
	//NOTE TO SELF:

	//count is how many odd numbers we need to use to sum.
	//bound is the max odd number we can use
	//value is the target sum we need to reach. 
	//if any of these cases fail, return 0.

	//base case
    if (count == 0 && value == 0) {
        return 1;
    }
    if (count == 0 || value <= 0 || bound <= 0) {
        return 0;
    }

    if (bound <= value) {
        if (oddSumHelp(count - 1, bound - 2, value - bound)) {
            printf("%d ", bound);
            return 1;
        }
    }
	if(oddSumHelp(count, bound - 2, value)) {
		return 1;
	}


    return 0; // no solution
}

void oddSum(int count, int bound, int value)
{
    if(value <= 0 || count <= 0 || bound <= 0) return;
    
    if(bound % 2 == 0) bound -= 1;

    if(!oddSumHelp(count, bound, value)) printf("No solutions.\n");
	else printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc != 4) return -1;

	int count = atoi(argv[1]);
	int bound = atoi(argv[2]);
	int value = atoi(argv[3]);

	//oddSum(12,30,200);
	//oddSum(10,20,100);
	//oddSum(20,20,200);
	oddSum(count, bound, value);
	return 0;
}