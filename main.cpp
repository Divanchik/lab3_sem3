/**
 * \file
 * Body of the program
 */
#include <iostream>
#include "my_vector.h"
#include "my_list.h"

template <typename T>
using CollectionType = List<T>;
/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {
        CollectionType<int> a;
        a.resize(5);
        for (size_t i = 0; i < a.size(); i++)
            a[i] = i * i;
        CollectionType<int> b(a);
        CollectionType<int> c(3);
        b[0] = 100;
        a.swap(b);
        CollectionType<int> d(std::move(a));
        c[0] = 7;
        c[1] = 7;
        c[2] = 7;
        b = c;
        c = std::move(b);
        a.insert(a.end(), 14);
        a.insert(a.begin(), 100);
        a.insert(a.end(), 10);
        a.erase(a.end());
        a.erase(a.begin());
        a.erase(a.begin());
        std::cout << a.size() << " " << b.size() << " " << c.size() << " " << d.size() << std::endl;
        std::cout << "a = " << a << std::endl;
        std::cout << "b = " << b << std::endl;
        std::cout << "c = " << c << std::endl;
        std::cout << "d = " << d << std::endl;
        return 0;
    }
    catch (const char *message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}