#include <stdio.h>

void printString(char name[])
{
    printf("The characters: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("The name: %s\n", name);
}

void printContent(char name[], int numbers[])
{
    printf("The numbers are %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);
    printString(name);
}

int main()
{
    int numbers[4] = {};
    char name[4] = {'a'};

    printContent(name, numbers);

    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;

    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    printContent(name, numbers);

    char *another = "Zed";
    printString(another);

    //Valgrind doesn't give a shit
    int numbers2[4] = {'T', 'a', 't'};
    char name2[4] = {82};

    printContent(name2, numbers2);
    //Valgrind doesn't give a shit either.
    //printContent(numbers2, name2);

    //Yeah C is a shit language.
    char *numbers3 = "Zed";
    printf("The numbers are: %d %d %d %d\n", numbers3[0], numbers3[1], numbers3[2], numbers3[3]); 

    char *name3 = (char*)4196856;
    printf("The number is %d.\n", (int) name3);
    printf("The numbers are %d %d %d %d\n", name3[0], name3[1], name3[2], name3[3]);
    printf("The final number is %d\n", (int) name3);
    printString(name3);
}
