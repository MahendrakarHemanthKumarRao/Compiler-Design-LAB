#include <stdio.h>
#include <string.h>

int isComment(const char *line);

int main() {
    char line[100];

    printf("Enter a line: ");
    fgets(line, sizeof(line), stdin);

    if (isComment(line)) {
        printf("The given line is a comment.\n");
    } else {
        printf("The given line is not a comment.\n");
    }

    return 0;
}

int isComment(const char *line) {
    // Check if the line starts with "//"
    if (strncmp(line, "//", 2) == 0) {
        return 1; // It's a comment
    }

    // Check if the line contains "/*" or "*/"
    if (strstr(line, "/*") != NULL || strstr(line, "*/") != NULL) {
        return 1; // It's a comment
    }

    return 0; // Not a comment
}

