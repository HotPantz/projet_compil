#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

static const char *input_ptr;

// Fonction pour obtenir le prochain token
Token getNextToken() {
    Token token;
    char buffer[20];
    int i = 0;

    // Ignorer les espaces
    while (isspace(*input_ptr)) {
        input_ptr++;
    }

    // Fin de la saisie
    if (*input_ptr == '\0') {
        token.type = TOKEN_EOF;
        return token;
    }

    // Identifier le type de token
    switch (*input_ptr) {
        case '+':
            token.type = TOKEN_PLUS;
            input_ptr++;
            return token;
        case '-':
            token.type = TOKEN_MINUS;
            input_ptr++;
            return token;
        case '*':
            token.type = TOKEN_MULTIPLY;
            input_ptr++;
            return token;
        case '/':
            token.type = TOKEN_DIVIDE;
            input_ptr++;
            return token;
        case '(':
            token.type = TOKEN_LPAREN;
            input_ptr++;
            return token;
        case ')':
            token.type = TOKEN_RPAREN;
            input_ptr++;
            return token;
    }

    // Lire les nombres flottants ou entiers
    while (isdigit(*input_ptr) || *input_ptr == '.') {
        buffer[i++] = *input_ptr++;
    }
    buffer[i] = '\0';

    // Convertir le buffer en float
    token.type = TOKEN_FLOAT;
    token.value = atof(buffer); // Conversion du buffer en float

    return token;
}

// Fonction pour définir la nouvelle entrée
void setInput(const char *input) {
    input_ptr = input;
}
