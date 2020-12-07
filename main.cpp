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

void print_container(collection a)
{
    std::cout << "[ ";
    auto tmp = a.begin();
    std::cout << tmp->data;
    // for (; tmp!=a.end(); tmp++)
    //     std::cout << *tmp << ", ";
    std::cout << *tmp << " ]" << std::endl;
}
void flag(const char *message) { std::cout << message << std::endl; }

/// 'main' function \return Exit code('0' if program ended successfully)
int main()
{
    try
    {

        collection a;
        flag("#1");
        collection b(10);
        flag("#2");
        auto tmp = b.begin();
        flag("#3");
        for (int i = 0; i < 10; i++, tmp++)
            *tmp = i * i;
        flag("#4");
        a = b;
        flag("#5");
        collection c(a);
        flag("#6");
        collection d = std::move(a);
        flag("#7");
        // print_container(a);
        // b.erase(b.begin());
        print_container(b);
        c.erase(c.begin());
        c.erase(c.begin());
        print_container(c);
        print_container(d);
        return 0;
    }
    catch (const char *message)
    {
        std::cout << "Program throwed an exception: " << message << std::endl;
    }
}