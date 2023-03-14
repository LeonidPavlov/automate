#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>


#include "template.h"
#include "lib/cocky_library.h"

const char* usage = "\nUsage C language source code folder generator:\n"
                    "usage: ./template.out [FOLDER_NAME] [PATH]\n"
                    "[FOLDER_NAME] - must be at least one letter\n"
                    "[PATH] optional, default current dir \n\n";
params parameters;
params* ppm = &parameters;

void interview(int argc, char* argv[])
{
    switch (argc)
    {
    case 1:
        log("\nto less params, than need ", argc -1, "%d");
        log("", usage, "%s");
        break;

    case 2:
        log("\none parameter, current directory folder name: ", argv[1], "%s");
        if ( check_one_alpha(argv[1]) ) params_constructor(ppm, argv[1], ".");
        else log("ERROR", " not suitable name need one alphabet symbol", "%s");
        break;

    case 3:
        log("\ntwo parameters, folder name-> ", argv[1], "%s");
        log("\t\tpath-> ", argv[2], "%s");
        if (check_dir_existance(argv[2])) {
            if (check_one_alpha(argv[1])) 
                params_constructor(ppm, argv[1], argv[2]);
            else log("ERROR ",
                        "not suitable name, need one alphabet symbol", "%s"); 
        } else log("ERROR, not such directory ", argv[2], "%s"); 
        break;
    
    case 4:
        log("\nto much parameters", argc -1, "%d");
        log("", usage, "%s");
    }
}

void params_constructor(params* pms, const char* name, const char* path)
{
    pms->full_name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(pms->full_name, name);
    
    pms->alpha_name = calloc(strlen(name) + 1, sizeof(char));
    pms->alpha_name = shrink_to_first_alpha(pms->alpha_name, name);
    
    pms->header_H = calloc(strlen(pms->alpha_name) + 3, sizeof(char));
    pms->header_H = to_upper_for_header_file(pms->header_H, pms->alpha_name);

    pms->folder_path = calloc(strlen(name) + strlen(path) + strlen("//") + 1,
                                                             sizeof(char));
    strcat(strcat(strcat(strcpy(pms->folder_path, path),"/"),name),"/");
    
    pms->dist_path = calloc(strlen(pms->folder_path) + 
                            strlen("dist") + strlen("/") + 1, sizeof(char));
    strcat(strcpy(pms->dist_path,pms->folder_path),"dist/");
    
    params_content(pms);
    if (add_directories(pms->folder_path, pms->dist_path)) 
                                                create_project_files(pms);
    else  log("source folder already exist ->", pms->folder_path, "%s");
    kill_params(pms);
}

void params_content(const params* const pms)
{
    fprintf(stderr, "full_name -> %s\n", pms->full_name);
    fprintf(stderr, "alpha_name -> %s\n", pms->alpha_name);
    fprintf(stderr, "header_H -> %s\n", pms->header_H);
    fprintf(stderr, "folder_path -> %s\n", pms->folder_path);
    fprintf(stderr, "dist_path -> %s\n", pms->dist_path);
}

void kill_params(params* pms){
    free(pms->full_name);
    free(pms->alpha_name);
    free(pms->header_H);
    free(pms->folder_path);
    free(pms->dist_path);
}


int add_directories(const char* folder, const char* dist)
{
    int result = 1;
    if (check_dir_existance(folder)) result = 0;
    else {
        mkdir(folder, 0777);
        mkdir(dist, 0777);
    } 
    return result;
}

void create_project_files(const params* const pms)
{
    int length = strlen(pms->dist_path) + strlen(pms->full_name) * 2;
    char* tmp = calloc(length, sizeof(char));
   
    FILE* header = fopen(
        strcat(strcat(strcat(strcpy(tmp, pms->folder_path), "/"),
                                         pms->alpha_name), ".h"), "w");
    fprintf(header,     "#ifndef %s\n" 
                        "#define %s\n\n"
                        "#define MODULE_NAME \"%s\"\n\n"
                        "void welcome(void);\n\n"
                        "#endif\n"
                        , pms->header_H, pms->header_H,
                        pms->full_name);
    fclose(header);
    
    FILE* row = fopen(
        strcat(strcat(strcat(strcpy(tmp, pms->folder_path), "/"),
                                         pms->alpha_name), ".c"), "w");
    fprintf(row,    "#include <stdio.h>\n\n"
                    "#include \"%s.h\"\n\n\n"
                    "void welcome(void)\n{\n"
                    "\tfprintf(stderr, \"welcome %%s\\n\", MODULE_NAME);\n}\n"
                    , pms->alpha_name);
    fclose(row);
    
    FILE* test = fopen(
        strcat(strcat(strcat(strcpy(tmp, pms->folder_path), "/"),
                                         "test"), ".c"), "w");
    fprintf(test,   "#include \"%s.h\"\n\n\n"
                    "int main(int argc, char* argv[])\n" 
                    "{\n\twelcome();\n}\n"  
                    , pms->alpha_name);
    fclose(test);

    FILE* make = fopen(
            strcat(strcat(strcpy(tmp, pms->folder_path),"/"), "makefile"), "w");
    fprintf(make,   "rf=%s\n"
                    "tf=test\n"
                    "exf=dist/%s.out\n\n\n"
                    "all: ${exf}\n"
                    "\t./${exf}\n\n"
                    "${exf} : ${rf}.o ${tf}.o\n"
                    "\tgcc ${rf}.o ${tf}.o -o ${exf}\n\n"
                    "${tf}.o : ${tf}.c ${rf}.h\n"
                    "\tgcc -c ${tf}.c\n\n"
                    "${rf}.o : ${rf}.c ${rf}.h\n"
                    "\tgcc -c ${rf}.c\n\n"
                    "clear :\n\trm -f *.o dist/*.out\n"
                    , pms->alpha_name ,pms->alpha_name);
    fclose(make);

    strcat(strcat(strcpy(tmp, "cd "), pms->folder_path), " && make");
    system(tmp);
    strcat(tmp," clear");
    system(tmp);
    free(tmp);
}
