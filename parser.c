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
            case TOKEN_LPAREN:
            case TOKEN_RPAREN:
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
    float currentTerm = 0;
    float currentFactor = 1; // Facteur initial
    TokenType lastOperator = TOKEN_PLUS; // Opérateur initial

    for (int i = 0; i < numTokens; i++) {
        TokenEntry tokenEntry = tokenEntries[i];

        switch (tokenEntry.type) {
            case TOKEN_PLUS:
            case TOKEN_MINUS:
                // Traiter l'opérateur précédent
                switch (lastOperator) {
                    case TOKEN_PLUS:
                        result += currentTerm * currentFactor;
                        break;
                    case TOKEN_MINUS:
                        result -= currentTerm * currentFactor;
                        break;
                    default:
                        break;
                }
                currentTerm = 0;
                currentFactor = 1;
                lastOperator = tokenEntry.type;
                break;
            case TOKEN_MULTIPLY:
            case TOKEN_DIVIDE:
                // Mettre à jour le facteur courant pour la multiplication et la division
                if (tokenEntry.type == TOKEN_MULTIPLY) {
                    currentFactor *= tokenEntries[++i].value;
                } else {
                    if (tokenEntries[++i].value != 0) {
                        currentFactor /= tokenEntries[i].value;
                    } else {
                        printf("Erreur : Division par zéro\n");
                        return;
                    }
                }
                break;
            case TOKEN_FLOAT:
            case TOKEN_INTEGER:
                // Mettre à jour le terme courant
                currentTerm = tokenEntry.value;
                break;
            case TOKEN_LPAREN:
                {
                    // Trouver l'index correspondant de la parenthèse fermante
                    int closingParenIndex = i + 1;
                    int depth = 1;
                    while (closingParenIndex < numTokens && depth > 0) {
                        if (tokenEntries[closingParenIndex++].type == TOKEN_LPAREN) {
                            depth++;
                        } else if (tokenEntries[closingParenIndex - 1].type == TOKEN_RPAREN) {
                            depth--;
                        }
                    }
                    // Extraire les tokens entre les parenthèses et récursivement évaluer l'expression
                    TokenEntry subExpression[MAX_TOKENS];
                    int subExpressionLength = closingParenIndex - i - 2;
                    for (int j = i + 1; j < closingParenIndex - 1; j++) {
                        subExpression[j - i - 1] = tokenEntries[j];
                    }
                    numTokens = i; // Réinitialiser numTokens pour évaluer uniquement la sous-expression
                    for (int j = 0; j < subExpressionLength; j++) {
                        tokenEntries[j] = subExpression[j];
                    }
                    parseExpression(); // Évaluer récursivement la sous-expression
                    i = closingParenIndex - 2; // Avancer l'index de l'expression principale jusqu'à la parenthèse fermante
                }
                break;
            default:
                break;
        }
    }

    // Traiter le dernier terme
    switch (lastOperator) {
        case TOKEN_PLUS:
            result += currentTerm * currentFactor;
            break;
        case TOKEN_MINUS:
            result -= currentTerm * currentFactor;
            break;
        default:
            break;
    }

    // Afficher le résultat final
    printf("Result: %.6f\n", result);
}
