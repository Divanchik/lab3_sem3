/**
 * \file
 * List container
 * \todo size() insert() erase() begin() end() swap() resize() clear()
 */
#pragma once

template<typename T>
/// List class
class List
{
    /// Node structure
    struct Node
    {
        /// Data
        T data;
        /// Next node
        Node* prev;
        /// Previous node
        Node* next;
        /// Constructor
        Node(const T& data, Node* prev, Node* next): data(data), prev(prev), next(next) {}
    };
    /// Head of list
    Node* _head;
    /// Past-the-end element
    Node* _tail;
    /// Size of list
    size_t _size;
    public:
    /// Constant iterator class
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
    List();
    /// Size constructor \param[in] new_size New size of list
    List(size_t new_size);
    /// Copy constructor \param[in] a List
    List(const List<T>& a);
    /// Move constructor \param[in,out] a List
    List(List<T>&& a);
    /// Copy assign
    List<T>& operator =(const List<T>& a);
    /// Move assign
    List<T>& operator =(List<T>&& a);
    /// Destructor
    ~List();
    /// Access operator \param[in] index Index of element
    T& operator [](size_t index);
    /// Constant access operator \param[in] index Index of element
    T operator [](size_t index) const;
    /// \return Size of list
    size_t size();
    /// Swap method
    void swap(List<T>& b);
    /// Change size of list \param[in] new_size New size of list
    void resize(size_t new_size);
    /// Clear the list
    void clear();
    
};