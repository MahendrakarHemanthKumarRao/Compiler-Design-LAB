#include <stdio.h>
#include <string.h>

int main() {
    char s[5];

    printf("\nEnter any operator: ");
    fgets(s, sizeof(s), stdin);

    switch(s[0]) {
        case '>':
            if(s[1] == '=')
                printf("\nGreater than or equal");
            else
                printf("\nGreater than");
            break;
        case '<':
            if(s[1] == '=')
                printf("\nLess than or equal");
            else
                printf("\nLess than");
            break;
        case '=':
            if(s[1] == '=')
                printf("\nEqual to");
            else
                printf("\nAssignment");
            break;
        case '!':
            if(s[1] == '=')
                printf("\nNot Equal");
            else
                printf("\nBit Not");
            break;
        case '&':
            if(s[1] == '&')
                printf("\nLogical AND");
            else
                printf("\nBitwise AND");
            break;
        case '|':
            if(s[1] == '|')
                printf("\nLogical OR");
            else
                printf("\nBitwise OR");
            break;
        case '+':
            printf("\nAddition");
            break;
        case '-':
            printf("\nSubtraction");
            break;
        case '*':
            printf("\nMultiplication");
            break;
        case '/':
            printf("\nDivision");
            break;
        case '%':
            printf("\nModulus");
            break;
        default:
            printf("\nNot a valid operator");
    }

    printf("\n");
    return 0;
}

