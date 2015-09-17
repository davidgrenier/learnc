#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *Name;
    int Age;
    int Height;
    int Weight;
};

void printPerson(struct Person who)
{
    printf("Name: %s\n", who.Name);
    printf("\tAge: %i\n", who.Age);
    printf("\tHeight: %i\n", who.Height);
    printf("\tWeight: %i\n", who.Weight);
}

int main()
{
    struct Person joe;
    joe.Name = "Joe Alex";
    joe.Age = 32;
    joe.Height = 64;
    joe.Weight = 140;
    struct Person jack;
    jack.Name = "Jack Blank";
    jack.Age = 20;
    jack.Height = 72;
    jack.Weight = 180;

    printf("Joe is at memory location %p\n", &joe);
    printPerson(joe);

    printf("Jack is at memory location %p\n", &jack);
    printPerson(jack);

    //Make everyone age 20 years.
    joe.Age += 20;
    joe.Height -=2;
    joe.Weight +=40;

    jack.Age += 20;
    jack.Weight += 20;

    printPerson(joe);
    printPerson(jack);

    return 0;
}
