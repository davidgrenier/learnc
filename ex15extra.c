#include <stdio.h>

void Trace()
{
    printf("---\n");
}

void printArrays(int count, int ages[], char *names[])
{
    for (int i = 0; i < count; i++) {
        printf("%s has %d years lived.\n", names[i], ages[i]);
    }
}

void printPointers(int count, int *curAge, char **curName)
{
    for (int i = 0; i < count; i++) {
        printf("%s is %d years old.\n", curName[i], curAge[i]);
    }
}

void printOffset(int count, int *curAge, char **curName)
{
    for (int i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", *(curName + i), *(curAge + i));
    }
}

void printSlide(int count, int *curAge, char **curName)
{
    int* ages = curAge;
    while (curAge - ages < count) {
        printf("%s lived %d years so far.\n", *curName, *curAge);
        curAge++;
        curName++;
    }
}

int main(int argc, char *argv[])
{
    int ages[] = { 23, 43, 12, 89, 2 };
    char *names[] = {
        "Mary", "Kim", "Daksha",
        "Terri", "Annie"
    };

    int count = sizeof(ages)/sizeof(ages[0]);
    printArrays(count, ages, names);

    int *curAge = ages;
    char **curName = names;

    Trace();
    printPointers(count, ages, names);

    Trace();
    printOffset(count, ages, names);

    Trace();
    printSlide(count, ages, names);

    for (curAge = ages, curName = names; (curAge - ages) < count; curAge++, curName++) {
        printf("Pointer to age of %s is %p\n", *curName, curAge);
    }

    return 0;
}
