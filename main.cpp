/**
 * \file
 * Body of the program
 */
#include<iostream>
#include"my_vector.h"
/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {
        MyVector<int> a;
        a.resize(5);
        // std::cout << "#1" << std::endl;
        std::cout << "Size: " << a.size() << std::endl;
        // std::cout << "#2" << std::endl;
        for (size_t i=0;i < a.size();i++)
            a[i] = i*i;
        MyVector<int> b(a);
        b[0] = 100;
        a.swap(b);
        MyVector<int> c(3);
        c[0] = 7;
        c[1] = 7;
        c[2] = 7;
        b = std::move(c);
        // std::cout << "#3" << std::endl;
        std::cout  << "a = " << a << std::endl << "b = " << b << std::endl;
        return 0;
    }
    catch (const char* message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}