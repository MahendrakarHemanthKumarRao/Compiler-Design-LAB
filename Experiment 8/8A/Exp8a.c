#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the grammar rules
char grammar[3][10] = {"E->E+T", "E->T", "T->T*F"};

// Define the parsing table
char parsing_table[3][4][10] = {
    {"", "E+T", "", ""},
    {"", "", "T", ""},
    {"", "", "T*F", ""}
};

// Function to find the index of a non-terminal in the grammar
int find_non_terminal(char non_terminal) {
    for (int i = 0; i < 3; i++) {
        if (grammar[i][0] == non_terminal)
            return i;
    }
    return -1;
}

// Function to find the index of a terminal in the parsing table
int find_terminal(char terminal) {
    switch (terminal) {
        case 'E':
            return 0;
        case '+':
            return 1;
        case 'T':
            return 2;
        case '*':
            return 3;
        default:
            return -1;
    }
}

// Function to perform LL(1) parsing
void parse(char *input) {
    char stack[100];
    int top = -1;
    int input_index = 0;
    stack[++top] = '$'; // Push initial stack symbol

    printf("Stack\t\tInput\t\tAction\n");
    printf("%s\t\t%s\t\tPush $\n", stack, input);

    while (stack[top] != '$') {
        char stack_top = stack[top];
        char current_input = input[input_index];

        // If stack top and input match, pop from stack and move to next input symbol
        if (stack_top == current_input) {
            printf("%s\t\t%s\t\tPop %c\n", stack, input, stack_top);
            top--;
            input_index++;
        } else {
            int non_terminal_index = find_non_terminal(stack_top);
            int terminal_index = find_terminal(current_input);
            if (non_terminal_index != -1 && terminal_index != -1) {
                // Find the production rule in the parsing table
                char *production = parsing_table[non_terminal_index][terminal_index];
                if (strcmp(production, "") == 0) {
                    printf("Error: No production rule found for %c, %c\n", stack_top, current_input);
                    return;
                }

                // Pop the non-terminal symbol and push the production rule onto the stack
                printf("%s\t\t%s\t\t%s\n", stack, input, production);
                top--;
                int len = strlen(production);
                for (int i = len - 1; i >= 0; i--) {
                    if (production[i] != 'e') // Ignore epsilon
                        stack[++top] = production[i];
                }
            } else {
                printf("Error: Invalid input symbol %c\n", current_input);
                return;
            }
        }
    }

    printf("%s\t\t%s\t\tAccepted\n", stack, input);
}

int main() {
    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);
    strcat(input, "$"); // Append $ to denote end of input

    parse(input);

    return 0;
}

