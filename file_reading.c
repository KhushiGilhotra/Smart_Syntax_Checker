#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int line_number;
    int line_length;
    char line_text[1024];
} FileLine;

int find_comment_position(char line[], int line_length) {
    for (int i = 0; i < line_length - 1; i++) {
        if (line[i] == '/' && line[i + 1] == '/') {
            return i;
        }
    }
    return -1;
}

FileLine* read_file(const char *filename, int *total_lines) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    int capacity = 100;
    *total_lines = 0;
    FileLine lines = (FileLine)malloc(capacity * sizeof(FileLine));
    if (!lines) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        int length = strlen(buffer);
        int comment_pos = find_comment_position(buffer, length);

        if (*total_lines >= capacity) {
            capacity *= 2;
            lines = (FileLine*)realloc(lines, capacity * sizeof(FileLine));
            if (!lines) {
                printf("Error: Memory reallocation failed\n");
                fclose(file);
                return NULL;
            }
        }

        lines[*total_lines].line_number = *total_lines + 1;
        if (comment_pos == -1) {
            strcpy(lines[*total_lines].line_text, buffer);
            lines[*total_lines].line_length = length;
        } else {
            strncpy(lines[*total_lines].line_text, buffer, comment_pos);
            lines[*total_lines].line_text[comment_pos] = '\0';
            lines[*total_lines].line_length = comment_pos;
        }

        (*total_lines)++;
    }

    fclose(file);
    return lines;
}