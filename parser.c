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


// Function to evaluate the stack input and calculate the final result
int evaluate(Stack* input) {
    Stack* tmp = createStack(100);
    Stack* evalStack = createStack(100);
    int element;
    while (input->top >= 0) {       // while loop to reverse the order of tokens in the input stack
        element = pop(input);
        push(tmp, element);
    }
        
    while (tmp->top >= 0) {
        element = pop(tmp);

        if (element >= 0) {
            // Operand
            push(evalStack, element);
        } else {
            // Operator
            switch (element) {
                case -1:
                    // Addition
                    if (evalStack->top < 1) {
                        printf("Syntax error: insufficient operands for addition\n");
                        free(evalStack->data);
                        free(evalStack);
                        return -1;
                    }
                    int operand2 = pop(evalStack);
                    int operand1 = pop(evalStack);
                    push(evalStack, operand1 + operand2);
                    break;
                case -2:
                    // Multiplication
                    if (evalStack->top < 1) {
                        printf("Syntax error: insufficient operands for multiplication\n");
                        free(evalStack->data);
                        free(evalStack);
                        return -1;
                    }
                    operand2 = pop(evalStack);
                    operand1 = pop(evalStack);
                    push(evalStack, operand1 * operand2);
                    break;
                default:
                    printf("Syntax error: unknown operator\n");
                    free(evalStack->data);
                    free(evalStack);
                    return -1;
            }
        }
    }
    int result = pop(evalStack);
    free(evalStack->data);
    free(evalStack);
    return result;
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
    Stack* input = createStack(100);
    
    // push the initial state
    push(stack, 0);

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

        // lookup the action in the parsing table based on the current state and token
        int action = parsingTable[state][(-1) * token.type];

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
                printf("%d\n", evaluate(input));
                free(stack->data);
                free(stack);
                free(input->data);
                free(input);
                return 0;
            case R1: {
                // reduce
                GrammarRule rule = grammar[0]; // use the grammar here
                for (int j = 0; j < 2*rule.length+1; ++j) {       // we iterate 2*rule.length times because we need to pop twice as many tokens as the length of the rule, since there are both tokens and states
                   if (j == 4) {
                        push(input, stack->data[stack->top]);
                    }                    
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
                   if (j == 4) {
                        push(input, stack->data[stack->top]);
                    }                    
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
                for (int j = 0; j < 2*rule.length+1; ++j) {
                    if (j == 2) {
                        push(input, stack->data[stack->top]);
                    }
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
            default:
                // error
                printf("Syntax error\n");
                printf("action = %d\n", action);
                free(stack->data);
                free(stack);
                return -1;
        }
        /*printf("Stack contents à l'itération %d: ", i);
        for (int j = 0; j <= stack->top; ++j) {
            printf("%d ", stack->data[j]);
        }
        printf("\n");                                          //thoses two printfs were used to debug the parser, they show the contents of the stack and the input at each iteration of the while loop
        printf("input contents à l'itération %d: ", i);
        for (int j = 0; j <= input->top; ++j) {
            printf("%d ", input->data[j]);
        }
        printf("\n\n\n");*/
    }
}
