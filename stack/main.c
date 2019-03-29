#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#define can1 888
#define can2 12

//Implementation of stack of LILO type
//with checks and hash
typedef int datatype;

#define $(CONDITION, error)                              \
    if(!(CONDITION))                                     \
    {                                                    \
        error;                                           \
    }

typedef enum ERRORS
{
    EMPTY_STACK =   1 << 0, //1 == 1
    OVERSIZE =      1 << 1, //10 == 2
    EMPTY_DATA =    1 << 2, //100 == 4
    NEGATIVE_SIZE = 1 << 3, //1000 == 8
    WRONG_BIRDS =   1 << 4, //1000 == 16
    WRONG_HASH =    1 << 5, //10000 == 32
}ERRORS;

typedef enum CANARIES
{
    canary1 = can1,
    canary2 = can2

}CANARIES;

char * EMessage[] = {
    "ERROR1: stack is empty\n",
    "ERROR2: the size is too big\n",
    "ERROR3: the data is null\n",
    "ERROR4: the size is negative\n",
    "ERROR5: wrong birds\n",
    "ERROR6: different hash\n"
};

typedef struct Stack{
    size_t      _size;
    size_t      _capacity;
    int         _canary1;
    datatype *  _data;
    int         _canary2;
    int         _error;
}Stack;

int     Push(Stack * stk, int value);
int     Pop(Stack * stk);
int     StackOk(Stack * stk);
Stack * CreateStack(Stack * stk, size_t cap);
void    StackDestructor(Stack * stk);
void    Dump(Stack * stk);
int     Top(Stack * stk);
void    Resize(Stack * stk, size_t size);
void    PrintStack(Stack * stk);


int main() {
    Stack stk = {};
    size_t cap = 0;

    printf("Please, enter Stack capacity:\n");
    scanf("%zu", &cap);

    CreateStack(&stk, cap);

    int command = 0, number = 0;
    printf("Print 0 for push and then your number, 1 for pop\n");
    while(scanf("%d", &command) != EOF)
    {
        if(command == 0)
        {
            scanf("%d", &number);
            //printf("%d======\n", number);
            Push(&stk, number);
        }
        else
        {
            Pop(&stk);
        }
    }

    StackDestructor(&stk);
    return 0;
}

Stack * CreateStack(Stack * stk, size_t cap){
    stk->_capacity = cap;
    stk->_data = (int*)calloc(stk->_capacity, sizeof(*stk->_data));

    if(stk->_data == NULL)
        exit(errno);

    stk->_canary1 = canary1;
    stk->_canary2 = canary2;
    stk->_error = 0;
    stk->_size = 0;

    PrintStack(stk);
}

int StackOk(Stack * stk)
{
    if(stk == NULL)
        stk->_error = EMPTY_STACK;
    if(stk->_size > stk->_capacity)
        stk->_error += OVERSIZE;
    if(stk->_data == NULL)
        stk->_error += EMPTY_DATA;
    if(stk->_size < 0)
        stk->_error += NEGATIVE_SIZE;
    if(stk->_canary1 != canary1 || stk->_canary2 != canary2)
        stk->_error += WRONG_BIRDS;
    Dump(stk);
    return stk->_error;
}

int Push(Stack * stk, int value)
{
    $((StackOk(stk) == 0), stk->_error);

    stk->_data[stk->_size++] = value;

    $((StackOk(stk) == 0), stk->_error);

    PrintStack(stk);
}

int Pop(Stack * stk)
{
    $((StackOk(stk) == 0), stk->_error);
    int h = Hash(stk);
    stk->_data[stk->_size--] = 0;

    $((StackOk(stk) == 0), stk->_error);
    PrintStack(stk);

    int h1 = Hash(stk);
    if(h != h1){
        Dump(stk);
        return WRONG_HASH;
    }

    return StackOk(stk);
}

int Top(Stack * stk)
{
    $((StackOk(stk) == 0), stk->_error);
    PrintStack(stk);
    return stk->_data[stk->_size];
}

void Resize(Stack * stk, size_t size)
{
    $((StackOk(stk) == 0), stk->_error);

    datatype * adr = (datatype*)calloc(stk->_capacity, sizeof(*stk->_data));
    for(int i = 0; i < stk->_size; i++)
        adr[i] = stk->_data[i];

    stk->_size = size;
    stk->_data = (int*)realloc(stk->_data, stk->_size);
    for(int i = 0; i < sizeof(adr); ++i)
        stk->_data[i] = adr[i];
    for(size_t i = stk->_size; i < stk->_capacity; ++i)
        stk->_data[i] = 0;
    free(adr);

    PrintStack(stk);
    Dump(stk);
    $((StackOk(stk) == 0), stk->_error);
}

void StackDestructor(Stack * stk){
    $((StackOk(stk) == 0), stk->_error);

    free(stk->_data);
    stk->_data = NULL;
    printf("The stack was destroyed. Press F to pay respect\n");
}

void Dump(Stack * stk)
{
    for(int i = 0; i < sizeof(EMessage)/8; i++)
    {
        if(((stk->_error) >> i) & 1)
            printf("%s", EMessage[i]);
    }
}

int Hash(Stack * stk)
{
    int hash = 0;
    for(int i = 0; i < stk->_size; ++i)
        hash |= stk->_data[i];
    hash ^= stk->_size;
    return hash;

}

void PrintStack(Stack * stk)
{
    printf("#------------------------------------------\n");
    printf("|||| size = %zu |||| capacity = %zu ||||\n", stk->_size, stk->_capacity);

    for(int i = 0; i < stk->_size; ++i)
        printf("|||| data[%p] = %d\n", &stk->_data[i], stk->_data[i]);
}
