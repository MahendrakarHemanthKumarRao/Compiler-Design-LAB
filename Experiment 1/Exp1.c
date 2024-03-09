#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENTIFIER_LENGTH 50
#define MAX_KEYWORD_LENGTH 10

// Token types
typedef enum {
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_COMMENT,
    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

// Structure for token
typedef struct {
    TokenType type;
    char lexeme[MAX_IDENTIFIER_LENGTH + 1]; // +1 for null terminator
} Token;

// Function prototypes
int isKeyword(char *identifier);
Token getNextToken(FILE *fp);

int main() {
    FILE *fp;
    char fileName[100];

    printf("Enter the file name: ");
    scanf("%s", fileName);

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    Token token;
    do {
        token = getNextToken(fp);
        switch (token.type) {
            case TOKEN_IDENTIFIER:
                printf("Identifier: %s\n", token.lexeme);
                break;
            case TOKEN_KEYWORD:
                printf("Keyword: %s\n", token.lexeme);
                break;
            case TOKEN_NUMBER:
                printf("Number: %s\n", token.lexeme);
                break;
            case TOKEN_COMMENT:
                // Ignore comments
                break;
            case TOKEN_ERROR:
                printf("Error: Invalid token\n");
                break;
            case TOKEN_EOF:
                printf("End of File\n");
                break;
        }
    } while (token.type != TOKEN_EOF);

    fclose(fp);
    return 0;
}

int isKeyword(char *identifier) {
    char keywords[][MAX_KEYWORD_LENGTH] = {"if", "else", "while", "for", "int", "float", "return"}; // Add more keywords as needed
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(identifier, keywords[i]) == 0) {
            return 1; // Keyword found
        }
    }
    return 0; // Not a keyword
}

Token getNextToken(FILE *fp) {
    char c;
    Token token;
    int index = 0;

    // Ignore whitespace characters
    do {
        c = fgetc(fp);
    } while (isspace(c));

    // Ignore comments
    if (c == '/') {
        char next = fgetc(fp);
        if (next == '/') {
            while ((c = fgetc(fp)) != '\n' && c != EOF);
            token.type = TOKEN_COMMENT;
            return token;
        } else {
            ungetc(next, fp);
        }
    }

    if (c == EOF) {
        token.type = TOKEN_EOF;
        return token;
    }

    // Read identifier or keyword
    if (isalpha(c)) {
        do {
            token.lexeme[index++] = c;
            c = fgetc(fp);
        } while (isalnum(c) && index < MAX_IDENTIFIER_LENGTH);
        token.lexeme[index] = '\0';

        if (isKeyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }

        ungetc(c, fp);
        return token;
    }

    // Read numbers
    if (isdigit(c)) {
        do {
            token.lexeme[index++] = c;
            c = fgetc(fp);
        } while (isdigit(c) && index < MAX_IDENTIFIER_LENGTH);
        token.lexeme[index] = '\0';

        token.type = TOKEN_NUMBER;
        ungetc(c, fp);
        return token;
    }

    // Invalid token
    token.type = TOKEN_ERROR;
    return token;
}

