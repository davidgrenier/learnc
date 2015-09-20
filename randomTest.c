#include <stdio.h>
#include <stdlib.h>

int main ()
{
    int count = 5000;

    for (int i = 0; i < count; i++) {
        printf("%d ", (int)random());
    }

    printf("\n");

    return 0;
}
