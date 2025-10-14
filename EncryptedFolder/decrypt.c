#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX 10240 // what is this max? 
#define MAX_WORD_COUNT 60000 //we have less than 60000 words
#define MAX_WORD_LENGTH 80 //each word is less than 80 letters

//Using these two global variables can be justified :)
char words[MAX_WORD_COUNT][MAX_WORD_LENGTH]; //2-d array to hold all the words

//I wonder why we use a 2d array?

int word_count = 0; //number of words, initilized to 0

//Note the words in the dictionary file are sorted
//This fact could be useful
void read_file_to_array(char *filename)
{
    FILE *fp; //what is stored in the file struct?

    //open the file for reading
    fp = fopen(filename, "r"); 

    if(fp==NULL)
    {
        printf("Cannot open file %s.\n", filename);
        exit(-1);
    }

    //make sure when each word is saved in the array words,
    //it does not end with a '\n'
    //see how this is done using fscanf 

    //feof used to check the end-of-file indicator for a given file stream. 
    //It takes a FILE* stream as an argument and returns a 
    //non-zero value if the end-of-file indicator is set, and 0 otherwise.
    while(!feof(fp))
        fscanf(fp, "%s\n", words[word_count++]);
    fclose(fp);
}

int bin_search_words(char words[MAX_WORD_COUNT][MAX_WORD_LENGTH], int word_count, char* word){
    //use this array ^^^^
    int low = 0;
    int high = word_count - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(strcmp(words[mid], word) == 0){
            return 1;
        }
        else if(strcmp(words[mid], word) < 0){
            low = mid + 1; // word is in upper half
        }
        else{
            high = mid - 1; // word is in lower half
        }
    }
    return 0; //word not found.
}

int in_dict(char *word)
{
    read_file_to_array("dict.txt");
    int found = bin_search_words(words, word_count, word);
    if(found == 1){
        return 1; //true
    }
    else{
        return 0; //false
    }
}

//TODO
//Use key and shift to decrypt the encrypted message
//len is the length of the encrypted message
//Note the encrypted message is stored as an array of integers (not chars)
//The result is in decrypted
void decryption(unsigned char key, unsigned char shift, const int *encrypted, int len, char *decrypted)
{
    len = len / sizeof(int);
    char message[len];

    for(int i = 0; i < len; i++){
        decrypted[i] = (char)(encrypted[i] >> shift) ^ key;
    }
    
    decrypted[len] = '\0';
}

//TODO
//calculate a score for a message msg
//the score is used to determine whether msg is the original message
int message_score(const char* msg)
{
    int count = 0;
    int iter = 0;
    while(msg[iter] != '\0'){
        char myMessage[MAX_WORD_LENGTH];
        if(isalpha(msg[iter])){
            strcat(myMessage, &msg[iter]); //append to the string
            iter++;
            if(in_dict(myMessage)){
                count++;
            }
        }
        else{
            iter++;
        }
    }
    return count;
}

//search using all the (key, shift) combinations
//to find the original message
//result is saved in message
void search(const int *encrypted, int len, char *message)
{
	char decrypted[MAX];

    int max_score = 0;
    strcpy(message, ""); //what does strcpy do?
    
    for(unsigned char k = 0; k < 255; k++)
    {
        for(unsigned char shift = 0; shift <= 24; shift++)
        {
            decryption(k, shift, encrypted, len, decrypted);
			int score = message_score(decrypted);
			if(score > max_score)
			{	
				max_score = score;
				strcpy(message, decrypted);
			}
        }
    }
}


//read the encrypted message from the file to encrypted
//return number of bytes read
int read_encrypted(char *filename, int *encrypted)
{
    FILE* file_to_open;
    file_to_open = fopen(filename, "r");
    if(file_to_open == NULL){
        perror("could not open file, or file was not passed");
        exit(1);
    }
    //fread(void* ptr, size_t size of each byte, size_t num_elements, FILE* stream)
    //the first ptr is where the block of memory is being read to
    //last file is the file being read from into the buffer (first ptr);
    int len = fread(encrypted, sizeof(int), MAX, file_to_open);
    fclose(file_to_open);
    return len;
}

//Do not change the main() function
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("%s encrypted-message\n", argv[0]);
		return 0;
	}

	read_file_to_array("dict.txt");

	int encrypted[MAX];
	int len = read_encrypted(argv[1], encrypted);
	
	char message[MAX];
	strcpy(message, "");
	search(encrypted, len, message);
	printf("%s\n", message);
	return 0;
}
