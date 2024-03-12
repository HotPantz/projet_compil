//Selyan Kablia et Nathan Lestrade

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "evaluator.h"



// Fonction pour évaluer une expression
double evaluateExpression(Token* tokens) {
    Stack* stack = createStack(100);
    double lastNumber = 0.0;
    bool hasLastNumber = false;

    for (int i = 0; tokens[i].type != TOKEN_EOF; ++i) {
        switch (tokens[i].type) {
            case TOKEN_NUMBER:
                lastNumber = tokens[i].value;
                printf("lastnumb %f ", lastNumber);
                hasLastNumber = true;
                break;
            case TOKEN_PLUS:
                if (hasLastNumber) {
                    push(stack, lastNumber);
                    hasLastNumber = false;
                }
                // Pas besoin de faire quoi que ce soit pour l'addition, elle sera effectuée au prochain tour de boucle
                break;
            case TOKEN_MULTIPLY:
                if (hasLastNumber) {
                    push(stack, lastNumber);
                    hasLastNumber = false;
                }
                // Pas besoin de faire quoi que ce soit pour la multiplication, elle sera effectuée au prochain tour de boucle
                break;
            default:
                // Ignorer les autres types de token
                break;
        }

        // Si on a rencontré un opérateur, et qu'il y a déjà un dernier nombre dans la pile, effectuer l'opération
        if (!hasLastNumber && (tokens[i].type == TOKEN_PLUS || tokens[i].type == TOKEN_MULTIPLY)) {
            double operand1 = pop(stack);
            double operand2 = pop(stack);

            printf("op1 %f op2 %f ", operand1, operand2);
            printf("lastNumber: %f\n", lastNumber);
            switch (tokens[i].type) {
                case TOKEN_PLUS:
                    push(stack, operand1 + operand2);
                    break;
                case TOKEN_MULTIPLY:
                    push(stack, operand1 * operand2);
                    break;
                default:
                    break;
            }
        }
    }

    // Retourner le résultat final
    double result = pop(stack);
    free(stack->data);
    free(stack);
    return result;
}
