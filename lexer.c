#include "lexer.h"

// Function to get the next token
Token getNextToken() {
    char c = getchar();
    
    // Ignore spaces
    while (isspace(c)) {
        c = getchar();
    }
    
    // Check for end of line
    if (c == '\n') {
        return (Token){TOKEN_EOL, 0};
    }
    
    // Check for operators and parentheses
    if (c == '+') {
        return (Token){TOKEN_PLUS, 0};
    } else if (c == '-') {
        return (Token){TOKEN_MINUS, 0};
    } else if (c == '*') {
        return (Token){TOKEN_MULTIPLY, 0};
    } else if (c == '/') {
        return (Token){TOKEN_DIVIDE, 0};
    } else if (c == '(') {
        return (Token){TOKEN_LPAREN, 0};
    } else if (c == ')') {
        return (Token){TOKEN_RPAREN, 0};
    }
    
    // If it's a digit or a decimal point, parse the number
    if (isdigit(c) || c == '.') {
        ungetc(c, stdin);
        double value;
        scanf("%lf", &value);
        return (Token){TOKEN_NUMBER, value};
    }
    
    // Unknown token
    return (Token){TOKEN_UNKNOWN, 0};
}
