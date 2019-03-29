#include <iostream>
#include <cstddef>
#include <fstream>

template <typename T>
Vector::Vector():
        size_       (0),
        capacity_   (V_CAPACITY),
        canary1_    (CANARY_FIRST),
        canary2_    (CANARY_SECOND),
        error_      (0),
        resizer_    (false)
{
    fout << "Constructor was called\n";
    try {
        data_ = new T[capacity_];
        //PRINT("NEW");
    }
    catch(const std::bad_alloc & e){
        fout << "Smth wrong with memory\n";
    }

}

template <typename T>
Vector<T>::Vector   (size_t cap):
        size_       (0),
        capacity_   (cap),
        canary1_    (CANARY_FIRST),
        canary2_    (CANARY_SECOND),
        error_      (0),
        resizer_    (false)
{
    fout << "Constructor was called\n";
    try {
        data_ = new T[capacity_];
        //PRINT("NEW");
    }
    catch(const std::bad_alloc & e){
        fout << "Smth wrong with memory\n";
    }

}

template <typename T>
Vector<T>::Vector(const Vector<T> & rhs):
        size_       (rhs.size_),
        capacity_   (rhs.capacity_),
        canary1_    (CANARY_FIRST),
        canary2_    (CANARY_SECOND),
        error_      (rhs.error_),
        resizer_    (rhs.resizer_)
{
    fout << "Constructor was called\n";
    try {
        data_ = new T[capacity_];
    }
    catch(const std::bad_alloc & e){
        fout << "Smth wrong with memory\n";
    }

}

template <typename T>
Vector<T>::Vector(Vector<T> && that):
        capacity_       (that.capacity_),
        size_           (that.size_),
        data_           (that.data_)
{
    that.data_ = nullptr;
}

template <typename T>
Vector<T>::~Vector()
{
    delete [] data_;
    data_ = nullptr;
}

template <typename T>
int Vector<T>::VectorOk()
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

template <typename T>
bool Vector<T>::Push(T value)
{
    $((VectorOk() == 0), error_);

    if(size_ * VECTOR_MULTIPLY >= capacity_)
    {
        resizer_ = true;
        Resize(VECTOR_MULTIPLY * capacity_);
    }

    data_[size_++] = value;

    $((VectorOk() == 0), error_);

    return true;
}

template <typename T>
int Vector<T>::Hash()
{
    size_t hash = 0;
    for(size_t i = 0; i < size_; ++i)
        hash |=   data_[i];
    hash ^=   size_;
    return hash;

}

template <typename T>
T Vector<T>::Pop()
{
    $((VectorOk( ) == 0),   error_);
    data_[  size_--] = 0;

    $((VectorOk( ) == 0),   error_);

    if(size_ == 0){
        Resize(capacity_ / 2 - capacity_ % 2);
    }

    return VectorOk( );
}

template <typename T>
T Vector<T>::Top()
{
    $((VectorOk() == 0),   error_);
    //PrintVector();
    return   data_[  size_];
}

template <typename T>
bool Vector<T>::Resize(size_t resize)
{
    $((VectorOk( ) == 0),   error_);

    T * adr;
    try
    {
        adr = new T [resize];
    }
    catch(const std::bad_alloc& ex)
    {
        fout << "Ops, problem with Resize: cannot return new memory for adr\n";
    }

    for(size_t i = 0; i < size_; i++)
        adr[i] = data_[i];

    capacity_ = resize;

    try
    {
        data_ = new T[capacity_];
    }
    catch(const std::bad_alloc& ex)
    {
        fout << "Ops, problem with Resize: cannot return new memory for data_\n";
    }

    for(size_t i = 0; i < size_; ++i)
        data_[i] = adr[i];
    for(size_t i = size_; i < capacity_; ++i)
        data_[i] = 0;

    delete [] (adr);
    resizer_ = false;

    $((VectorOk( ) == 0),   error_);

    if(error_ == 0) {
        return true;
    }
    return false;
}

