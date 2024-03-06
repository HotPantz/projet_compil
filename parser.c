#include "parser.h"

// Function to handle errors
void handleError() {
    printf("Error: Invalid expression\n");
    // Handle the error (e.g., exit or recovery mechanism)
}

// Function to parse a term
double parseTerm() {
    Token token = getNextToken();
    if (token.type == TOKEN_NUMBER) {
        return token.value;
    } else if (token.type == TOKEN_LPAREN) {
        double result = parseExpression();
        token = getNextToken();
        if (token.type != TOKEN_RPAREN) {
            handleError();
        }
        return result;
    } else if (token.type == TOKEN_MINUS) {
        return -parseTerm();
    } else {
        handleError();
        return 0; // Placeholder for error handling
    }
}

// Function to parse a product
double parseProduct() {
    double result = parseTerm();
    Token token = getNextToken();
    while (token.type == TOKEN_MULTIPLY || token.type == TOKEN_DIVIDE) {
        double nextTerm = parseTerm();
        if (token.type == TOKEN_MULTIPLY) {
            result *= nextTerm;
        } else {
            result /= nextTerm;
        }
        token = getNextToken();
    }
    ungetc('\n', stdin); // Add the missing argument here
    return result;
}

// Function to parse an expression
double parseExpression() {
    double result = parseProduct();
    Token token = getNextToken();
    while (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
        double nextProduct = parseProduct();
        if (token.type == TOKEN_PLUS) {
            result += nextProduct;
        } else {
            result -= nextProduct;
        }
        token = getNextToken();
    }
    ungetc('\n', stdin); // Add the missing argument here
    return result;
}
