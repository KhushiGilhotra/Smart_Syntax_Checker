#include <stdio.h>
#include <string.h>
#include "fileline.h"  

int is_valid_function_syntax(char *line);
int is_valid_variable_declaration(char *line);

void count_functions_and_prototypes(FileLine lines[], int total_lines, FILE *output_file) {
    int function_count = 0;
    int prototype_count = 0;

    for (int i = 0; i < total_lines; i++) {
        char *line = lines[i].line_text;

        if (is_valid_function_syntax(line)) {
            function_count++;
            fprintf(output_file, "Line %d: Valid function definition detected\n", lines[i].line_number);
        } else if (is_valid_variable_declaration(line)) {
            prototype_count++;
            fprintf(output_file, "Line %d: Variable declaration detected\n", lines[i].line_number);
        }
    }

    fprintf(output_file, "Total functions: %d\n", function_count);
    fprintf(output_file, "Total variable declarations: %d\n", prototype_count);
}

int is_valid_function_syntax(char *line) {
    return strstr(line, "(") && strstr(line, ")") && strstr(line, "{");
}

int is_valid_variable_declaration(char *line) {
    return strstr(line, ";") && (strstr(line, "int ") || strstr(line, "float ") || strstr(line, "char "));
}
