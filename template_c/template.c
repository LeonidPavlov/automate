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
    int length = strlen(pms->dist_path) + strlen(pms->full_name) * 2;
    char* tmp = calloc(length, sizeof(char));
   
    FILE* header = fopen(
        strcat(strcat(strcat(strcpy(tmp, pms->folder_path), "/"),
                                         pms->alpha_name), ".h"), "w");
    fprintf(header,     "#ifndef %s\n" 
                        "#define %s\n\n"
                        "\t#define MODULE_NAME \"%s\"\n\n"
                        "\tvoid welcome(void);\n\n"
                        "#endif\n"
                        , pms->define_header, pms->define_header,
                        pms->full_name);
    fclose(header);
    
    FILE* row = fopen(
        strcat(strcat(strcat(strcpy(tmp, pms->folder_path), "/"),
                                         pms->alpha_name), ".c"), "w");
    fprintf(row,    "#include <stdio.h>\n\n"
                    "#include \"%s.h\"\n\n\n"
                    "void welcome(void)\n{\n"
                    "\tfprintf(stderr, \"Welcome ~ %%s\\n\", MODULE_NAME);\n}\n"
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
                    , pms->alpha_name ,pms->full_name);
    fclose(make);

    strcat(strcat(strcpy(tmp, "cd "), pms->folder_path), " && make");
    system(tmp);
    strcat(tmp," clear");
    system(tmp);
    free(tmp);
}
