#include <stdio.h>

void PrintFrom(char c)
{
    for (int i = 0; i < 25; i++) {
        printf("Char %c -> %i\n", c + i, c + i);
    }
}

int main()
{
    char x = 'a';
    PrintFrom(x);

    x = 'A';
    PrintFrom(x);
    
    return 0;
}
