/**
 * \file
 * List container
 */
#pragma once

template <typename T>
/// Structure Node
struct Node
{
    /// Data
    T _data;
    /// Pointer to next Node
    Node *_next;
    /// Pointer to prevoius Node
    Node *_prev;
    /// Constructor
    Node(const T &data, Node *prev, Node *next) : _data(data), _next(next), _prev(prev) {}
};
template <typename T>
/// Constant bidirectional iterator
class bidirectional_list_iterator
{
    /// Node pointer
    Node<T> *node;

public:
    /// Default constructor
    bidirectional_list_iterator() : node(nullptr) {}
    /// Constructor
    bidirectional_list_iterator(Node<T> *new_node) : node(new_node) {}
    /// Destructor
    ~bidirectional_list_iterator() {}
    /// Preincrenment
    bidirectional_list_iterator &operator++()
    {
        node = node->next;
        return *this;
    }
    /// Postincrement
    bidirectional_list_iterator operator++(int)
    {
        auto result(*this);
        node = node->next;
        return result;
    }
    /// Predecrement
    bidirectional_list_iterator &operator--()
    {
        node = node->prev;
        return *this;
    }
    /// Postdecrement
    bidirectional_list_iterator operator--(int)
    {
        auto result(*this);
        node = node->prev;
        return result;
    }
    /// Dereferentiation
    const T &operator*() const { return node->data; }
    /// Dereferentiation
    T &operator*() { return node->data; }
    /// Member access operator
    const Node<T> *operator->() { return node; }
    /// Equality operator
    bool operator==(bidirectional_list_iterator rhs) const { return node == rhs.node; }
    /// Inequality operator
    bool operator!=(bidirectional_list_iterator rhs)  const { return node != rhs.node; }
};
template <typename T>
/// List class
class List
{
    /// Head of list
    Node<T> *_head;
    /// Tail of list
    Node<T> *_tail;
    /// Past-the-end Node
    Node<T> *_void;
    /// Size of list
    size_t _size;

public:
    /// \return 'true' if list is empty
    bool empty() const noexcept { return _size == 0 ? true : false; }
    /// \return Size of list
    size_t size() const noexcept { return _size; }
    /// Default constructor
    List() : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0) {}
    /// Size constructor \param[in] new_size New size of list
    List(size_t new_size) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        while (_size != new_size)
            insert(end(), T());
    }
    /// Copy constructor \param[in] a List
    List(const List<T> &a) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        for (size_t i = 0; i < a.size(); i++)
            insert(end(), a[i]);
    }
    /// Move constructor \param[in] a List
    List(List &&a) : _void(new Node<T>(T(), nullptr, nullptr))
    {
        std::swap(_head, a._head);
        std::swap(_tail, a._tail);
        std::swap(_size, a._size);
    }
    /// Assign copy operator \param[in] a List
    List<T> &operator=(const List<T> &a)
    {
        clear();
        _void = new Node<T>(T(), nullptr, nullptr);
        for (size_t i = 0; i < a.size(); i++)
            insert(end(), a[i]);
    }
    /// Assign move operator \param[in] a List
    List<T> &operator=(List<T> &&a)
    {
        std::swap(_head, a._head);
        std::swap(_tail, a._tail);
        std::swap(_size, a._size);
    }
    /// Destructor
    ~List() { clear(); }
    /// Swap \param[in, out] a List
    void swap(List<T> &a)
    {
        std::swap(_head, a._head);
        std::swap(_tail, a._tail);
        std::swap(_size, a._size);
    }
    /// Clear the list
    void clear()
    {
        while (_size != 0)
            erase(begin());
        _head = nullptr;
        _tail = nullptr;
        delete _void;
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T operator[](size_t index) const
    {
        if (index >= _size)
            throw "IndexError: Index out of range!";
        Node<T> *tmp = _head;
        for (size_t i = 0; i != index; i++)
            tmp = tmp->next;
        return tmp->_data;
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T &operator[](size_t index)
    {
        if (index >= _size)
            throw "IndexError: Index out of range!";
        Node<T> *tmp = _head;
        for (size_t i = 0; i != index; i++)
            tmp = tmp->next;
        return tmp->_data;
    }
    /// \return Constant begin iterator
    const bidirectional_list_iterator<T> begin() const noexcept { return bidirectional_list_iterator<T>(_head); }
    /// \return Constant past-the-end iterator
    const bidirectional_list_iterator<T> end() const noexcept { return bidirectional_list_iterator<T>(_void); }
    /// \return Begin iterator
    bidirectional_list_iterator<T> begin() noexcept { return bidirectional_list_iterator<T>(_head); }
    /// \return Past-the-end iterator
    bidirectional_list_iterator<T> end() noexcept { return bidirectional_list_iterator<T>(_void); }
    /// Insert method
    const bidirectional_list_iterator<T> insert(const bidirectional_list_iterator<T>& pos, const T &data)
    {
        if (_size == 0)
        {
            _head = new Node<T>(data, _void, _void);
            _tail = _head;
        }
        else if (pos == begin())
        {
            Node<T> *tmp = new Node<T>(data, _void, _head);
            _head->prev = tmp;
            _head = tmp;
        }
        else if (pos == end())
        {
            Node<T> *tmp = new Node<T>(data, _tail, _void);
            _tail->next = tmp;
            _tail = _tail->next;
        }
        else
            throw "Incorrect parameter 'pos' in method 'insert'!";
        _size += 1;
        return pos;
    }
    /// Erase method
    const bidirectional_list_iterator<T> erase(const bidirectional_list_iterator<T>& pos)
    {
        if (size == 1)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        if (pos == begin())
        {
            _head = _head->next;
            delete _head->prev;
            _head->prev = _void;
        }
        if (pos == end())
        {
            _tail = _tail->prev;
            delete _tail->next;
            _tail->next = _void;
        }
        else
            throw "Incorrect parameter 'pos' in method 'insert'!";
        _size -= 1;
    }
    /**
     * Change size of List
     * \param[in] new_size New size of list
     */
    void resize(size_t new_size)
    {
        if (new_size > 10000000)
            throw "MemoryError: Over 10000000 bytes memory requested!";
        else if (new_size > _size)
        {
            for (size_t i = 0; i < new_size - _size; i++)
                insert(end(), T());
        }
        else if (new_size < _size)
        {
            for (size_t i = 0; i < _size - new_size; i++)
                    erase(end());
        }
    }
    /// Output method
    void output()
    {
        Node<T>* tmp = _head;
        std::cout << "[";
        for (; tmp->next != _void; tmp = tmp->next)
            std::cout << *tmp << ", ";
        std::cout << *tmp << "]" << std::endl;
    }
};