//Selyan Kablia et Nathan Lestrade

#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include "lexer.h"

#define NUM_STATES 12
#define NUM_SYMBOLS 6

#define E 0
#define T 1
#define F 2

#define D4 4
#define D5 5
#define D6 6
#define D7 7
#define D11 11

#define R1 21
#define R2 22
#define R3 23
#define R4 24
#define R5 25
#define R6 26

#define ACC 30

typedef struct {
    int* data;
    int top;
    int size;
} Stack;

Stack* createStack(int size); // Create a stack of given size
void push(Stack* stack, int value); // Push a value onto the stack
int pop(Stack* stack) ; // Pop a value from the stack
int parse(Token* tokens, int parsingTable[NUM_STATES][NUM_SYMBOLS], int* gotoTable[NUM_STATES][3]) ; // Parse the input tokens using the given parsing table and follow set

typedef enum {
    PROD_E_PLUS_T,          // E -> E + T
    PROD_E_T,               // E -> T
    PROD_T_MUL_F,           // T -> T * F
    PROD_T_F,               // T -> F
    PROD_F_LPAREN_E_RPAREN, // F -> (E)
    PROD_F_VAL              // F -> val
} Production;

typedef struct {
    Production production;
    int length;
} GrammarRule;


#endif /* PARSER_H */
