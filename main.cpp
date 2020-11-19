/**
 * \file
 * Body of the program
 */
#include <iostream>
#include "my_vector.h"
#include "my_list.h"
/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {
        MyVector<int> a;
        a.resize(5);
        for (size_t i=0;i < a.size();i++)
            a[i] = i*i;
        MyVector<int> b(a);
        MyVector<int> c(3);
        b[0] = 100;
        a.swap(b);
        MyVector<int> d(std::move(a));
        c[0] = 7;
        c[1] = 7;
        c[2] = 7;
        b = c;
        c = std::move(b);
        std::cout << "#1" << std::endl;
        a.insert(a.end(), 14);
        std::cout << "#1" << std::endl;
        a.insert(a.begin(), 100);
        std::cout << "#1" << std::endl;
        a.insert(a.end(), 10);
        std::cout << "#1" << std::endl;
        a.erase(a.end());
        a.erase(a.begin());
        a.erase(a.begin());
        std::cout << a.size() << " " << b.size() << " " << c.size() << " " << d.size() << std::endl;
        std::cout  << "a = " << a << std::endl;
        std::cout  << "b = " << b << std::endl;
        std::cout  << "c = " << c << std::endl;
        std::cout  << "d = " << d << std::endl;
        return 0;
    }
    catch (const char* message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}