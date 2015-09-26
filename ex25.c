#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

//#define MAX_DATA 5
#define MAX_DATA 100

int readString(char **outString, int maxBuffer)
{
    *outString = calloc(1, maxBuffer);
    checkMem(*outString);

    char *result = fgets(*outString, maxBuffer, stdin);
    check(result != NULL, "Input error.");

    return 0;

error:
    if (*outString) free(*outString);
    *outString = NULL;
    return -1;
}

int readInt(int *outInt)
{
    char *input = NULL;
    int rc = readString(&input, MAX_DATA);
    check(rc == 0, "Failed to read number.");

    *outInt = atoi(input);
    
    free(input);
    return 0;

error:
    if (input) free(input);
    return -1;
}

int readScan(const char *fmt, ...)
{
    int rc = 0;
    int maxBuffer = 0;

    va_list argp;
    va_start(argp, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            switch(fmt[++i]) {
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;

                case 'd':
                    rc = readInt(va_arg(argp, int *));
                    check(rc == 0, "Failed to read int.");
                    break;

                case 'c':
                    *va_arg(argp, char *) = fgetc(stdin);
                    break;

                case 's':
                    maxBuffer = va_arg(argp, int);
                    rc = readString(va_arg(argp, char **), maxBuffer);
                    check(rc == 0, "Failed to read string.");
                    break;

                default:
                    sentinel("Invalid format.");
            }
        } else {
            fgetc(stdin);
        }

        check (!feof(stdin) && !ferror(stdin), "Input error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

int main()
{
    printf("What's your first name? ");
    char *firstName = NULL;
    int rc = readScan("%s", MAX_DATA, &firstName);
    check(rc == 0, "Failed first name.");

    printf("What's your initial? ");
    char initial = ' ';
    rc = readScan("%c\n", &initial);
    check(rc == 0, "Failed initial.");

    printf("What's your last name? ");
    char *lastName = NULL;
    rc = readScan("%s", MAX_DATA, &lastName);
    check(rc == 0, "Failed last name.");

    printf("How old ar you? ");
    int age = 0;
    rc = readScan("%d", &age);

    printf("---- RESULTS ----\n");
    printf("First Name: %s", firstName);
    printf("Initial '%c'\n", initial);
    printf("Last Name: %s", lastName);
    printf("Age: %d\n", age);

    free(firstName);
    free(lastName);
    return 0;

error:
    return -1;
}
