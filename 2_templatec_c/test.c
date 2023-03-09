#include <stdio.h>
#include <stdlib.h>

#include "template.h"


params parameters;
params* pms = &parameters;
const char * test_name = "327_huyev_tebe_b_gopu";

void test_constructor_and_killer();
void params_content(const params* const pms);

int main(int argc, char** argv)
{
    test_constructor_and_killer();
    return 0;
}

void params_content(const params* const pms)
{
    fprintf(stderr, "full_name -> %s\n", pms->full_name);
    fprintf(stderr, "alpha_name -> %s\n", pms->alpha_name);
    fprintf(stderr, "define_header -> %s\n", pms->define_header);
}

void test_constructor_and_killer()
{
    params_constructor(pms, test_name);
    params_content(pms);
    kill_params(pms);
}
