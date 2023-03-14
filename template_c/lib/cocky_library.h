#ifndef COCKY_LIBRARY_H
#define COCKY_LIBRARY_H

    char* shrink_to_first_alpha(char* dest, const char* source);   
    char* to_upper_for_header_file(char* dest, const char* source); 
    int check_one_alpha(const char* source);
    int check_dir_existance(const char* assumption);

#endif
