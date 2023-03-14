#include <stdio.h>

#ifndef TEMPLATE_C_H
#define TEMPLATE_C_H

#define log(message, var, format) fprintf(stderr, message" "format"\n", (var))

typedef struct project_directory_parameters {
    char* full_name;
    char* alpha_name;
    char* header_H;
    char* folder_path;
    char* dist_path;
} params;


void interview(int argc, char* argv[]);

void params_constructor(params* pms, const char* name, const char* path);
void params_content(const params* const pms);
void kill_params(params* pms);

int add_directories(const char* folder, const char* dist);
void create_project_files(const params* const pms);

#endif