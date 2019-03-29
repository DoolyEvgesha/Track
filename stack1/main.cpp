//  Implementation of stack of LILO type
//  with checks and hash in C++

#include <iostream>
#include <cstddef>

#include "stack.h"

int main() {
    int unit_test()
    {
        Stack stk = {};
        for(int i = 0; i < 30; ++i)
        {
            stk.Push(i);
        }
        for(int i = 0; i < 20; ++i)
        {
            stk.Push(i);
        }
    }
    return 0;
}