template <typename T>
bool Vector<T>::Dump()
{
    fout << "Error = " << error_ << std::endl;
    for(unsigned i = 0; i < sizeof(EMes)/ sizeof(char*); i++)
    {
        if(((error_) >> i) & 1) {
            fout << EMes[i] << std::endl;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::PrintVector()
{
    fout <<"#------------------------------------------\n";
    fout << "|||| size = " << size_ << " |||| capacity = " << capacity_ <<" ||||\n";

    for(size_t i = 0; i < size_; ++i)
        fout <<"|||| data[" << &data_[i] << "] = "<< data_[i]<< std::endl;
    return true;
}

//=========================================
//      The beginning of operator
//          overloading session
//=========================================

template <typename T>
T & Vector<T>::at(size_t index)
{
    $((0 <= index)&&(index <= capacity_), error_);
    return data_[index];
}

template <typename T>
T & Vector<T>::operator[] (/*const*/size_t index)
{
    if(!((0 <= index) && (index <= capacity_))) {
        fout << "ERROR: the index is out of range\n" ;
        //return ;
    }
    return data_[index];
}

template <typename T>
const T & Vector<T>::operator[](size_t index) const
{
    if(!((0 <= index) && (index <= capacity_))) {
        fout << "ERROR: the index is out of range\n" ;
        //return ;
    }
    return data_[index];
}

template <typename T>
const size_t Vector<T>::getCapacity() const
{
    return capacity_;
}

template <typename T>
const size_t Vector<T>::getSize() const
{
    return size_;
}
/*
template <typename T>//???????????????????????????????????????????
Vector<T> operator+(const Vector<T> &v1, const Vector<T> &v2)
{
    //$(v1.getCapacity() == v2.getCapacity(), DIF_SIZE);
    $(v1.getSize() == v2.getSize(), DIF_SIZE);

    Vector<T> result(v2.getSize());

    for(size_t i = 0; i < v1.getSize(); ++i) {
        result.Push(v1[i] + v2[i]);
    }

    return result;
}
*/
template <typename T>
void Vector<T>::swap(Vector & rhs)
{
    using std::swap;
    swap(size_, rhs.size_);
    swap(capacity_, rhs.capacity_);
    swap(data_, rhs.data_);
}

//------------------------------------------------------------------
//----------Overloading NEW-----------------------------------------
//------------------------------------------------------------------

void * operator new(size_t size, const char* file, int line, const char * func)
{
    //void * p = nullptr;
    fout << "NEW CALLED\n";
    try {
        return new char[size];
        //return ::operator new (size); //can I place return in try statement????????
        //p = ::operator new (size);
    }
    catch(std::bad_alloc & e){
        PR("NEW", line, file, func);
    }
    //return p;
    //return new char[size]; ????????????
    //return ::operator new(size);
}

void * operator new[](size_t size, size_t number, const char * file, int line, const char * func)
{
    fout << "NEW[] CALLED\n";
    try {
        return new char[size * number];
    }
    catch(std::bad_alloc & e){
        PR("NEW[]", line, file, func);
    }
}


//------------------------------------------------------------------
//----------Stop overloading NEW------------------------------------
//------------------------------------------------------------------


void operator delete(void * ptr, const char * file, int line, const char * func)
{
    try {
        delete ((char*)ptr); // static_cast<char>
    }
    catch(std::bad_alloc & e){
        PR("DELETE", line, file, func);
    }
    //std::free(ptr);
    ptr = nullptr;
}

void operator delete[](void * ptr, const char * file, int line, const char * func)
{
    try {
        delete [] (char*)ptr; //Do i have to put size in the brackets?
    }
    catch(std::bad_alloc & e){
        PR("DELETE[]", line, file, func);
    }
    ptr = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator = (Vector<T> & rhs)
{
    if(this == &rhs)
        return *this;

    swap(rhs);
    return * this;
}

template <typename T>
Vector<T> & Vector<T>::operator = (Vector<T> && rhs)
{

    if(this == &rhs)
        return *this;

    delete [] data_;

    swap(rhs);

    return *this;
}

//~~~~~~~~~~~~~~~Implementation of " COPY & SWAP "~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
Vector<T> & Vector<T>::operator = (const Vector<T> & that)
{
    Vector copy(that);
    swap(copy);
    return * this;
}


template <typename T>
bool Vector<T>::operator==(const Vector<T> & that)
{
    if(size_ != that.getSize() || capacity_ != that.getCapacity())
    {
        return false;
    }

    for(size_t i = 0; i < capacity_; i++)
    {
        if(data_[i] != that[i])
        {
            return false;
        }
    }

    return true;
}

//=========================================
//      The end of operator
//      overloading session
//=========================================