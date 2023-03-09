#ifndef TEMPLATE_C_H
#define TEMPLATE_C_H

typedef struct project_directory_parameters {
    // name with posible lead numbers
    char* full_name;
    // name cleaned from leading digits
    char* alpha_name;
    // name for header file all uppercase with _H end
    char* define_header;
} params;

void params_constructor(params* pms, const char* name);
void kill_params(params* pms);

#endif