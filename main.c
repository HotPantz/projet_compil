#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "parser.h"

int main() {
    int parsingTable[NUM_STATES][NUM_SYMBOLS];
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < NUM_SYMBOLS; j++) {
            parsingTable[i][j] = -1;
        }
    }

    // Fill in the parsing table
    parsingTable[0][2] = 1; // d2
    parsingTable[0][5] = 1; // d3
    parsingTable[1][0] = 2; // d4
    parsingTable[1][1] = 2; // d5
    parsingTable[1][5] = 3; // acc
    parsingTable[2][2] = 1; // d2
    parsingTable[2][5] = 1; // d3
    parsingTable[3][0] = 44; // r4
    parsingTable[3][1] = 44; // r4
    parsingTable[3][3] = 44; // r4
    parsingTable[3][5] = 44; // r4
    parsingTable[4][2] = 1; // d2
    parsingTable[4][5] = 1; // d3
    parsingTable[5][2] = 1; // d2
    parsingTable[5][5] = 1; // d3
    parsingTable[6][0] = 2; // d4
    parsingTable[6][1] = 2; // d5
    parsingTable[6][3] = 3; // d9
    parsingTable[7][0] = 41; // r1
    parsingTable[7][2] = 41; // r1
    parsingTable[7][4] = 41; // r1
    parsingTable[8][0] = 42; // r2
    parsingTable[8][1] = 42; // r2
    parsingTable[8][3] = 42; // r2
    parsingTable[8][5] = 42; // r2
    parsingTable[9][0] = 43; // r3
    parsingTable[9][1] = 43; // r3
    parsingTable[9][3] = 43; // r3
    parsingTable[9][5] = 43; // r3

    // Initialize the goto table
    int gotoTable[NUM_STATES];
    for (int i = 0; i < NUM_STATES; i++) {
        gotoTable[i] = -1;
    }

    // Fill in the goto table
    gotoTable[0] = 1;
    gotoTable[2] = 6;
    gotoTable[4] = 7;
    gotoTable[5] = 8;



    char input[100];
    
    while (true) {
        printf("Enter an expression (q to quit):\n");
        fgets(input, sizeof(input), stdin);
        
        if (input[0] == 'q') {
            break;
        }
        
        // Read the input
Token* tokens = tokenize(input);

// Print the tokens
printf("Tokens in the input: ");
for (int i = 0; tokens[i].type != TOKEN_EOF; ++i) {
    switch (tokens[i].type) {
        case TOKEN_NUMBER:
            printf("%f ", tokens[i].value);
            break;
        case TOKEN_PLUS:
            printf("+ ");
            break;
        case TOKEN_MULTIPLY:
            printf("* ");
            break;
        case TOKEN_LPAREN:
            printf("( ");
            break;
        case TOKEN_RPAREN:
            printf(") ");
            break;
        default:
            printf("Unknown token ");
    }
}
printf("\n");

// Call the parse function
parse(tokens, parsingTable, gotoTable);
    }

    

    return 0;
}
