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

namespace="lnp"

header_file="${lc_header}.hpp"
row_file="${lc_header}.cpp"
main_file="test"

{
    echo "#ifndef ${uc_header}_H"
    echo "#define ${uc_header}_H    "
    echo ""
    echo "namespace ${namespace}"
    echo "{"
    echo -e "\tvoid greeting(void);"
    echo "}"
    echo ""
    echo "#endif"
} > $header_file

{
    echo "#include <iostream>"
    echo ""
    echo "#include \"${header_file}\""
    echo ""
    echo "using namespace std;"
    echo ""
    echo ""
    echo "namespace ${namespace}"
    echo "{"
    echo -e "\tvoid greeting(void)"
    echo -e "\t{"
    echo -e "\t\tcout << \"${uc_header}\" << endl;"
    echo -e "\t}"
    echo "}"
} > $row_file

{   echo "#include <iostream>"
    echo "#include <exception>"
    echo ""
    echo "#include \"$header_file\""
    echo ""
    echo "using namespace std;"
    echo ""
    echo ""
    echo "int main(int argc, char* argv[])"
    echo "{"
    echo -e "\ttry{"
    echo -e "\t\t${namespace}::greeting();"
    echo -e "\t} catch (exception & exc) {"
    echo -e "\t\tcerr << exc.what() << endl;"
    echo -e "\t}"
    echo "}"
} > ${main_file}.cpp

mkdir dist
executable="${lc_header}.out"

{
    echo "all : dist/${executable}"
    echo -e "\tdist/${executable}"
    echo ""
    echo "dist/${executable} : ${lc_header}.o ${main_file}.o ${lc_header}.hpp"
    echo -e "\tg++ ${lc_header}.o ${main_file}.o -o dist/$executable"
    echo ""
    echo "${main_file}.o : ${main_file}.cpp ${lc_header}.hpp"
    echo -e "\tg++ -c ${main_file}.cpp"
    echo ""
    echo "${lc_header}.o : ${lc_header}.cpp ${lc_header}.hpp"
    echo -e "\tg++ -c ${lc_header}.cpp"
    echo ""
    echo "clear : "
    echo -e "\trm -f *.o dist/*"
    echo ""
    echo "valgrind : all"
    echo -e "\tvalgrind dist/${executable}" 
} > makefile

make

