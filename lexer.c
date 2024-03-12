#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>


Token* tokenize(char* input) {
    size_t inputLength = strlen(input);
    Token* tokens = malloc(sizeof(Token) * (inputLength + 1)); // +1 for TOKEN_EOF
    size_t tokenCount = 0;

    for (size_t i = 0; i < inputLength; ++i) {
        if (isspace(input[i])) {
            continue;
        } else if (isdigit(input[i])) {
            tokens[tokenCount].type = TOKEN_NUMBER;
            char* end;
            tokens[tokenCount].value = strtod(&input[i], &end);
            i = end - input - 1; // update i to the position where the number ends
        } else {
            switch (input[i]) {
                case '+': tokens[tokenCount].type = TOKEN_PLUS; break;
                case '*': tokens[tokenCount].type = TOKEN_MULTIPLY; break;
                case '(': tokens[tokenCount].type = TOKEN_LPAREN; break;
                case ')': tokens[tokenCount].type = TOKEN_RPAREN; break;
                default: /* handle error */ break;
            }
            tokens[tokenCount].value = 0;
        }
        ++tokenCount;
    }

    tokens[tokenCount].type = TOKEN_EOF;
    tokens[tokenCount].value = 0;

    return tokens;
}