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
using CollectionType = List<T>;
using collection = CollectionType<int>;

void print_container(collection& a, const char* name)
{
    std::cout << name << " == [ ";
    auto tmp = a.begin();
    for (size_t i = 0; i < a.size(); i++, tmp++)
    {
        std::cout << *tmp << ", ";
    }
    std::cout << *tmp << " ]" << std::endl;
}
void flag(const char *message) { std::cout << message << std::endl; }

/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {

        collection a;
        collection b(10);
        flag("#1");
        auto tmp = b.begin();
        for (int i = 0; i < 10; i++, tmp++)
        {
            *tmp = i * i;
            std::cout << "b[" << i << "] = " << *tmp << std::endl;
        } 
        flag("#4");
        a = b;
        flag("#5");
        collection c(a);
        flag("#6");
        collection d = std::move(a);
        flag("#7");
        // print_container(a);
        // b.erase(b.begin());
        print_container(b, "b");
        c.erase(c.begin());
        c.erase(c.begin());
        print_container(c, "c");
        print_container(d, "d");
        return 0;
    }
    catch (const char *message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}