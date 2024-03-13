//Selyan Kablia et Nathan Lestrade

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

Stack* createStack(int size) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(size * sizeof(int));
    stack->top = -1;
    stack->size = size;
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->top == stack->size - 1) {
        // stack is full, resize it
        stack->size *= 2;
        stack->data = (int*)realloc(stack->data, stack->size * sizeof(int));
    }
    stack->data[++stack->top] = value;
}

int pop(Stack* stack) {
    if (stack->top == -1) {
        // stack is empty, return error
        return -1;
    }
    return stack->data[stack->top--];
}

int parse(Token* tokens, int parsingTable[NUM_STATES][NUM_SYMBOLS], int gotoTable[NUM_STATES][3])
 {
    GrammarRule grammar[] = {
        { PROD_E_PLUS_T, 3},           // E -> E + T
        { PROD_E_T, 1 },               // E -> T
        { PROD_T_MUL_F, 3 },           // T -> T * F
        { PROD_T_F, 1 },               // T -> F
        { PROD_F_LPAREN_E_RPAREN, 3 }, // F -> (E)
        { PROD_F_VAL, 1 }              // F -> val
    };
    Stack* stack = createStack(100);
    Stack* act = createStack(100);
    
    // push the initial state
    push(stack, 0);
    push(act, 0);

    int i = 0;
    while (1) {
        int state = stack->data[stack->top];

        Token token = tokens[i];
        if(token.type == TOKEN_NUMBER) { 
            push(stack, token.value);
        }
        else {
            push(stack, token.type);
        }

        printf("Current state: %d\n", state);
        printf("Current token type: %d\n", token.type);

        // lookup the action in the parsing table based on the current state and token
        int action = parsingTable[state][(-1) * token.type];


        printf("Action: %d\n", action);

        switch (action) {
            case D4:
                // shift
                push(stack, action);
                ++i;
                break;
            case D5:
                // shift 
                push(stack, action);
                ++i;
                break;
            case D6:
                // shift
                push(stack, action);
                ++i;
                break;
            case D7:
                // shift
                push(stack, action);
                ++i;
                break;
            case D11:
                // shift
                push(stack, action);
                ++i;
                break;
            case ACC:
                // accept
                // print the contents of the stack
                printf("Stack contents: ");
                for (int j = 0; j <= stack->top; ++j) {
                    printf("%d ", stack->data[j]);
                }
                printf("\n");
                free(stack->data);
                free(stack);
                free(act->data);
                free(act);
                return 0;
            case R1: {
                // reduce
                GrammarRule rule = grammar[0]; // use the grammar here
                for (int j = 0; j < 2*rule.length+1; ++j) {       //on fait 2*rule.length car on a besoin de pop 2 fois plus de tokens que la longueur de la règle puisque qu'il y a les tokens et les états
                    pop(stack);
                }
                // check if the stack is empty
                if (stack->top == -1) {
                    // stack is empty, return error
                    printf("Syntax error: unexpected end of input\n");
                    free(stack->data);
                    free(stack);
                    return -1;
                }
                // push the new state based on the left-hand side of the rule and the current state
                int newState = gotoTable[stack->data[stack->top]][E-E];
                push(stack, E);
                push(stack, newState);
                break;
            }
            case R2: {
                // reduce
                GrammarRule rule = grammar[1]; // use the grammar here
                for (int j = 0; j < 2*rule.length+1; ++j) {
                    pop(stack);
                }
                // check if the stack is empty
                if (stack->top == -1) {
                    // stack is empty, return error
                    printf("Syntax error: unexpected end of input\n");
                    free(stack->data);
                    free(stack);
                    return -1;
                }
                // push the new state based on the left-hand side of the rule and the current state
                int newState = gotoTable[stack->data[stack->top]][E-E];
                push(stack, E);
                push(stack, newState);
                break;
            }
            case R3: {
                // reduce
                GrammarRule rule = grammar[2]; // use the grammar here
                for (int j = 0; j < 2*rule.length+1; ++j) {
                    pop(stack);
                }
                // check if the stack is empty
                if (stack->top == -1) {
                    // stack is empty, return error
                    printf("Syntax error: unexpected end of input\n");
                    free(stack->data);
                    free(stack);
                    return -1;
                }
                // push the new state based on the left-hand side of the rule and the current state
                int newState = gotoTable[stack->data[stack->top]][T-E];
                push(stack, T);
                push(stack, newState);
                break;
            }
            case R4: {
                // reduce
                GrammarRule rule = grammar[3]; // use the grammar here
                for (int j = 0; j < 2*rule.length+1; ++j) {
                    pop(stack);
                }
                // check if the stack is empty
                if (stack->top == -1) {
                    // stack is empty, return error
                    printf("Syntax error: unexpected end of input\n");
                    free(stack->data);
                    free(stack);
                    return -1;
                }
                // push the new state based on the left-hand side of the rule and the current state
                int newState = gotoTable[stack->data[stack->top]][T-E];
                push(stack, T);
                push(stack, newState);
                break;
            }
            case R5: {
                // reduce
                GrammarRule rule = grammar[4]; // use the grammar here
                for (int j = 0; j < 2*rule.length+1; ++j) {
                    pop(stack);
                }
                // check if the stack is empty
                if (stack->top == -1) {
                    // stack is empty, return error
                    printf("Syntax error: unexpected end of input\n");
                    free(stack->data);
                    free(stack);
                    return -1;
                }
                // push the new state based on the left-hand side of the rule and the current state
                int newState = gotoTable[stack->data[stack->top]][F-E];
                push(stack, F);
                push(stack, newState);
                break;
            }
            case R6: {
                // reduce
                GrammarRule rule = grammar[5]; // use the grammar here
                printf("rule.length = %d\n", rule.length);
                for (int j = 0; j < 2*rule.length+1; ++j) {
                    printf("1 tour de boucle\n");
                    pop(stack);
                }
                // check if the stack is empty
                if (stack->top == -1) {
                    // stack is empty, return error
                    printf("Syntax error: unexpected end of input\n");
                    free(stack->data);
                    free(stack);
                    return -1;
                }
                // push the new state based on the left-hand side of the rule and the current state
                int newState = gotoTable[stack->data[stack->top]][F-E];
                printf("state = %d | newState = %d\n", stack->data[stack->top], newState);
                push(stack, F);
                push(stack, newState);
                break;
            }
            default:
                // error
                printf("Syntax error\n");
                printf("action = %d\n", action);
                free(stack->data);
                free(stack);
                return -1;
        }
    }
}
