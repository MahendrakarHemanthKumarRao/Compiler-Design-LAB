#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

int isValidIdentifier(const char *identifier);

int main() {
    char identifier[MAX_LENGTH];

    printf("Enter an identifier: ");
    scanf("%s", identifier);

    if (isValidIdentifier(identifier)) {
        printf("%s is a valid identifier.\n", identifier);
    } else {
        printf("%s is not a valid identifier.\n", identifier);
    }

    return 0;
}

int isValidIdentifier(const char *identifier) {
    // Check if the identifier is empty
    if (strlen(identifier) == 0)
        return 0;

    // Check if the first character is a letter or underscore
    if (!isalpha(identifier[0]) && identifier[0] != '_')
        return 0;

    // Check the rest of the characters
    for (int i = 1; i < strlen(identifier); i++) {
        if (!isalnum(identifier[i]) && identifier[i] != '_')
            return 0;
    }

    // If all checks pass, the identifier is valid
    return 1;
}

