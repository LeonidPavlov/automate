#ifndef TEMPLATE_C_H
#define TEMPLATE_C_H

typedef struct project_directory_parameters {
    // name with posible lead numbers
    char* full_name;
    // name cleaned from leading digits
    char* alpha_name;
    // name for header file all uppercase with _H end
    char* define_header;
    char* folder_path;
    char* dist_path;
} params;

void interview(int argc, char* argv[]);

void params_constructor(params* pms, const char* name, const char* dir);
void params_content(const params* const pms);
void kill_params(params* pms);

int check_dir_existance(const char* assumption);
void add_directories(const params* const pms);
void create_project_files(const params* const pms);

#endif