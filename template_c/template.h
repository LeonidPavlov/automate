#ifndef TEMPLATE_H
#define TEMPLATE_H

#define AT_LEAST_SIGNIFICANT 32

typedef struct project_parameters {
    char path[AT_LEAST_SIGNIFICANT * 4];
    char name[AT_LEAST_SIGNIFICANT];
    char header[AT_LEAST_SIGNIFICANT];
} parameters;

void handle_args(int argc, char* argv[]);
void print_manual();
void extact_header();
void print_parameters(parameters* pms);
void located_file(char* path, const char* name);
int check_path(const char* path);
void project_directory(parameters* pms);
void project_content(parameters* pms);
void files(const char* header_caps, const parameters* pms);

#endif

