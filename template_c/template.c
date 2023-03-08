#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>

#include "template.h"


void handle_args(int argc, char* argv[])
{    
    parameters pms = {".", "c_source_file", ""};

    for (int j = argc - 1; j >= 0; j--)
        fprintf(stderr,"argv[%d] -> %s\n", j, argv[j]);

    if (argc == 1) print_manual();
    if (argc == 2) print_manual();
    if (argc == 3 || argc == 4) {
        if (argc == 3 && strcmp(argv[1],"file") == 0) {
            strcpy(pms.name, argv[2]);
            if(check_path(pms.path)) located_file(pms.path, pms.name);
        }
        if (argc == 4 && strcmp(argv[1], "file") == 0) {
            strcpy(pms.name, argv[2]);
            strcpy(pms.path, argv[3]);
            if(check_path(pms.path)) located_file(pms.path, pms.name);
        }
        if (argc == 3 && strcmp(argv[1], "project") == 0) {
            strcpy(pms.name, argv[2]);
            extact_header(&pms);
            if (check_path(pms.path)) project_directory(&pms);
        }
        if (argc == 4 && strcmp(argv[1], "project") == 0) {
            strcpy(pms.name, argv[2]);
            strcpy(pms.path, argv[3]);
            extact_header(&pms);
            if(check_path(pms.path)) project_directory(&pms);
        }
    }
    print_parameters(&pms);
}

void print_manual()
{
    puts("\ncommand line arguments");
    puts("1 - [TYPE WORD] project or file");
    puts("2 - [FILE NAME] or [PROJECT NAME] without extension");
    puts("3 - [PATH] default -> current directory");
}

void extact_header(parameters* pms)
{
	int k = 0;
	while (!isalpha(pms->name[k++]));
	k--;
	printf("skip characters -> %d\n", k);
	for (int i = 0; pms->name[k] !='\0'; k++, i++) 
                                        pms->header[i] = pms->name[k];
	pms->header[k] = '\0';
    printf("pms.path -> %s pms.name -> %s pms.header -> %s\n",
                        pms->path, pms->name, pms->header);
}

void print_parameters(parameters* pms)
{
    fprintf(stderr, "param.path->%s\nparam.name->%s\nparam.header->%s\n",
                    pms->path, pms->name, pms->header);
}

void located_file(char* path, const char* name)
{
    strcat(strcat(strcat(path, "/"),name), ".c");
    fprintf(stderr, "located file temp-> %s\n", path);
    FILE* file = fopen(path,"w");
    fprintf(file,
                    "#include <stdio.h>\n"
                    "#include <stdlib.h>\n\n"
                    "int main(int argc, char* argv[])\n"
                    "{\n"
                    "\tprintf(\"file %s.c\");\n"
                    "\treturn EXIT_SUCCESS;\n"
                    "}\n", name);
    fclose(file);
}

int check_path(const char* path)
{
    int result = 0;
    DIR* dir = opendir(path);
    if (dir) result = 1;
    else {
        fprintf(stderr, "ERROR PATH NOT EXIST -> %s\n", path);
        result = 0;
    }
    closedir(dir);
    return result;
}

void project_directory(parameters* pms)
{
    DIR* dir = opendir(pms->path);
    strcat(strcat(pms->path,"/"), pms->name);
    if(dir) {
        mkdir(pms->path, 0777);
        project_content(pms);
    } 
    else fprintf(stderr, "DIRECTORY %s NOT EXIST\n", pms->path);      
    closedir(dir);
}

void project_content(parameters* pms)
{
    char header_caps[AT_LEAST_SIGNIFICANT] = {0};
    int j = 0;
    for ( j; pms->header[j] != '\0'; j++) 
                        header_caps[j] = toupper(pms->header[j]);
    header_caps[j] = '\0';
    strcat(header_caps,"_H");
    fprintf(stderr, "header -> %s\n", header_caps);
   
    files(header_caps, pms);
}

void files(const char* header_caps, const parameters* pms)
{    
    strcat(strcat(strcat(strcpy(pms->path, pms->path),"/"),pms->header),".h");
    FILE* file = fopen(pms->path, "w");
    fprintf(file,   "#ifndef %s\n"
                    "#define %s\n\n"
                    "\tvoid greeting(void);\n\n"
                    "#endif"
                    ,header_caps, header_caps);
    fclose(file);
}
