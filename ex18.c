#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    
    exit(1);
}

typedef int (*compare)(int a, int b);
typedef int *(*sort)(int *numbers, int count, compare cmp);

#define SWAP(expr1, expr2) int temp = expr1; expr1 = expr2; expr2 = temp;

int *getCopy(int *numbers, int count)
{
    int *target = malloc(count * sizeof(int));
    if (!target) die("Memory error");

    memcpy(target, numbers, count * sizeof(int));

    return target;
}

int partition(int *numbers, int low, int hi, compare cmp)
{
    int pivot = numbers[low];

    int i = low;
    int j = hi;

    while (i < j) {
        i++;
        if (cmp(numbers[i], pivot) > 0) {
            while (j > i) {
                if (cmp(pivot, numbers[j]) > 0) {
                    SWAP(numbers[i], numbers[j])
                    break;
                }
                j--;
            }
            j--;
        }
    }

    if (j < i) i = j;

    numbers[low] = numbers[i];
    numbers[i] = pivot;

    return i;
}

void qSort(int *numbers, int low, int hi, compare cmp)
{
    if (low >= hi) return;

    int i = partition(numbers, low, hi, cmp);

    qSort(numbers, low, i - 1, cmp);
    qSort(numbers, i + 1, hi, cmp);
}

int *quickSort(int *numbers, int count, compare cmp)
{
    int *target = getCopy(numbers, count);

    qSort(target, 0, count - 1, cmp);

    return target;
}

int *bubbleSort(int *numbers, int count, compare cmp)
{
    int *target = getCopy(numbers, count);

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < count - 1; j++) {
            if (cmp(target[j], target[j+1]) > 0) {
                SWAP(target[j], target[j+1]);
            }
        }
    }

    return target;
}

int sortedOrder(int a, int b)
{
    return a - b;
}

int reverseOrder(int a, int b)
{
    return b - a;
}

int strangeOrder(int a, int b)
{
    if (b == 0) {
        return 0;
    } else {
        return a % b;
    }
}

void testSort(int *numbers, int count, sort sort, compare cmp)
{
    int *sorted = sort(numbers, count, cmp);
    if (!sorted) die("Failed to sort as requested");

    for (int i = 0; i < count; i++) {
        printf("%d ", sorted[i]);
    }

    printf("\n");

    free(sorted);
}


int main(int argc, char *argv[])
{
    if (argc == 1) die("Usage: ex18 2 5 2 1 3\n");

    int count = argc - 1;

    int *numbers = malloc(count * sizeof(int));
    if (!numbers) die("Memory error");

    char **input = argv + 1;

    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(input[i]);
    }

    testSort(numbers, count, bubbleSort, sortedOrder);
    testSort(numbers, count, bubbleSort, reverseOrder);
    testSort(numbers, count, bubbleSort, strangeOrder);

    testSort(numbers, count, quickSort, sortedOrder);
    testSort(numbers, count, quickSort, reverseOrder);
    testSort(numbers, count, quickSort, strangeOrder);

    free(numbers);
    
    return 0;
}
