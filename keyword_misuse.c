#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int line_number;
    char line_text[1024];
    int line_length;
} FileLine;

int is_keyword(const char *word)
{
    const char *keywords[] = {"for", "while", "if", "else", "switch", "case", "return"};
    int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < num_keywords; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void check_keyword_misuse(FileLine lines[], int total_lines, FILE *output_file)
{
    for (int i = 0; i < total_lines; i++)
    {
        char *line = lines[i].line_text;

        // Check misuse of 'for'
        if (strstr(line, "for"))
        {
            char *pos = strstr(line, "for");
            // Ensure 'for' is followed by '('
            if (pos[3] != '(' && !isspace(pos[3]))
            {
                fprintf(output_file, "Line %d: Misuse of 'for' keyword (missing '(' after 'for').\n", lines[i].line_number);
            }
        }

        // Check misuse of 'while'
        if (strstr(line, "while"))
        {
            char *pos = strstr(line, "while");
            if (pos[5] != '(' && !isspace(pos[5]))
            {
                fprintf(output_file, "Line %d: Misuse of 'while' keyword (missing '(' after 'while').\n", lines[i].line_number);
            }
        }

        // Check misuse of 'if'
        if (strstr(line, "if"))
        {
            char *pos = strstr(line, "if");
            if (pos[2] != '(' && !isspace(pos[2]))
            {
                fprintf(output_file, "Line %d: Misuse of 'if' keyword (missing '(' after 'if').\n", lines[i].line_number);
            }
        }
    }
}