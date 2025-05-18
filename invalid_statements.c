#include <string.h>
#include <ctype.h>
#include <stdio.h>

typedef struct
{
    int line_number;
    char line_text[1024];
    int line_length;
} FileLine;

int is_comment_or_empty(char *line)
{
    for (int i = 0; line[i]; i++)
    {
        if (!isspace(line[i]))
        {
            if (line[i] == '/' && (line[i + 1] == '/' || line[i + 1] == '*'))
                return 1;
            return 0;
        }
    }
    return 1;
}

int ends_with_semicolon(char *line)
{
    int len = strlen(line);
    if (len == 0)
        return 0;

    int i = len - 1;
    while (i >= 0 && isspace(line[i]))
        i--;

    return (i >= 0 && line[i] == ';');
}

void check_invalid_statements(FileLine lines[], int total_lines, FILE *output_file)
{
    for (int i = 0; i < total_lines; i++)
    {
        char *line = lines[i].line_text;

        if (is_comment_or_empty(line))
            continue;

        if (strchr(line, '{') || strchr(line, '}') ||
            strstr(line, "for") || strstr(line, "while") ||
            strstr(line, "if") || strstr(line, "else"))
            continue;

        if (!ends_with_semicolon(line))
        {
            fprintf(output_file, "Line %d: Invalid statement (missing semicolon or incomplete statement).\n", lines[i].line_number);
        }
    }
}
