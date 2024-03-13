//Selyan Kablia et Nathan Lestrade

#ifndef LEXER_H
#define LEXER_H

#define TOKEN_PLUS -1
#define TOKEN_MULTIPLY -2
#define TOKEN_LPAREN -3
#define TOKEN_RPAREN -4
#define TOKEN_NUMBER -5
#define TOKEN_EOF -6

#include <stdbool.h>

typedef struct { // Structur for token representation
    int type;
    double value;
} Token;

Token* tokenize(char* input); // Tokenize the input string

#endif /* LEXER_H */
