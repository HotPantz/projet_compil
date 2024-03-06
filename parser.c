// parser.c

#include "parser.h"
#include <stdio.h>
#include <stdbool.h>

// Tableau pour stocker les tokens analysés
TokenEntry tokenEntries[MAX_TOKENS];
int numTokens = 0;

// Fonction pour stocker les tokens analysés
void storeToken(TokenType type, float value) {
    TokenEntry entry;
    entry.type = type;
    entry.value = value;
    tokenEntries[numTokens++] = entry;
}

// Fonction pour parser une expression
void parseExpression() {
    Token token;

    // Réinitialiser le tableau des tokens
    numTokens = 0;

    // Analyser les tokens et les stocker
    while (true) {
        token = getNextToken();

        if (token.type == TOKEN_EOF || token.type == TOKEN_UNKNOWN) {
            // Fin de l'expression ou token inconnu
            break;
        }

        switch (token.type) {
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_MULTIPLY:
            case TOKEN_DIVIDE:
                storeToken(token.type, 0);
                break;
            case TOKEN_FLOAT:
            case TOKEN_INTEGER:
                storeToken(token.type, token.value);
                break;
            default:
                break;
        }
    }

    // Calculer le résultat final en utilisant les tokens stockés
    float result = 0;
    float currentOperand = 0;
    TokenType lastOperator = TOKEN_PLUS; // Opérateur initial

    for (int i = 0; i < numTokens; i++) {
        TokenEntry tokenEntry = tokenEntries[i];

        switch (tokenEntry.type) {
            case TOKEN_PLUS:
            case TOKEN_MINUS:
            case TOKEN_MULTIPLY:
            case TOKEN_DIVIDE:
                // Traiter l'opérateur précédent et mettre à jour le dernier opérateur
                switch (lastOperator) {
                    case TOKEN_PLUS:
                        result += currentOperand;
                        break;
                    case TOKEN_MINUS:
                        result -= currentOperand;
                        break;
                    case TOKEN_MULTIPLY:
                        result *= currentOperand;
                        break;
                    case TOKEN_DIVIDE:
                        if (currentOperand != 0) {
                            result /= currentOperand;
                        } else {
                            printf("Erreur : Division par zéro\n");
                            return;
                        }
                        break;
                    default:
                        break;
                }
                lastOperator = tokenEntry.type;
                currentOperand = 0;
                break;
            case TOKEN_FLOAT:
            case TOKEN_INTEGER:
                // Mettre à jour l'opérande courante
                currentOperand = tokenEntry.value;
                break;
            default:
                break;
        }
    }

    // Traiter le dernier opérande
    switch (lastOperator) {
        case TOKEN_PLUS:
            result += currentOperand;
            break;
        case TOKEN_MINUS:
            result -= currentOperand;
            break;
        case TOKEN_MULTIPLY:
            result *= currentOperand;
            break;
        case TOKEN_DIVIDE:
            if (currentOperand != 0) {
                result /= currentOperand;
            } else {
                printf("Erreur : Division par zéro\n");
                return;
            }
            break;
        default:
            break;
    }

    // Afficher le résultat final
    printf("Result: %.6f\n", result);
}
