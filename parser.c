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

int parse(Token* tokens, int parsingTable[NUM_STATES][NUM_SYMBOLS], int gotoTable[NUM_STATES]) {
    GrammarRule grammar[] = {
        { PROD_E_PLUS_E, 3 },      // E -> E + E
        { PROD_E_MUL_E, 3 },       // E -> E * E
        { PROD_LPAREN_E_RPAREN, 3 }, // E -> (E)
        { PROD_VAL, 1 }            // E -> val
    };
    Stack* stack = createStack(100);
    push(stack, 0); // push the initial state

    int i = 0;
    while (1) {
        int state = stack->data[stack->top];

        
        
        Token token = tokens[i];
        token.type++;

        // lookup the action in the parsing table based on the current state and token
        int action = parsingTable[state][token.type];


        switch (action) {
            case D2:
                // shift
                push(stack, action);
                ++i;
                break;
            case D3:
                // shift
                push(stack, action);
                ++i;
                break;
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
            case D9:
                // shift
                push(stack, action);
                ++i;
                break;
            case ACC:
                // accept
                printf("")
                free(stack->data);
                free(stack);
                return 0;
            case R1: {
                // reduce
                GrammarRule rule = grammar[0]; // use the grammar here
                for (int j = 0; j < rule.length; ++j) {
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
                int newState = gotoTable[stack->data[stack->top]];
                push(stack, newState); // use followOfE here
                break;
            }
            case R2: {
                // reduce
                GrammarRule rule = grammar[1]; // use the grammar here
                for (int j = 0; j < rule.length; ++j) {
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
                int newState = gotoTable[stack->data[stack->top]];
                push(stack, newState); // use followOfE here
                break;
            }
            case R3: {
                // reduce
                GrammarRule rule = grammar[2]; // use the grammar here
                for (int j = 0; j < rule.length; ++j) {
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
                int newState = gotoTable[stack->data[stack->top]];
                push(stack, newState); // use followOfE here
                break;
            }
            case R4: {
                // reduce
                GrammarRule rule = grammar[3]; // use the grammar here
                for (int j = 0; j < rule.length; ++j) {
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
                int newState = gotoTable[stack->data[stack->top]];
                push(stack, newState); // use followOfE here
                break;
            }
            default:
                // error
                printf("Syntax error\n");
                free(stack->data);
                free(stack);
                return -1;
        }
    }
}
