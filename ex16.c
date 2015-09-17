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

struct Person *createPerson(char* name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->Name = strdup(name);
    who->Age = age;
    who->Height = height;
    who->Weight = weight;

    return who;
}

void destroyPerson(struct Person *who)
{
    assert(who != NULL);

    free(who->Name);
    free(who);
}

void printPerson(struct Person *who)
{
    printf("Name: %s\n", who->Name);
    printf("\tAge: %i\n", who->Age);
    printf("\tHeight: %i\n", who->Height);
    printf("\tWeight: %i\n", who->Weight);
}

int main()
{
    struct Person *joe = createPerson("Joe Alex", 32, 64, 140);
    struct Person *jack = createPerson("Jack Blank", 20, 72, 180);

    printf("Joe is at memory location %p\n", joe);
    printPerson(joe);

    printf("Jack is at memory location %p\n", jack);
    printPerson(jack);
    //printPerson(NULL);

    //Make everyone age 20 years.
    joe->Age += 20;
    joe->Height -=2;
    joe->Weight +=40;

    jack->Age += 20;
    jack->Weight += 20;

    printPerson(joe);
    printPerson(jack);

    struct Person j = *joe;
    struct Person j2 = j;

    printf("Joe is at memory location %p\n", &j);

    j.Age += 3;

    printf("Joe is %i years old\n", j.Age);
    printf("Joe is at memory location %p\n", &j2);
    printf("Joe is %i years old\n", j2.Age);

    destroyPerson(joe);
    destroyPerson(jack);
    //destroyPerson(NULL);

    return 0;
}
