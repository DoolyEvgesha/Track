#include <iostream>
#include <fstream>

#include "excep.h"

MyException::MyException() :
    info_(nullptr)
{
    fout << "Constr was called" << std::endl;
}

MyException::~MyException()
{
    fout << "Dtr was called" << std::endl;
}

