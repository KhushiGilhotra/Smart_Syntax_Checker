#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS_PER_LINE 100
#define MAX_TOKEN_LENGTH 50

typedef struct {
    char tokens[MAX_TOKENS_PER_LINE][MAX_TOKEN_LENGTH];
    int token_count;
} TokenizedLine;

void tokenize_line(char *line, TokenizedLine *tline) {
    int len = strlen(line);
    int token_index = 0;
    int current_length = 0;
    char current_token[MAX_TOKEN_LENGTH] = {0};

    for (int i = 0; i <= len; i++) {
        char c = line[i];

        if (isspace(c) || c == '\0' || strchr("(){};,=+-/*<>!&|[]\"", c)) {
            if (current_length > 0) {
                current_token[current_length] = '\0';
                strcpy(tline->tokens[token_index++], current_token);
                current_length = 0;
            }
            if (c != '\0' && !isspace(c)) {
                char sym[2] = {c, '\0'};
                strcpy(tline->tokens[token_index++], sym);
            }
        } else {
            if (current_length < MAX_TOKEN_LENGTH - 1) {
                current_token[current_length++] = c;
            }
        }
    }
    tline->token_count = token_index;
}

void print_tokens(char *line) {
    TokenizedLine tline;
    tokenize_line(line, &tline);

    printf("Tokens:\n");
    for (int i = 0; i < tline.token_count; i++) {
        printf("'%s'\n", tline.tokens[i]);
    }
}
