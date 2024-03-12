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
        printf("top: %d\n", stack->top);

        
        
        Token token = tokens[i];
        token.type++;
        printf("Current token: %d\n", token.type);
        printf("Current token value: %f\n", token.value);
        printf("Current state: %d\n", state);
        printf("Stack: ");
        for (int j = 0; j <= stack->top; ++j) {
            printf("%d ", stack->data[j]);
        }
        printf("\n");

        // lookup the action in the parsing table based on the current state and token
        int action = parsingTable[state][token.type];

        printf("Action: %d\n", action);

        switch (action) {
            case D2:
                // shift
                printf("Shifting...\n");
                push(stack, action);
                ++i;
                break;
            case D3:
                // shift
                printf("Shifting...\n");
                push(stack, action);
                ++i;
                break;
            case D4:
                // shift
                printf("Shifting...\n");
                push(stack, action);
                ++i;
                break;
            case D5:
                // shift
                printf("Shifting...\n");
                push(stack, action);
                ++i;
                break;
            case D9:
                // shift
                printf("Shifting...\n");
                push(stack, action);
                ++i;
                break;
            case ACC:
                // accept
                printf("Accepted!\n");
                free(stack->data);
                free(stack);
                return 0;
            case R1: {
                // reduce
                printf("Reducing...\n");
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
                printf("Reducing...\n");
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
                printf("Reducing...\n");
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
                printf("Reducing...\n");
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
