#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <dirent.h>

#define  AT_LEAST_SIGNIFICANT 32

char dir_name[AT_LEAST_SIGNIFICANT * 2] = {0};
char header[AT_LEAST_SIGNIFICANT] = {0};
char path[AT_LEAST_SIGNIFICANT * 5] = {0};

void handle_args(int argc, char * argv[]);
void project();
void file();
void extact_header(void);
int add_main();
int add_header();
int add_row_file();
int add_makefile();

// USAGE -> ./template.out and
// [FILENAME or PROJECT_NAME without extension]
// [WORD project, if project or file, if file]
// [PATH if somwhere other place]
// without arguments will be create file sample.c


int main(int argc, char * argv[])
{
	puts("USAGE -> ./template.out and\n"
						"[FILENAME or PROJECT_NAME without extension]\n"
						"[WORD project, if project or file, if file]\n"
						"[PATH if somwhere other place]\n"
						"without arguments will be create file sample.c\n");
	handle_args(argc, argv);
	return EXIT_SUCCESS;
}

void handle_args(int argc, char * argv[])
{
	if (argc == 1) file("sample");
	if (argc == 2) {
		strcpy(path, argv[1]);
		file();
	} 
	if (argc == 3){
		strcpy(path, argv[1]);
		strcpy(dir_name, argv[1]);
		if (strcmp(argv[2], "file") == 0) file();
		if (strcmp(argv[2], "project") == 0) project(); 
	}
	if (argc == 4) {
		DIR* dir = opendir(argv[3]);
		if (dir) { 
			strcpy(path, argv[3]);
			strcpy(dir_name, argv[1]);
			strcat(path, "/");
			strcat(path, dir_name);
			if (strcmp(argv[2], "file") == 0) file();
			if (strcmp(argv[2], "project") == 0) project();
		}
		else fprintf(stderr, "directory %s not exist\n", argv[3]);
	}
}

void project()
{
	extact_header();
	printf("header -> %s\n", header);
	int child_pid  = fork();
	if(child_pid == 0) execl("/usr/bin/mkdir","/usr/bin/mkdir", path, NULL);
	if (wait(&child_pid)) printf("add main file -> %d\n", 
												add_main());
	printf("header file -> %d\n", add_header());
	printf("row file -> %d\n", add_row_file());
	// printf("makefile -> %d\n", add_makefile());
	// strcpy(dir_name, "cd ");
	// strcat(dir_name, name);
	// strcat(dir_name, " && make");
	// system(dir_name);

	/* THIS VERSION + MAY BE NEW */
}

void extact_header()
{
	int k = 0;
	while (!isalpha(dir_name[k++]));
	k--;
	printf("skip characters -> %d\n", k);
	for (int i = 0; dir_name[k] !='\0'; k++, i++) header[i] = dir_name[k];
	header[k+1] = '\0';
}

void file()
{
	char * one_file_content = "#include <stdio.h>\n#include <stdlib.h>\n\n"
						"int main(int argc, char *argv[])\n{\n\n\t"
						"return EXIT_SUCCESS;\n}\n";
	FILE* file = fopen(strcat(path, ".c"), "w");
	fprintf(file, "%s", one_file_content);
	fclose(file);
}

int add_main()
{
	char temp[AT_LEAST_SIGNIFICANT * 5] = {0};
	strcpy(temp, path); 
	strcat(strcat(temp, "/"), "main");
	FILE* main = fopen(strcat(temp, ".c"), "w");
	fprintf(main,	"#include <stdio.h>\n"
					"#include <stdlib.h>\n\n"
					"#include \"%s.h\"\n\n\n"
					"int main(int argc, char* argv[])\n{\n"
					"\tgreeting();\n"
					"\treturn EXIT_SUCCESS;\n}\n", header);
	return fclose(main);
}

int add_header()
{
	char temp[AT_LEAST_SIGNIFICANT * 5] = {0};
	strcpy(temp, path);
	char temp_header[AT_LEAST_SIGNIFICANT] = {0};
	strcpy(temp_header, header); 	
	FILE* hider_file = 
			fopen(strcat(strcat(strcat(temp, "/"), temp_header),".h"), "w");
	for(int j = 0; temp_header[j] != '\0'; j++) temp_header[j] 
										=  toupper(temp_header[j]);
	fprintf(hider_file, 
				"#ifndef %s\n"
				"#define %s\n\n"
				"#define PROJECT_NAME \"%s\"\n\n"
				"\t void greeting(void);\n\n"
				"#endif", strcat(temp_header, "_H"), temp_header, dir_name);
	return fclose(hider_file);
}

int add_row_file()
{
	char temp[AT_LEAST_SIGNIFICANT * 5] = {0};
	strcpy(temp, path); 	
	FILE* row_file = fopen(strcat(strcat(strcat(temp, "/"),header),".c"), "w");
	fprintf(row_file, 	"#include <stdio.h>\n\n"
						"#include \"%s.h\"\n\n\n"
						"void greeting(void)\n"
						"{\n"
						"\t printf(\"start project %%s\\n\", PROJECT_NAME);\n"
						"}\n"
						""
						,header);
	return fclose(row_file);
}

int add_makefile(const char* dir_name, const char* header_name)
{
	#define dn header
	char path[AT_LEAST_SIGNIFICANT * 2] = {0};
	strcpy(path, dir_name);
	char header[AT_LEAST_SIGNIFICANT * 2] = {0};
	strcpy(header, header_name);
	
	FILE* make = fopen(strcat(strcat(path, "/"), "makefile") ,"w");
	fprintf(make, 	"all : %s.out\n"
					"\t./%s.out\n\n" 
					"%s.out : *.o *.h\n" 
					"\tgcc *.o -o %s.out\n\n" 
					"*.o : *.c *.h\n" 
					"\tgcc -c *.c\n\n" 
					"clean :\n\trm *.o\n" 
					,dn,dn,dn,dn);
	fclose(make);
}
