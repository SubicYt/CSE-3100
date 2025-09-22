#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
    int x = 0;
    int y = 0;
    int z = 0;

    for(int i = 0; i < n; i++){
        int direction = rand() % 6;
        if(direction == 0) x++;
        else if(direction == 1) x--;
        else if(direction == 2) y++;
        else if(direction == 3) y--;
        else if(direction == 4) z++;
        else if(direction == 5) z--;
    }
    //represent 3d point in 1d array?
    //row major - index(xyz) = x * size^2 + y * size + z;
    int index = (x + n) * (2*n + 1) * (2*n + 1) + 
                (y + n) * (2*n + 1) + 
                (z + n);

    grid[index]++;
}

//TODO
//Implement the following function 
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r){

    int count = 0;
    int total = 0;
    int size = (2*n+1) * (2*n+1) * (2*n+1);
    for(int i = 0; i < size; i++){
        //Access the individual 3d coordinates
        // x = index / size^2 - n
        // y = (index / size) % size - n
        // z = index % size - n
        int x = i / ((2*n + 1) * (2*n + 1)) - n;
        int y = (i / (2*n + 1)) % (2*n + 1) - n;
        int z = i % (2*n + 1) - n;
        double distance = (x*x) + (y*y) + (z*z);
        if (distance <= ((r * n) * (r * n))){
            count += grid[i];
        }
        total += grid[i];
    }
    return (double)count / (double)total;
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}


void diffusion(int n, int m)
{
	//fill in a few line of code below
    //size ranges from -n to n including zero in each dimension.
    int size = (2*n + 1) * (2*n + 1) * (2*n + 1);
    //using calloc to initialize all elements to zero.
    //ask about calloc in office hours.
    int *grid = (int *)malloc(size * sizeof(int));

	for(int i = 1; i<=m; i++){
        one_particle(grid, n);
    }

	print_result(grid, n);
	//fill in some code below
    free(grid); //idk if free is in the right spot, ask abt it in office hrs tmw.
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}