#include <iostream>
#include <cstddef>

#include "stack.h"

Stack::Stack():
    size_        (0),
    capacity_    (STACK_CAPACITY),
    canary1_     (CANARY_FIRST),
    canary2_     (CANARY_SECOND),
    error_       (0),
    resizer_     (false)
{
    std::cout << ("Constructor v zdanii\n") << std::endl;

    try
    {
        data_ = new datatype[STACK_CAPACITY];
    }
    catch(const std::bad_alloc & e)
    {
        std::cout << "\nOps, smth wrong with new memory for _data\n" << std::endl<< std::endl;
    }
}


Stack::~Stack()
{
    std::cout << ("Destructor v zdanii\n") << std::endl;
    delete [] Stack::data_;
    data_ = nullptr;
}

int Stack::StackOk()
{
    //hash???
    if(size_ > capacity_)
        error_ += OVERSIZE;
    if(data_ == NULL)
        error_ += EMPTY_DATA;
    if(size_ < 0)
        error_ += NEGATIVE_SIZE;
    if(canary1_ != CANARY_FIRST || canary2_ != CANARY_SECOND)
        error_ += WRONG_BIRDS;

    if(error_ != 0)
        Dump();
    return error_;
}

bool Stack::Push(datatype value)
{
    $((StackOk() == 0), error_);

    if(size_ * STACK_MULTIPLE >= capacity_)
    {
        resizer_ = true;
        Resize(STACK_MULTIPLE * capacity_);
    }

    data_[size_++] = value;

    $((StackOk() == 0), error_);

    return true;
}


int Stack::Hash()
{
    size_t hash = 0;
    for(size_t i = 0; i < size_; ++i)
        hash |=   data_[i];
    hash ^=   size_;
    return hash;

}

int Stack::Pop()
{
    $((StackOk( ) == 0),   error_);
    data_[  size_--] = 0;

    $((StackOk( ) == 0),   error_);

    if(size_ == 0){
        Resize(capacity_ / 2 - capacity_ % 2);
    }

    return StackOk( );
}

datatype Stack::Top()
{
    $((StackOk() == 0),   error_);
    PrintStack();
    return   data_[  size_];
}

bool Stack::Resize(size_t resize)
{
    $((StackOk( ) == 0),   error_);

    datatype * adr;
    try
    {
        adr = new datatype [resize];
    }
    catch(const std::bad_alloc& ex)
    {
        std::cout << "Ops, problem with Resize: cannot return new memory for adr\n" << std::endl;
    }

    for(size_t i = 0; i < size_; i++)
        adr[i] = data_[i];

    capacity_ = resize;

    try
    {
        data_ = new datatype[capacity_];
    }
    catch(const std::bad_alloc& ex)
    {
        std::cout << "Ops, problem with Resize: cannot return new memory for data_\n" << std::endl;
    }

    for(size_t i = 0; i < size_; ++i)
        data_[i] = adr[i];
    for(size_t i = size_; i < capacity_; ++i)
        data_[i] = 0;

    delete [] (adr);
    resizer_ = false;

    $((StackOk( ) == 0),   error_);

    if(error_ == 0)
        return true;
    return false;
}

bool Stack::Dump()
{
    PrintStack();
    //Is it right to change magic number 8 for sizeof(char*)?
    for(int i = 0; i < sizeof(EMes)/ sizeof(char*); i++)
    {
        if(((error_) >> i) & 1)
            std::cout << EMes[i] << std::endl;
    }
    return true;
}

bool Stack::PrintStack()
{
    std::cout <<("#------------------------------------------\n")<< std::endl;

    std::cout << "|||| size = " << size_ <<" |||| capacity = " << capacity_ << " ||||" << std::endl;

    for(size_t i = 0; i < size_; ++i)
        std::cout <<"|||| data["<< &data_[i] <<"] = "<< data_[i] << std::endl;

    return true;
}

