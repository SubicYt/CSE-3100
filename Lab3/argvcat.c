#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    size_t len = strlen(s1) + strlen(s2) + 1;
    char *mystr = malloc(len);
    if (mystr == NULL){
        my_error("malloc failed");
    }

    strcpy(mystr, s1); // starting string
    strcat(mystr, s2); // concatenates to the rest of mystr
    
    return mystr;
}

int main(int argc, char *argv[])
{
    char *s;
    char *temp;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        temp = s;
        s = my_strcat(s, argv[i]);
        free(temp);
    }

    printf("%s\n", s);

    free(s);
    return 0;
}

    printf("%s\n", s);

    return 0;
}
