#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "template.h"
#include "lib/cocky_library.h"


void params_constructor(params* pms, const char* name)
{
    // obtain full project name
    pms->full_name = (char*) malloc(strlen(name) + 1);
    strcpy(pms->full_name, name);
    // shrink possible leading numbers
    pms->alpha_name = shrink_to_first_alpha(pms->full_name);
    // to upper + _H
    pms->define_header = to_upper_for_header_file(pms->alpha_name);
}

void kill_params(params* pms){
    free(pms->full_name);
    free(pms->alpha_name);
    free(pms->define_header);
}


