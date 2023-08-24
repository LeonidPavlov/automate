#!/bin/bash 

# EXIT IF PROJECT NAME IS EMPTY
if [ ${#1} -eq 0 ]
then 
    echo "USAGE: ./init.sh PROJECT_NAME PATH"
    exit
fi

# OBTAIN PROJECT NAME FOR FOLDER WITHOUT CHANGES
project_name=$1

# REMOVE LEADED NUMBERS AND UNDERSCORE _ FOR HEADER
without_leaded_numbers=$project_name

while ! [[ "${without_leaded_numbers:0:1}" = [a-z] ]] \
                         && ! [[ "${without_leaded_numbers:0:1}" = [A-Z] ]]
do
    without_leaded_numbers="${without_leaded_numbers:1}"
    if [ ${#without_leaded_numbers} -eq 0 ]
    then 
        echo "in project folder name must be at least one letter"
        exit
    fi
done

# CHECK RESULT
echo "header without leaded numbers and _ -> $without_leaded_numbers"

# UPPERCASE AND LOWCASE HEADERS
# upper case header
uc_header="${without_leaded_numbers^^}"
echo "header with upper case letters => ${uc_header}"
# low case header
lc_header="${without_leaded_numbers,,}"
echo "header with low case letters => ${lc_header}"

path=${2:-.}
echo "PATH -> $path"

if ! [ -e $path ]
then 
    echo "folder in path is not exist"
    exit
fi

project_folder=$path/$project_name
echo "project name with path => $project_folder"
if [ -e $project_folder ]
then 
    echo "can't create folder ${project_foder} already exist"
    exit
fi

mkdir $project_folder && cd $project_folder

 
