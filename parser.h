// parser.h

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Définition de la taille maximale du tableau de tokens
#define MAX_TOKENS 100

// Structure pour représenter une entrée de token
typedef struct {
    TokenType type;
    float value; // Utilisé pour les tokens de type FLOAT et INTEGER
} TokenEntry;

// Déclaration des fonctions
void parseExpression();
void storeToken(TokenType type, float value);

#endif /* PARSER_H */
