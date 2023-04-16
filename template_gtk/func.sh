function handle_folder_name_and_headers()
{
     truth=0
    while [[ $truth -eq 0 ]]
    do
        printf "enter folder name : "
        read folder_name
        folder_name="${folder_name// /_}"
        if [ -e $folder_name ] 
        then
            echo FOLDER ALREADY EXIST ENTER ANOTHER
        else 
            mkdir "${folder_name}"
            mkdir "${folder_name}/dist"
            truth=1
        fi
    done

    # REMOVING LEADING NUMBERS
    header="${folder_name##[0-9]*[0-9]}"
    # REMOVING LEADING UNDERSCORE
    header="${header#_}"
    # TO UPPER CASE
    HEADER="${header^^}";   
}
