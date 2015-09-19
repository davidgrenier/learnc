#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int Value;
    struct Stack *next;
};

#define EMPTY (malloc(sizeof(struct Stack)))

int peek(struct Stack *stack)
{
    return stack->Value;
}

struct Stack *pop(struct Stack *stack)
{
   if (!stack->next) {
       printf("ERROR: the stack is empty\n");
       exit(1);
   }

   return stack->next;
}

struct Stack *push(struct Stack *stack, int value)
{
    struct Stack *new = EMPTY;

    new->Value = value;
    new->next = stack;

    return new;
}

void showTop(struct Stack *stack)
{
    printf("The top of the stack has %d\n", peek(stack));
}

int main()
{
    struct Stack *myStack = EMPTY;

    myStack = push(myStack, 3);
    myStack = push(myStack, 12);

    showTop(myStack);

    myStack = pop(myStack);
    showTop(myStack);

    myStack = pop(myStack);
    showTop(myStack);

    myStack = pop(myStack);

    return 0;
}
