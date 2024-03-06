// lexer.h

#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>

// Définition des types de tokens
typedef enum {
    TOKEN_UNKNOWN,
    TOKEN_EOF,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_FLOAT,
    TOKEN_INTEGER // Nouveau type pour les nombres entiers
} TokenType;

// Structure pour représenter un token
typedef struct {
    TokenType type;
    float value; // Utilisé pour les tokens de type FLOAT
    int integer_value; // Nouveau champ pour les tokens de type INTEGER
} Token;

// Déclaration des fonctions
Token getNextToken();
void setInput(const char *input);

#endif /* LEXER_H */
