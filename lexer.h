#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

// Enum for token types
typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_EOL,
    TOKEN_UNKNOWN
} TokenType;

// Structure for tokens
typedef struct {
    TokenType type;
    double value;
} Token;

// Function to get the next token
Token getNextToken();

#endif /* LEXER_H */
