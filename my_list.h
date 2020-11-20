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
    /// Head of list
    Node* _head;
    /// Past-the-end element
    Node* _tail;
    /// Size of list
    size_t _size;
    public:

    class ConstIterator
    {
        Node* node;
        ConstIterator(Node* node): node(node) {}

        public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::bidirectional_iterator_tag;

        friend class List<T>;

        ConstIterator& operator++()
        {
            node = node->next;
            return *this;
        }
        ConstIterator operator++(int)
        {
            auto result(*this);
            node = node->next;
            return result
        }
    }
    /// Default construcor
    MyList();
    /// Size constructor
    MyList(size_t new_size);
    /// Copy constructor
    MyList(const MyList<T>& a);
    /// Move constructor
    MyList(MyList<T>&& a);
    /// Copy assign
    MyList<T>& operator =(const MyList<T>& a);
    /// Move assign
    MyList<T>& operator =(MyList<T>&& a);
    /// Destructor
    ~MyList();
    /// Access operator
    T& operator [](size_t index);
    /// Constant access operator
    T operator [](size_t index) const;
    /// size() insert() erase() begin() end() swap() resize() clear()
    size_t size();
    void swap(MyList<T>& b);
    void resize(size_t new_size);
    void clear();
    
};