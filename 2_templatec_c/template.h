#ifndef TEMPLATE_C_H
#define TEMPLATE_C_H

typedef struct project_directory_parameters {
    // name with posible lead numbers
    const char* full_name;
    // name cleaned from leading digits
    const char* alpha_name;
    // name for header file all uppercase with _H end
    const char* define_header;
} params;

void params_constructor(params* params, const char* name);

#endif