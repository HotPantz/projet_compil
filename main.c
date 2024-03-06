#include <stdio.h>
#include "parser.h"

int main() {
    printf("Enter an expression (q to quit):\n");
    char input[100];
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (input[0] == 'q') {
            break;
        }
        double result = parseExpression();
        printf("Result: %lf\n", result);
        fflush(stdin); // Vider le tampon d'entrée
        printf("Enter an expression (q to quit):\n");
    }
    return 0;
}
