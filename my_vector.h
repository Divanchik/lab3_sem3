/**
 * \file
 * MyVector container
 */
#pragma once

template<typename T>
class MyVector
{
    /// Data array
    T* _data;
    /// Size of used space
    size_t _size;
    /// Size of actual space
    size_t _capacity;

    public:
    using iterator = T*;
    using const_iterator = const T*;

    /// \return Size of used space
    size_t size() const noexcept {return _size;}
    /// \return Size of actual space
    size_t capacity() const noexcept {return _capacity;}
    /// Default constructor
    MyVector(): _data(nullptr), _size(0), _capacity(0) {}
    /// Copy constructor \param[in] a MyVector
    MyVector(const MyVector<T>& a): _data(new T[a._capacity]), _size(a._size), _capacity(a._capacity)
    {
        for (size_t i = 0; i < _size; ++i)
            _data[i] = a[i];
    }
    /// Move constructor \param[in] a MyVector
    MyVector(MyVector<T>&& a) noexcept : _data(a._data), _size(a._size), _capacity(a._capacity)
    {
        a._data = nullptr;
    }
    /// Assign copy operator \param[in] a MyVector
    MyVector<T>& operator=(const MyVector<T>& a)
    {
        if (&a == this)
            return *this;
        reallocate(a.capacity());
        for (size_t i = 0; i < a.size(); i++)
            _data[i] = a[i];
        return *this;
    }
    /// Assign move operator \param[in] a MyVector
    MyVector<T>& operator=(MyVector<T>&& a) noexcept
    {
        if (&a == this)
            return *this;
        _data = a._data;
        _size = a._size;
        _capacity = a._capacity;
        a._data = nullptr;
        return *this;
    }
    /// Destructor
    ~MyVector()
    {
        delete[] _data;
    }
    /// Swap \param[in, out] a MyVector
    void swap(MyVector<T>& a) noexcept
    {
        std::swap(_data, a._data);
        std::swap(_size, a._size);
        std::swap(_capacity, a._capacity);
    }
    /// Clean vector
    void clean() noexcept
    {
        delete[] _data;
        _data = nullptr;
        _size = 0;
        _capacity = 0;
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T& operator [](size_t index)
    {
        if (index >= _size)
            throw "Access error: Index out of range!";
        return _data[index];
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    const T& operator [](size_t index) const
    {
        if (index >= _size)
            throw "Access error: Index out of range!";
        return _data[index];
    }
    /// \return Iterator to beginning
    const_iterator begin() const {return _data;}
    /// \return Iterator to end
    const_iterator end() const {return _data + _size;}
    /**
     * Reallocate array without data copying
     * \param[in] new_size New size of array
     */
    void reallocate(size_t new_size)
    {
        clean();
        _data = new T[new_size];
        _capacity = new_size;
    }
    /**
     * Change size of vector
     * \param[in] new_size New size of array
     */
    void resize(size_t new_size)
    {
        if (new_size <= _capacity - 1)
            _size = new_size;
        else
        {
            T* tmp = new T[new_size + 100];
            _capacity = new_size + 100;
            for (size_t i = 0;i < _size; i++)
                tmp[i] = _data[i];
            _size = new_size;
            _data = tmp;
        }
    }
};
