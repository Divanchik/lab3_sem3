/**
 * \file
 * List container
 */
#pragma once

template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;
    /// Constructor
    Node(const T &new_data, Node *new_prev, Node *new_next) : data(new_data), next(new_next), prev(new_prev) {}
};

template <typename T>
class List;
template <typename T>
class list_iterator
{
    Node<T> *node;

public:
    list_iterator() : node(nullptr) {}                   /// Default constructor
    list_iterator(Node<T> *new_node) : node(new_node) {} /// Constructor
    ~list_iterator() {}                                  /// Destructor
    /// Preincrenment
    list_iterator &operator++()
    {
        node = node->next;
        return *this;
    }
    /// Postincrement
    list_iterator operator++(int)
    {
        auto result(*this);
        node = node->next;
        return result;
    }
    /// Predecrement
    list_iterator &operator--()
    {
        node = node->prev;
        return *this;
    }
    /// Postdecrement
    list_iterator operator--(int)
    {
        auto result(*this);
        node = node->prev;
        return result;
    }

    T operator*() const { return node->data; } /// Dereferentiation
    T &operator*() { return node->data; }      /// Dereferentiation

    Node<T> *operator->() { return node; }                                /// Member access operator
    bool operator==(const list_iterator& a) const { return node == a.node; } /// Equality operator
    bool operator!=(const list_iterator& a) const { return node != a.node; } /// Inequality operator

    friend class List<T>;
};

template <typename T>
/// List class
class List
{
    Node<T> *_head;
    Node<T> *_tail;
    Node<T> *_void; /// Past-the-end Node
    size_t _size;   /// Size of list

public:
    using const_iterator = const list_iterator<T>;
    using iterator = list_iterator<T>;

    bool empty() const noexcept { return _size == 0 ? true : false; } /// \return 'true' if list is empty
    size_t size() const noexcept { return _size; }                    /// \return Size of list

    /// Default constructor
    List() : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        std::cout << "Default constructor!" << std::endl;
        _void->next = _void;
        _void->prev = _void;
    }
    /// Size constructor \param[in] new_size New size of list
    List(size_t new_size) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        std::cout << "Size constructor!" << std::endl;
        _void->next = _void;
        _void->prev = _void;

        resize(new_size);
    }
    /// Copy constructor \param[in] a List
    List(const List<T> &a) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        std::cout << "Copy constructor!" << std::endl;
        _void->next = _void;
        _void->prev = _void;

        for (auto tmp = a.begin(); tmp != a.end(); tmp++)
            insert(end(), *tmp);
    }
    /// Move constructor \param[in] a List
    List(List &&a) : _head(nullptr), _tail(nullptr), _void(new Node<T>(T(), nullptr, nullptr)), _size(0)
    {
        std::cout << "Move constructor!" << std::endl;
        _void->next = _void;
        _void->prev = _void;

        swap(a);
    }
    /// Assign copy operator \param[in] a List
    List<T> &operator=(const List<T> &a)
    {
        std::cout << "Copy assignment!" << std::endl;
        clear();
        _void = new Node<T>(T(), nullptr, nullptr);
        _void->next = _void;
        _void->prev = _void;

        for (auto tmp = a.begin(); tmp != a.end(); tmp++)
            insert(end(), *tmp);
        return *this;
    }
    /// Assign move operator \param[in] a List
    List<T> &operator=(List<T> &&a)
    {
        std::cout << "Move assignment!" << std::endl;
        clear();
        _void = new Node<T>(T(), nullptr, nullptr);
        _void->next = _void;
        _void->prev = _void;

        swap(a);
        return *this;
    }
    /// Destructor
    ~List()
    {
        std::cout << "Destructor!" << std::endl;
        clear();
    }

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
        Node<T> *tmp = _head;
        if (_size != 0)
        {
            while (_head != _void)
            {
                tmp = _head;
                _head = _head->next;
                delete tmp;
            }
            _size = 0;
        }
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
        return tmp->data;
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
        return tmp->data;
    }

    /// \return Constant begin iterator
    const_iterator begin() const noexcept { return list_iterator<T>(_head); }
    /// \return Constant past-the-end iterator
    const_iterator end() const noexcept { return list_iterator<T>(_void); }
    /// \return Begin iterator
    iterator begin() noexcept { return list_iterator<T>(_head); }
    /// \return Past-the-end iterator
    iterator end() noexcept { return list_iterator<T>(_void); }

    /// Insert method
    const_iterator insert(const list_iterator<T> &pos, const T &data)
    {
        std::cout << "Insert " << data << std::endl;
        if (_size == 0)
        {
            _head = new Node<T>(data, _void, _void);
            _tail = _head;
        }
        else if (pos == begin())
        {
            Node<T> *tmp = new Node<T>(data, _void, _head);
            tmp->next->prev = tmp;
            _head = tmp;
        }
        else if (pos == end())
        {
            Node<T> *tmp = new Node<T>(data, _tail, _void);
            tmp->prev->next = tmp;
            _tail = _tail->next;
        }
        else
        {
            Node<T> *tmp = new Node<T>(data, pos.node->prev, pos.node);
            tmp->next->prev = tmp;
            tmp->prev->next = tmp;
        }
        _size += 1;
        return list_iterator<T>(pos.node->prev);
    }
    /// Erase method
    const_iterator erase(const list_iterator<T> &pos)
    {
        std::cout << "Erase " << pos.node->data << std::endl;
        Node<T> *ret;
        if (_size == 1)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            ret = nullptr;
        }
        else if (pos == begin())
        {
            _head = _head->next;
            delete _head->prev;
            _head->prev = _void;
            ret = _head;
        }
        else if (pos == end())
        {
            _tail = _tail->prev;
            delete _tail->next;
            _tail->next = _void;
            ret = _tail;
        }
        else
        {
            Node<T> *tmp = pos.node;
            ret = tmp->next;
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            delete tmp;
        }
        _size -= 1;
        return list_iterator<T>(ret);
    }
    /**
     * Change size of List
     * \param[in] new_size New size of list
     */
    void resize(size_t new_size)
    {
        std::cout << "Resize " << _size << " -> " << new_size << std::endl;
        if (new_size > 10000000)
            throw "MemoryError: Too many memory requested!";
        
        if (new_size > _size)
            for (size_t i = 0; i < new_size - _size; i++)
                insert(end(), T());
        else if (_size > new_size)
            for (size_t i = 0; i < _size - new_size; i++)
                erase(end());
    }
};