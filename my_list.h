#pragma once

template <typename T>
struct Node
{
    T _data;
    Node *_next;
    Node *_prev;

    Node(const T &data, Node *prev, Node *next) : _data(data), _next(next), _prev(prev) {}
};

template <typename T>
class List
{
    Node *_head;
    Node *_tail;
    Node *_end;
    size_t _size;

public:
    List() : _head(nullptr), _tail(nullptr), _end(T(), nullptr, nullptr), _size(0) {}
    List(size_t new_size);
    void insert(const Node *pos, const T &data)
    {
        if (_size == 0)
        {
            _head = new Node(data, nullptr, _end);
            _tail = _head;
            _end->prev = _tail;
            return;
        }
        if (pos == begin())
        {
            Node *tmp = new Node(data, nullptr, _head);
            _head->prev = tmp;
            _head = tmp;
            _tail = _end->prev;
        }
        else if (pos == end())
        {
            Node *tmp = new Node(data, nullptr, _head);
            _tail->
        }
        else
        {
        }
    }
    size_t size() const noexcept { return _size; }
    Node *begin() const noexcept { return _head; }
    Node *end() const noexcept { return _end; }
    T operator[](size_t index) const
    {
        if (index >= _size)
            throw "IndexError: Index out of range!";
        Node *tmp = _head;
        for (size_t i = 0; i != index; i++)
            tmp = tmp->next;
        return tmp->_data;
    }
    T &operator[](size_t index)
    {
        if (index >= _size)
            throw "IndexError: Index out of range!";
        Node *tmp = _head;
        for (size_t i = 0; i != index; i++)
            tmp = tmp->next;
        return tmp->_data;
    }
};