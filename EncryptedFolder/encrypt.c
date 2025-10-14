#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#define MAX 10240
//encrypt the message and write the result to file fd

void encrypt(char *message, unsigned char key, unsigned char shift, int fd)
{
	int len = strlen(message);
	printf("len = %d\n", len);
	int msg[len];

	for(int i = 0; i<len; i++)
		msg[i] = (message[i] << shift) ^ key; //bitwise shift operator. what does ^ key do?
	write(fd, msg, len*sizeof(int));
	printf("%s\n", (char *)msg);
}

int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		printf("Usage: %s plain-text-file encrypted-file key shift\n", argv[0]);
		return -1;
	}

    char message[MAX]; //max chars for the message. 

    int fd = open(argv[1], O_RDONLY); // opening the file to read only dont edit. 
	

	//my question is, why is it an int? 
	//it is an int because it is a file descriptor! 
	//In Unix type systems, 
	//a file descriptor (fd for short) is a small positive integer 
	//used as reference to an open file in a process.
	
	//read() function reads up to x bytes from the file descriptor 

    if(fd < 0)
    {
        printf("Cannot open file %s\n", argv[1]);
        return -1;
    } // file descriptors are always positive ints. 


    int len = read(fd, message, MAX);
	close(fd);
	assert(len > 0); //if len wasnt >0 then there would be no message. 


	//note how we open the file
	fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0600);
	//the open is the path which is argv[2] (the file we want to use)
	//the flags go as such When a file is opened in C using the "w" (write) mode, 
	//it overwrites the existing content of the file. If the file already exists, 
	//its contents are truncated (effectively deleted), 
	//and the file is treated as a new, empty file ready for writing. 
	//If the file does not exist, it will be created. 
	
	if(fd < 0)
	{
		printf("Cannot open the file\n");
		return -1;
	}


	int key = atoi(argv[3]); //some int value
	int shift = atoi(argv[4]); //some int value.
	assert(key >= 0 && key <= 255);
	assert(shift >=0 && shift <= 24);
	encrypt(message, key, shift, fd);

	//remember to close the file
	close(fd);
	return 0;
}
