#include <stdio.h>
#include <string.h>

typedef struct {
    int line_number;
    int line_length;
    char line_text[1024];
} FileLine;

void check_semicolons(FileLine lines[], int total_lines, FILE *output_file) {
    for (int i = 0; i < total_lines; i++) {
        // Skip empty lines
        if (lines[i].line_length == 0 || lines[i].line_text[0] == '\n') continue;

        // If line doesn't contain ';' and is not control structure or bracket line, report missing semicolon
        if (!strchr(lines[i].line_text, ';') &&
            !strstr(lines[i].line_text, "for") &&
            !strstr(lines[i].line_text, "while") &&
            !strstr(lines[i].line_text, "if") &&
            !strstr(lines[i].line_text, "else") &&
            !strstr(lines[i].line_text, "{") &&
            !strstr(lines[i].line_text, "}")) {
                fprintf(output_file, "Line %d: Missing semicolon\n", lines[i].line_number);
        }
    }
}