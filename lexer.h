//Selyan Kablia et Nathan Lestrade

#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

typedef enum {
    TOKEN_PLUS,
    TOKEN_MULTIPLY,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_NUMBER,
    TOKEN_EOF
} TokenType;

typedef struct { // Structur for token representation
    TokenType type;
    double value;
} Token;

Token* tokenize(char* input); // Tokenize the input string

#endif /* LEXER_H */
