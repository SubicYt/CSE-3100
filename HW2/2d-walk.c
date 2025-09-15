#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n)
{

	//Fill in code below
	//When deciding which way to go for the next step, generate a random number as follows.
	//r = rand() % 4;
	//Treat r = 0, 1, 2, 3 as up, right, down and left respectively.

	//The random walk should stop once the x coordinate or y coordinate reaches $-n$ or $n$. 
	//The function should return the fraction of the visited $(x, y)$ coordinates inside (not including) the square.


    //cells go from -n to n inclusive 

    int x = 0;
    int y = 0;
    int visited[2*100+1][2*100+1] = {0}; 
    int total_visited = 0;

    //start walk from (0,0) which counts as visited
    visited[x+n][y+n] = 1;
    total_visited++;

    //make sure we are within (-n,-n) (n,n))
    while(x > -n && x < n && y > -n && y < n){
        //generate random number for direction
        int r = rand() % 4;
        if(r==0){
            y++; //up
        }
        else if (r==1){
            x++; //right
        }
        else if (r==2){
            y--; //down
        }
        else if (r==3){
            x--; //left
        }
        
        if(x > -n && x < n && y > -n && y < n){
            if(visited[x + n][y + n] == 0){ //mark as visited if not already
                visited[x + n][y + n] = 1;
                total_visited++;
            }
        }
    }  
    //dont include outside of square or square boundaries
    double fraction = (double) total_visited / (double) ((2*n - 1) * (2*n - 1));
    return fraction;
}

//Do not change the code below
int main(int argc, char *argv[])
{
	int trials = 1000;
	int i, n, seed;
	if (argc == 2) seed = atoi(argv[1]);
	else seed = 12345;

	srand(seed);
	for(n=1; n<=64; n*=2)
	{	
		double sum = 0.;
		for(i=0; i < trials; i++)
		{
			double p = two_d_random(n);
			sum += p;
		}
		printf("%d %.3lf\n", n, sum/trials);
	}
	return 0;
}
