/*  Implementation of Vector on the basis
 *  of Stack using C++
 *  Current aim: read the book 55 Effective methods C++
 * */

#include <iostream>
#include <fstream>
#include <cstddef>

#include "vector.h"

int main()
{
    Vector<int> v;
    Vector<int> v1(3);
    Vector<int> v2(3);
    for(int i = 0; i < 3; ++i) {
        v1.Push(i);
    }

    for(int i = 7; i < 10; ++i)
        v2.Push(i);

    v1.PrintVector();
    v2.PrintVector();

    Vector<int> v_res = v1 + v2;
    v_res.PrintVector();

    for(int i = 0; i < 3; i++)
        fout << v_res.Pop() << std::endl;
    v_res.PrintVector();

    fout << "V1 " << std::endl;
    v1.PrintVector();
    Vector<int> v_copy1(v1);
    Vector<int>* v_copy2(&v2);
    v_copy1.PrintVector();
    v_copy2->PrintVector();

    return 0;
}