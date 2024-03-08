#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    float value;
    struct StackNode *next;
} StackNode;

typedef struct OpStackNode {
    TokenType type;
    struct OpStackNode *next;
} OpStackNode;

// Fonctions pour la pile d'opérandes
StackNode* pushOperand(StackNode **top, float value) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        perror("Failed to allocate memory for operand node");
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = *top;
    *top = newNode;
    return newNode;
}

float popOperand(StackNode **top) {
    if (*top == NULL) {
        printf("Operand stack underflow\n");
        exit(EXIT_FAILURE);
    }
    StackNode* tempNode = *top;
    float value = tempNode->value;
    *top = tempNode->next;
    free(tempNode);
    return value;
}

// Fonctions pour la pile d'opérateurs
OpStackNode* pushOperator(OpStackNode **top, TokenType type) {
    OpStackNode* newNode = (OpStackNode*)malloc(sizeof(OpStackNode));
    if (!newNode) {
        perror("Failed to allocate memory for operator node");
        exit(EXIT_FAILURE);
    }
    newNode->type = type;
    newNode->next = *top;
    *top = newNode;
    return newNode;
}

TokenType popOperator(OpStackNode **top) {
    if (*top == NULL) {
        printf("Operator stack underflow\n");
        exit(EXIT_FAILURE);
    }
    OpStackNode* tempNode = *top;
    TokenType type = tempNode->type;
    *top = tempNode->next;
    free(tempNode);
    return type;
}

// Vérifie si l'opérateur est '+' ou '-'
bool isLowPrecedenceOperator(TokenType type) {
    return type == TOKEN_PLUS || type == TOKEN_MINUS;
}

// Vérifie si l'opérateur est '*' ou '/'
bool isHighPrecedenceOperator(TokenType type) {
    return type == TOKEN_MULTIPLY || type == TOKEN_DIVIDE;
}

// Applique un opérateur à deux opérandes
float applyOperator(float operand1, float operand2, TokenType operator) {
    switch (operator) {
        case TOKEN_PLUS: return operand1 + operand2;
        case TOKEN_MINUS: return operand1 - operand2;
        case TOKEN_MULTIPLY: return operand1 * operand2;
        case TOKEN_DIVIDE:
            if (operand2 == 0) {
                printf("Division by zero error.\n");
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        default:
            printf("Unknown operator error.\n");
            exit(EXIT_FAILURE);
    }
}

// Évalue l'expression en tenant compte des priorités des opérateurs
void evaluateExpressionWithPrecedence(StackNode **operands, OpStackNode **operators) {
    while (*operators != NULL) {
        TokenType operator = popOperator(operators);
        float operand2 = popOperand(operands);
        float operand1 = popOperand(operands);
        float result = applyOperator(operand1, operand2, operator);
        pushOperand(operands, result);
    }
}

void parseExpression() {
    StackNode *operandStack = NULL;
    OpStackNode *operatorStack = NULL;
    Token token;

    while (true) {
        token = getNextToken();
        if (token.type == TOKEN_EOF) break;

        if (token.type == TOKEN_FLOAT) {
            pushOperand(&operandStack, token.value);
        } else if (isLowPrecedenceOperator(token.type) || isHighPrecedenceOperator(token.type)) {
            pushOperator(&operatorStack, token.type);
        } else if (token.type == TOKEN_LPAREN) {
            // Traitement spécifique pour les parenthèses ouvrantes
        } else if (token.type == TOKEN_RPAREN) {
            // Traitement spécifique pour les parenthèses fermantes, y compris l'évaluation de l'expression parenthésée
        }
    }

    evaluateExpressionWithPrecedence(&operandStack, &operatorStack);

    if (operandStack != NULL) {
        float finalResult = popOperand(&operandStack);
        if (operandStack != NULL) {
            printf("Error: Stack not empty after evaluation.\n");
        } else {
            printf("Result: %.2f\n", finalResult);
        }
    } else {
        printf("Error: Operand stack is empty.\n");
    }

    // Libérer la mémoire si nécessaire
    while (operandStack != NULL) {
        StackNode *temp = operandStack;
        operandStack = operandStack->next;
        free(temp);
    }

    while (operatorStack != NULL) {
        OpStackNode *temp = operatorStack;
        operatorStack = operatorStack->next;
        free(temp);
    }
}