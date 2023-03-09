#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* shrink_to_first_alpha(const char* source)
/*
    shrinks not alphabetic simbols in the begining of string
    uses calloc and must be released memory
*/
{
    char* temp = calloc(strlen(source) + 1, sizeof(char));

    int j = 0;
    for ( j; !isalpha(source[j]) ; j++);

    int k = 0;
    for ( k, j; source[j] != '\0'; j++, k++) temp[k] = source[j];
    temp[k] = '\0';

    char* result = calloc(strlen(temp) + 1, sizeof(char));
    strcpy(result, temp);
    free(temp);

    return result;
}

char* to_upper_for_header_file(const char* source)
/*
    filename without extension to upper case and adds _H
    possible memory leak without release
*/
{
    const char* suff = "_H";
    char* result = calloc(strlen(source) + strlen(suff) + 1, sizeof(char));
    for (int j = 0; source[j] != '\0'; j++) result[j] = toupper(source[j]);
    strcat(result,suff);
    return result;
}
