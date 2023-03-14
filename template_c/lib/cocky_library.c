#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

char* shrink_to_first_alpha(char* dest, const char* source)
/*
    shrinks not alphabetic simbols in the begining of string
    uses calloc and must be released memory
*/
{
    int j = 0;
    for ( j; !isalpha(source[j]) && j <= strlen(source) ; j++);
    
    int k = 0;
    for ( k, j; source[j] != '\0'; j++, k++) dest[k] = source[j];
    dest[k] = '\0';
    return dest;
}

char* to_upper_for_header_file(char* dest, const char* source)
/*
    filename without extension to upper case and adds _H
    possible memory leak without release
*/
{
    const char* suff = "_H";
    for (int j = 0; source[j] != '\0'; j++) dest[j] = toupper(source[j]);
    strcat(dest,suff);
    return dest;
}

int check_one_alpha(const char* source)
{
    int result = 0;
    while(*source != 0)
        if (isalpha(*(source++))) result = 1;
    return result;
}

int check_dir_existance(const char* assumption)
{
    int res = 0;
    printf("directory existence assumption -> %s\n", assumption);
    DIR* dir = opendir(assumption);
    if(dir) res = 1;
    else fprintf(stderr, "no such directory\n");
    closedir(dir);
    return res;
}

