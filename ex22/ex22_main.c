#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Zed A. Shaw";

void scopeDemo(int count)
{
    logInfo("count is: %d", count);

    if (count > 10) {
        int count = 100;
        logInfo("count in this scope is %d", count);
    }

    logInfo("count is at exit: %d", count);

    count = 3000;

    //scopeDemo(count + 1);

    logInfo("count after assign: %d", count);
}

int main(int argc, char *argv[])
{
    logInfo("My name: %s, age: %d", MY_NAME, getAge());

    setAge(100);
    logInfo("My age is now: %d", getAge());

    logInfo("THE_SIZE is: %d", THE_SIZE);
    printSize();

    THE_SIZE = 9;

    logInfo("THE_SIZE is now: %d", THE_SIZE);
    printSize();

    logInfo("Ratio at first: %f", updateRatio(2.0));
    logInfo("Ratio again: %f", updateRatio(10.0));
    logInfo("Ratio at last: %f", updateRatio(300.0));

    int count = 4;
    scopeDemo(count);
    scopeDemo(count * 20);

    logInfo("Count after calling scopeDemo: %d", count);

    return 0;
}
