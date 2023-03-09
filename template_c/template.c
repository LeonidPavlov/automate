#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>


#include "template.h"
#include "lib/cocky_library.h"

const char* usage = "\nInitial C project folder generator\n"
                    "usage: ./template.out [FOLDER_NAME] [PATH]\n"
                    "FOLDER_NAME - must be at least one letter\n"
                    "PATH - is optional\n\n";
params parameters;
params* ppm = &parameters;

void interview(int argc, char* argv[])
{
    if(argc == 1) {
        fprintf(stdout,"%s" ,usage);
        exit(0);
    } 
    if(argc == 2) params_constructor(ppm, argv[1], "");
    if(argc == 3 && check_dir_existance(argv[2])) 
                            params_constructor(ppm, argv[1], argv[2]);
    else {
        fprintf(stdout,"%s" ,usage);
        exit(0);
    } 
        
    params_content(ppm);
    add_directories(ppm);
    kill_params(ppm);
}

void params_constructor(params* pms, const char* name, const char* dir)
{
    // obtain full project name
    pms->full_name = (char*) malloc(strlen(name) + 1);
    strcpy(pms->full_name, name);
    
    // shrink possible leading numbers
    pms->alpha_name = shrink_to_first_alpha(pms->full_name);
    if(strlen(pms->alpha_name) == 1) {
        fprintf(stderr, "ILLEGAL PROJECT NAME\n");
        exit(0);
    }
    
    // to upper + _H
    pms->define_header = to_upper_for_header_file(pms->alpha_name);

    char* fp = calloc(strlen(dir) + strlen(pms->full_name) 
                        + strlen("//") +1, sizeof(char));
    pms->folder_path = fp;
    strcat(strcat(strcpy(fp, dir),"/"), pms->full_name);

    fp = calloc(strlen(pms->folder_path) + strlen("dist") + 2, sizeof("char"));
    pms->dist_path = fp;
    strcat(strcat(strcpy(fp, pms->folder_path),"/"), "dist");
}

void params_content(const params* const pms)
{
    fprintf(stderr, "full_name -> %s\n", pms->full_name);
    fprintf(stderr, "alpha_name -> %s\n", pms->alpha_name);
    fprintf(stderr, "define_header -> %s\n", pms->define_header);
    fprintf(stderr, "folder_path -> %s\n", pms->folder_path);
    fprintf(stderr, "dist_path -> %s\n", pms->dist_path);
}

void kill_params(params* pms){
    free(pms->full_name);
    free(pms->alpha_name);
    free(pms->define_header);
    free(pms->folder_path);
    free(pms->dist_path);
}

int check_dir_existance(const char* assumption)
{
    int res = 0;
    printf("assumption -> %s\n", assumption);
    DIR* dir = opendir(assumption);
    if(dir) res = 1;
    else fprintf(stdout, "directory vacant\n");
    closedir(dir);
    return res;
}

void add_directories(const params* const pms)
{
    if (check_dir_existance(pms->folder_path)) {
        fprintf(stderr, "CAN'T CREATE PROJECT FOLDER -> ALSO EXIST ?\n");
    } else {
        mkdir(pms->folder_path, 0777);
    }
    if (check_dir_existance(pms->dist_path)) {
        fprintf(stderr, "CANT CREAT DIST DIR ?\n");
    } else {
        mkdir(pms->dist_path, 0777);
        create_project_files(pms);
    }
}

void create_project_files(const params* const pms)
{

}
