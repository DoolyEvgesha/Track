#ifndef   STACK_H
#define   STACK_H

#define $(cond, error)         \
    do{                        \
        if(!(cond))            \
            {                  \
                error;         \
            }                  \
    }while(0)


//enum class CONSTS : int {STACK_CAPACITY = 20};//???????????????????
enum{
    RESIZE_MULTIPLE     = 2
};

typedef int datatype;


enum ERRORS
{
    EMPTY_STACK =   1 << 0, //1 == 1
    OVERSIZE =      1 << 1, //10 == 2
    EMPTY_DATA =    1 << 2, //100 == 4
    NEGATIVE_SIZE = 1 << 3, //1000 == 8
    WRONG_BIRDS =   1 << 4, //1000 == 16
    WRONG_HASH =    1 << 5, //10000 == 32
};

//How to use enum classes properly
enum CANARIES
{
    CANARY_FIRST     = 888,
    CANARY_SECOND    = 12

};

static char * EMes[] = {
        "ERROR1: stack is empty\n",
        "ERROR2: the size is too big\n",
        "ERROR3: the data is null\n",
        "ERROR4: the size is negative\n",
        "ERROR5: wrong birds\n",
        "ERROR6: different hash\n"
};

class Stack{
private:
    size_t      size_;
    size_t      capacity_;
    int         canary1_;
    datatype*   data_;
    int         canary2_;
    int         error_;
    bool        resizer_;

    int         StackOk         ();
    bool        PrintStack      ();
    int         Hash            ();
    bool        Resize          (size_t resize);

public:
    Stack();
    ~Stack();

    bool        Push            (datatype);
    int         Pop             ();
    bool        Dump            ();
    int         Top             ();
};

#endif
