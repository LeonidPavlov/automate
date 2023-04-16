
main_file_content="\
#include <gtk/gtk.h>\n\n\
static void activate(GtkApplication *app, gpointer user_data)\n{\n\t\
GtkWidget *window = gtk_application_window_new(app);\n\t\
gtk_window_set_title(GTK_WINDOW(window), \"$HEADER\");\n\t\
gtk_widget_show(window);\n\
\n}\n\n\
int main(int argc, char *argv[])\n{\n\t\
int status = 0;\n\t\
GtkApplication *app;\n\t\
app = gtk_application_new(\"org.gtk.$header\", G_APPLICATION_FLAGS_NONE);\n\t\
g_signal_connect(app, \"activate\", G_CALLBACK(activate), NULL);\n\t\
status = g_application_run(G_APPLICATION(app), argc, argv);\n\t\
g_object_unref(app);\n\t\
return status;\n\
}\n\
"

makefile_content="\
flags=\`pkg-config --cflags gtk4\`\n\
libs=\`pkg-config --libs gtk4\`\n\
file=$header\n\n\
all : dist/\${file}.out\n\
\t./dist/\${file}.out\n\n\
dist/\${file}.out : \${file}.o\n\
\tgcc \${flags} \${file}.o \${libs} -o dist/\${file}.out\n\n\
\${file}.o : \${file}.c\n\
\tgcc \${flags} -c \${file}.c \${libs}\n\n\
clear :\n\
\trm -rf *.o *.out\n\
"



