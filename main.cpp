/**
 * \file
 * Body of the program
 */
#include <iostream>
#include <vector>
#include <list>
#include "my_vector.h"
#include "my_list.h"
template <typename T>
using CollectionType = std::list<T>;
using collection = CollectionType<int>;
template <typename T>
void print_container(const CollectionType<T>& a)
{
    std::cout << "[ ";
    auto tmp = a.begin();
    for (size_t i = 1; i < a.size(); i++)
    {
        std::cout << *tmp << ", ";
        tmp++;
    }
    std::cout << *tmp << " ]" << std::endl;
}
/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {
        collection a;
        collection b(10);
        auto tmp = b.begin();
        for (int i = 0; i < 10; i++, tmp++)
            *tmp = i*i;
        a = b;
        collection c(a);
        collection d = std::move(a);
        print_container(a);
        print_container(b);
        print_container(c);
        print_container(d);
        return 0;
    }
    catch (const char *message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}