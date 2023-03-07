#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define  AT_LEAST_SIGNIFICANT 32

char dir_name[AT_LEAST_SIGNIFICANT] = {0};
char header[AT_LEAST_SIGNIFICANT] = {0};

void handle_args(int argc, char * argv[]);
void project(const char * name);
void file(const char* anme);
void extact_header(void);
int add_main(const char* dir_name, const char* header);
int add_header(const char* dir_name, const char* header);
int add_row_file(const char* dir_name, const char* header);
int add_makefile(const char* dir_name, const char* header);

int main(int argc, char * argv[])
{
	puts("USAGE -> ./template.out and\n"
						"[FILENAME or PROJECT_NAME without extension]"
						"[WORD project, if project]\n"
						"[PATH if somwhere other place]\n");
	puts("without arguments will be create file sample.c");
	handle_args(argc, argv);
	return EXIT_SUCCESS;
}

void handle_args(int argc, char * argv[])
{
	if (argc == 1) file("sample");
	if (argc == 2) file(argv[1]); 
	if (argc == 3 && strcmp(argv[2],"project") == 0) project(argv[1]);  
}

void project(const char * name)
{
	strcpy(dir_name, name);
	extact_header();
	printf("created project in directory -> %s header -> %s\n", 
															dir_name, header);

	// int child_pid  = fork();
	// if(child_pid == 0) execl("/usr/bin/mkdir","/usr/bin/mkdir", dir_name, NULL);
	// if (wait(&child_pid)) printf("add main file -> %d\n", 
	// 											add_main(dir_name, header));
	// printf("header file -> %d\n", add_header(dir_name, header));
	// printf("row file -> %d\n", add_row_file(dir_name, header));
	// printf("makefile -> %d\n", add_makefile(dir_name, header));
	// strcpy(dir_name, "cd ");
	// strcat(dir_name, name);
	// strcat(dir_name, " && make");
	// system(dir_name);
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

void file(const char * name)
{
	char * one_file_content = "#include <stdio.h>\n#include <stdlib.h>\n\n"
						"int main(int argc, char *argv[])\n{\n\n\t"
						"return EXIT_SUCCESS;\n}\n";
	strcpy(dir_name, name);
	FILE* file = fopen(strcat(dir_name, ".c"), "w");
	fprintf(file, "%s", one_file_content);
	fclose(file);
}

int add_main(const char* dir_name, const char* header)
{
	char path[AT_LEAST_SIGNIFICANT * 2] = {0};
	strcpy(path, dir_name);
	strcat(strcat(path, "/"), "main");
	FILE* main = fopen(strcat(path, ".c"), "w");
	fprintf(main,	"#include <stdio.h>\n"
					"#include <stdlib.h>\n\n"
					"#include \"%s.h\"\n\n\n"
					"int main(int argc, char* argv[])\n{\n"
					"\tgreeting();\n"
					"\treturn EXIT_SUCCESS;\n}\n", header);
	return fclose(main);
}

int add_header(const char* dir_name, const char* header_name)
{
	char path[AT_LEAST_SIGNIFICANT * 2] = {0};
	char header[AT_LEAST_SIGNIFICANT * 2] = {0};
	strcpy(path, dir_name);
	strcpy(header, header_name);
	FILE* hider_file = fopen(strcat(strcat(strcat(path, "/"), header),".h"), "w");
	strcpy(path, dir_name);
	for(int j = 0; header[j] != '\0'; j++) header[j] =  toupper(header[j]);
	fprintf(hider_file, 
				"#ifndef %s\n"
				"#define %s\n\n"
				"#define PROJECT_NAME \"%s\"\n\n"
				"\t void greeting(void);\n\n"
				"#endif", strcat(header, "_H"), header, dir_name);
	return fclose(hider_file);
}

int add_row_file(const char* dir_name, const char* header_name)
{
	char path[AT_LEAST_SIGNIFICANT * 2] = {0};
	char header[AT_LEAST_SIGNIFICANT * 2] = {0};
	strcpy(path, dir_name);
	strcpy(header, header_name);
	FILE* row_file = fopen(strcat(strcat(strcat(path, "/"),header),".c"), "w");
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
