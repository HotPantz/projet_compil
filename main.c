//Selyan Kablia et Nathan Lestrade

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
    parsingTable[0][3] = D4; // d4
    parsingTable[0][5] = D5; // d5
    parsingTable[1][1] = D6; // d6
    parsingTable[1][6] = ACC; // acc
    parsingTable[2][1] = R2; // r2
    parsingTable[2][2] = D7; // d7
    parsingTable[2][4] = R2; // r2
    parsingTable[2][6] = R2; // r2
    parsingTable[3][1] = R4; // r4
    parsingTable[3][2] = R4; // r4
    parsingTable[3][4] = R4; // r4
    parsingTable[3][6] = R4; // r4
    parsingTable[4][3] = D4; // d4
    parsingTable[4][5] = D5; // d5
    parsingTable[5][1] = R6; // r6
    parsingTable[5][2] = R6; // r6
    parsingTable[5][4] = R6; // r3
    parsingTable[5][6] = R6; // r6
    parsingTable[6][3] = D4; // d4
    parsingTable[6][5] = D5; // d5
    parsingTable[7][3] = D4; // d4
    parsingTable[7][5] = D5; // d5
    parsingTable[8][1] = D6; // d6
    parsingTable[8][4] = D11; // d11
    parsingTable[9][1] = R1; // r1
    parsingTable[9][2] = D7; // d7
    parsingTable[9][4] = R1; // r1
    parsingTable[9][6] = R1; // r1
    parsingTable[10][1] = R3; // r3
    parsingTable[10][2] = R3; // r3
    parsingTable[10][4] = R3; // r3
    parsingTable[10][6] = R3; // r3
    parsingTable[11][1] = R5; // r5
    parsingTable[11][2] = R5; // r5
    parsingTable[11][4] = R5; // r5
    parsingTable[11][6] = R5; // r5

    // Initialize the goto table
    int gotoTable[NUM_STATES][3];
    
    for (int i = 0; i < NUM_STATES; i++) {
        for (int j = 0; j < 3; j++) {
            gotoTable[i][j] = -1;
        }
    }

    // Fill in the goto table for E
    gotoTable[0][E-E] = 1;  //on fait E-E car on a initialisé E à 13, T à 14 et F à 15 pour pouvoir les différencier des valeurs des états dans la stack du parser
    gotoTable[4][E-E] = 8;

    // Fill in the goto table for T
    gotoTable[0][T-E] = 2;
    gotoTable[4][T-E] = 2;
    gotoTable[6][T-E] = 9;

    // Fill in the goto table for F
    gotoTable[0][F-E] = 3;
    gotoTable[4][F-E] = 3;
    gotoTable[6][F-E] = 3;
    gotoTable[7][F-E] = 10;

    char input[100];
    
    while (true) {
        printf("> ");
        fgets(input, sizeof(input), stdin);
        
        if (input[0] == 'q') {
            break;
        }
        
        // Read the input
        Token* tokens = tokenize(input);

        for (int i = 0; tokens[i].type != TOKEN_EOF; ++i) {
            switch (tokens[i].type) {
                case TOKEN_NUMBER:
                    break;
                case TOKEN_PLUS:
                    break;
                case TOKEN_MULTIPLY:
                    break;
                case TOKEN_LPAREN:
                    break;
                case TOKEN_RPAREN:
                    break;
                default:
                    printf("Unknown token ");
            }
        }

        // Call the parse function
        parse(tokens, parsingTable, gotoTable);

        // Evaluate the parsed expression
        //double result = evaluateExpression(tokens);

        // Print the result
        //printf("Result: %.2f\n", result);
    
    }

    return 0;

}
