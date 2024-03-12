#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "lexer.h"

#define NUM_STATES 10
#define NUM_SYMBOLS 8

typedef struct {
    int* data;
    int top;
    int size;
} Stack;

Stack* createStack(int size); // Create a stack of given size
void push(Stack* stack, int value); // Push a value onto the stack
int pop(Stack* stack) ; // Pop a value from the stack
int parse(Token* tokens, int parsingTable[NUM_STATES][NUM_SYMBOLS], int gotoTable[NUM_STATES]) ; // Parse the input tokens using the given parsing table and follow set

typedef enum {
    PROD_E_PLUS_E,      // E -> E + E
    PROD_E_MUL_E,       // E -> E * E
    PROD_LPAREN_E_RPAREN, // E -> (E)
    PROD_VAL            // E -> val
} Production;

typedef struct {
    Production production;
    int length;
} GrammarRule;


#endif /* PARSER_H */
