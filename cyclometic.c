#include <stdio.h>
#include <string.h>
#include "fileline.h"

int calculate_cyclomatic_complexity(FileLine lines[], int total_lines) {
    int complexity = 1; // start with 1

    for (int i = 0; i < total_lines; i++) {
        char *line = lines[i].line_text;

        if (strstr(line, "if") || strstr(line, "else if") || strstr(line, "for") ||
            strstr(line, "while") || strstr(line, "case") || strstr(line, "default") ||
            strstr(line, "&&") || strstr(line, "||")) {
            complexity++;
        }
    }
    return complexity;
}

// Example usage
void print_cyclomatic_complexity(FileLine lines[], int total_lines, FILE *output_file) {
    int complexity = calculate_cyclomatic_complexity(lines, total_lines);
    fprintf(output_file, "Cyclomatic Complexity: %d\n", complexity);
}
