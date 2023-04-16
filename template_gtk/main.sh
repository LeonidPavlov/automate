#!/usr/bin/env bash

set -x

#                               DEFINING WORKING DIRECTORY
working_dir="${PWD}/"

source_path="${0%/*}/";
source_path="${source_path#*./}"

full_path=$working_dir$source_path

source ${source_path}func.sh


folder_name=
header=
HEADER=

# function
handle_folder_name_and_headers


source ${source_path}const.sh

{
    echo -e $main_file_content 
} > "${folder_name}/${header}.c"

{
    echo -e $makefile_content
} > "${folder_name}/makefile"

cd $folder_name && make

