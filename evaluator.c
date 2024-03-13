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
    bool hasLastNumber = false, second_iteration = false;
    TokenType last_token_type = 6;  //on initialise à une valeur qui ne correspond à aucun type de token


    for (int i = 0; tokens[i].type != TOKEN_EOF; ++i) {
        switch (tokens[i].type) {
            case TOKEN_NUMBER:
                lastNumber = tokens[i].value;
                hasLastNumber = true;
                break;
            case TOKEN_PLUS:
                if (hasLastNumber) {
                    push(stack, lastNumber);  //si on tombe sur une opération, on push sur la stack la première opérande (aka la token.value du token précédent) 
                    hasLastNumber = false;
                }
                last_token_type = tokens[i].type;  //on enregistre le type du token de l'opération pour pouvoir l'effectuer au prochain tour de boucle
                break;
            case TOKEN_MULTIPLY:
                if (hasLastNumber) {
                    push(stack, lastNumber);
                    hasLastNumber = false;
                }
                last_token_type = tokens[i].type;
                break;
            default:
                // Ignorer les autres types de token
                break;
        }


        //printf("au tour de boucle %d, hasLastNumber = %d | second_iteration = %d | last_token_type = %u\n", i, hasLastNumber, second_iteration, last_token_type);
        // Si on a rencontré un opérateur on passe le bool second_iteration à true pour pouvoir effectuer l'opération au prochain tour de boucle lorsqu'on aura push la deuxième opérande sur la stack
        if ((!hasLastNumber || second_iteration) && (tokens[i].type == TOKEN_PLUS || tokens[i].type == TOKEN_MULTIPLY || last_token_type == 0 || last_token_type == 1)) {
            if (!second_iteration) {
                second_iteration = true;
            }
            else {
                if (hasLastNumber) {
                    push(stack, lastNumber);  //si l'avant-dernier token est un opérateur, on push la dernière opérande sur la stack
                    hasLastNumber = false;
                }
                double operand1 = pop(stack);
                double operand2 = pop(stack);
                switch (last_token_type) {
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
    }

    // Retourner le résultat final
    double result = pop(stack);
    free(stack->data);
    free(stack);
    return result;
}
