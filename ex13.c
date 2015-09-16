#include <stdio.h>

char toLower(char c) {
    if (c < 97) {
        return c + 32;
    }

    return c;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("You need to supply at least one argument.\n");
        
        return 1;
    }

    for (int y = 1; y < argc; y++)
    {
        char *word = argv[y];
    
        int i = 0;
        char letter = word[i];

        for (; letter != '\0'; i++, letter = word[i]) {
            char l = toLower(letter);
            if (l == 'a') {
                printf("%d: 'A'\n", i);
            } else if (l == 'e') {
                printf("%d: 'E'\n", i);
            } else if (l == 'i') {
                printf("%d: 'I'\n", i);
            } else if (l == 'o') {
                printf("%d, 'O'\n", i);
            } else if (l == 'u') {
                printf("%d, 'U'\n", i);
            } else if (l == 'y') {
                if (i > 2) {
                    printf("%d, 'Y'\n", i);
                }
                // It'll skip to the "not a vowel" block before char 2.
            } else {
                printf("%d: %c is not a vowel\n", i, letter);
            }
        }
    }

    return 0;
}
