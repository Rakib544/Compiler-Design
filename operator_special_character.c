#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isOperator(char buffer[]) {
    char operators[][4] = {
        "+", "-", "*", "/", "%",
        "=", "==", "!=", "<", ">",
        "<=", ">=", "++", "--",
        "&&", "||", "!", "&", "|",
        "^", "~", "<<", ">>",
        "+=", "-=", "*=", "/=", "%=",
        "&=", "|=", "^=", "<<=", ">>=",
        "->"
    };

    int i;
    for (i = 0; i < sizeof(operators) / sizeof(operators[0]); i++) {
        if (strcmp(operators[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int isSpecial(char ch) {
    char special[] = "(){}[];,.:#?'\"\\";
    return strchr(special, ch) != NULL;
}

int main() {
    char ch, next;
    char buffer[4];
    FILE *fp;
    int i;

    fp = fopen("code.txt", "r");

    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (strchr("+-*/%=!<>&|^~", ch) != NULL) {
            buffer[0] = ch;
            buffer[1] = '\0';

            next = fgetc(fp);

            if (next != EOF) {
                buffer[1] = next;
                buffer[2] = '\0';

                if (!isOperator(buffer)) {
                    buffer[1] = '\0';
                    ungetc(next, fp);
                }
            }

            if (isOperator(buffer))
                printf("%s is operator\n", buffer);
            else
                printf("%c is operator\n", ch);
        }
        else if (isSpecial(ch)) {
            printf("%c is special character\n", ch);
        }
    }

    fclose(fp);
    return 0;
}