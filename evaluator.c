#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "evaluator.h"



// Fonction pour évaluer une expression
double evaluateExpression(Token* tokens) {
    Stack* stack = createStack(100);

    for (int i = 0; tokens[i].type != TOKEN_EOF; ++i) {
        switch (tokens[i].type) {
            case TOKEN_NUMBER:
                push(stack, tokens[i].value);
                break;
            case TOKEN_PLUS: {
                double operand2 = pop(stack);
                double operand1 = pop(stack);
                push(stack, operand1 + operand2);
                break;
            }
            case TOKEN_MULTIPLY: {
                double operand2 = pop(stack);
                double operand1 = pop(stack);
                push(stack, operand1 * operand2);
                break;
            }
            default:
                // Ignorer les autres types de token
                break;
        }
    }

    double result = pop(stack);
    free(stack->data);
    free(stack);
    return result;
}