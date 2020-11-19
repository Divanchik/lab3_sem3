/**
 * \file
 * MyList container
 */
#pragma once

template<typename T>
class MyList
{
    struct Node
    {
        T data;
        Node* prev;
        Node* next;

        Node(const T& data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };

    Node* _head;
    Node* _tail;
    size_t _size;
    
};