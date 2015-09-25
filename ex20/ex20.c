#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void testDebug()
{
    debug("I have Brown Hair.");

    debug("I am %d years old.", 37);
}

void testLogErr()
{
    logError("I believe everything is broken.");
    logError("There are %d problems in %s.", 0, "space");
}

void testLogWarn()
{
    logWarn("You can safely ignore this.");
    logWarn("Maybe consider looking at: %s.", "/etc/passwd");
}

void testLogInfo()
{
    logInfo("Well I did something mundane.");
    logInfo("It happened %f times today.", 1.3f);
}

int testCheck(char *fileName)
{
    FILE *input = NULL;
    char *block = NULL;

    block = malloc(100);
    checkMem(block);

    input = fopen(fileName, "r");
    check(input, "Failed to open %s.", fileName);

    free(block);
    fclose(input);
    return 0;

error:
    if (block) free(block);
    if (input) free(input);
    return -1;
}

int testSentinel(int code)
{
    char *temp = malloc(100);
    checkMem(temp);

    switch (code) {
        case 1:
            logInfo("It worked.");
            break;
        default:
            sentinel("I shouldn't run.");
    }

    free(temp);
    return 0;

error:
    if (temp) free(temp);
    return -1;
}

int testCheckMem()
{
    char *test = NULL;
    checkMem(test);
    return 1;

error:
    return -1;
}

int testCheckDebug()
{
    int i = 0;
    checkDebug(i != 0, "Oops, I was 0.");

    return 0;
error:
    return -1;
}

int main(int argc, char *argv[])
{
    check(argc == 2, "Need an argument.");

    testDebug();
    testLogErr();
    testLogWarn();
    testLogInfo();

    check(testCheck("ex20.c") == 0, "failed with ex20.c");
    check(testCheck(argv[1]) == -1, "failed with argv");
    check(testSentinel(1) == 0, "testSentinel failed.");
    check(testSentinel(100) == -1, "testSentinel failed.");
    check(testCheckMem() == -1, "testCheckMem failed.");
    check(testCheckDebug() == -1, "testCheckDebug failed.");

    return 0;

error:
    return 1;
}

