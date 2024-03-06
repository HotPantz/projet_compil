#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"
#include "parser.h"

int main() {
    char input[100];
    
    while (true) {
        printf("Enter an expression (q to quit):\n");
        fgets(input, sizeof(input), stdin);
        
        if (input[0] == 'q') {
            break;
        }
        
        setInput(input); // Mettre à jour l'entrée pour le lexer
        parseExpression();
    }
    
    return 0;
}

