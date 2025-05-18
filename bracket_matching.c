#include <stdio.h>

typedef struct {
    int line_number;
    int line_length;
    char line_text[1024];
} FileLine;

void check_brackets(FileLine lines[], int total_lines, FILE *output_file) {
    int curly_open = 0, curly_close = 0;
    int round_open = 0, round_close = 0;
    int square_open = 0, square_close = 0;

    for (int i = 0; i < total_lines; i++) {
        for (int j = 0; j < lines[i].line_length; j++) {
            char c = lines[i].line_text[j];
            if (c == '{') curly_open++;
            else if (c == '}') curly_close++;
            else if (c == '(') round_open++;
            else if (c == ')') round_close++;
            else if (c == '[') square_open++;
            else if (c == ']') square_close++;
        }
    }

    if (curly_open != curly_close) {
        fprintf(output_file, "Error: Mismatched curly brackets '{' and '}' detected.\n");
    } else {
        fprintf(output_file, "Curly brackets are balanced.\n");
    }

    if (round_open != round_close) {
        fprintf(output_file, "Error: Mismatched round brackets '(' and ')' detected.\n");
    } else {
        fprintf(output_file, "Round brackets are balanced.\n");
    }

    if (square_open != square_close) {
        fprintf(output_file, "Error: Mismatched square brackets '[' and ']' detected.\n");
    } else {
        fprintf(output_file, "Square brackets are balanced.\n");
    }
}