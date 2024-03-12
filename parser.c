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

        printf("Current state: %d\n", state);
        printf("Current token type: %d\n", token.type);
        
        // lookup the action in the parsing table based on the current state and token
        int action = parsingTable[state][token.type];

        printf("Action: %d\n", action);

        if (action > 0) {
            // shift
            printf("Shifting...\n");
            push(stack, action);
            ++i;
        } else if (action < 0) {
            // reduce
            printf("Reducing...\n");
            GrammarRule rule = grammar[-action - 1]; // use the grammar here
            for (int j = 0; j < rule.length; ++j) {
                pop(stack);
            }
            // check if the stack is empty
            if (stack->top == -1) {
                // stack is empty, return error
                printf("Syntax error: unexpected end of input\n");
                return -1;
            }
            // push the new state based on the left-hand side of the rule and the current state
            push(stack, gotoTable[stack->data[stack->top]]); // use followOfE here
        } else if (action == 0) {
            // accept
            printf("Accepted!\n");
            break;
        } else {
            // error
            printf("Syntax error\n");
            return -1;
        }
    }

    free(stack->data);
    free(stack);
    return 0;
}
