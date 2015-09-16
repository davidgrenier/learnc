#include <stdio.h>

#define NELEMS(xs) (sizeof(xs)/sizeof(xs[0]))

void Trace()
{
    printf("---\n");
}

int main(int argc, char *argv[])
{
    int ages[] = { 23, 43, 12, 89, 2 };
    char* names[] = {
        "Mary", "Kim", "Daksha",
        "Terri", "Annie"
    };

    int count = NELEMS(ages);

    for (int i = 0; i < count; i++) {
        printf("%s has %d years lived.\n", *(names+i), ages[i]);
    }

    int *curAge = ages;
    char **curName = names;

    Trace();
    for (int i = 0; i < count; i++) {
        printf("%s is %d years old.\n", *(curName + i), *(curAge + i));
    }

    Trace();
    for (int i = 0; i < count; i++) {
        printf("%s is %d years old again.\n", i[curName], curAge[i]);
    }

    Trace();
    for (curAge = ages, curName = names; (curAge - ages) < count; curAge++, curName++) {
        printf("%s lived %d years so far.\n", *curName, *curAge);
    }

    return 0;
}
