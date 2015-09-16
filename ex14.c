#include <stdio.h>
#include <ctype.h>
#include <string.h>

int canPrintIt(char ch)
{
    return isalpha(ch) || isblank(ch);
}

void printLetters(int length, char *arg)
{
    for (int i = 0; i < length; i++) {
        char ch = arg[i];

        //if (canPrintIt(ch)) {
        if (isalpha(ch) || isblank(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

void printArguments(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        int length = strlen(argv[i]);
        printLetters(length, argv[i]);
    }
}

int main(int argc, char *argv[])
{
    printArguments(argc, argv);
    return 0;
}
