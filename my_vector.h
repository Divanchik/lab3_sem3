/**
 * \file
 * Vector container
 */
#pragma once

template<typename T>
class Vector
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
    Vector(): _data(nullptr), _size(0), _capacity(0) {std::cout << "Default constructor!" << std::endl;}
    /// Constructor, allocating demanded memory \param[in] new_size New size of array
    Vector(size_t new_size): _data(new T[new_size + 1]), _size(new_size), _capacity(new_size + 1) {std::cout << "Size constructor!" << std::endl;}
    /// Copy constructor \param[in] a Vector
    Vector(const Vector<T>& a): _data(new T[a._capacity]), _size(a._size), _capacity(a._capacity)
    {
        std::cout << "Copy constructor!" << std::endl;
        for (size_t i = 0; i < _size; ++i)
            _data[i] = a[i];
    }
    /// Move constructor \param[in] a Vector
    Vector(Vector<T>&& a) noexcept : _data(a._data), _size(a._size), _capacity(a._capacity)
    {
        std::cout << "Move constructor!" << std::endl;
        a._data = nullptr;
        a._size = 0;
        a._capacity = 0;
    }
    /// Assign copy operator \param[in] a Vector
    Vector<T>& operator=(const Vector<T>& a)
    {
        std::cout << "Copy assign!" << std::endl;
        Vector<T> tmp(a);
        swap(tmp);
        return *this;
    }
    /// Assign move operator \param[in] a Vector
    Vector<T>& operator=(Vector<T>&& a) noexcept
    {
        std::cout << "Move assign!" << std::endl;
        swap(a);
        return *this;
    }
    /// Destructor
    ~Vector()
    {
        std::cout << "Destructor!" << std::endl;
        delete[] _data;
    }
    /// Swap \param[in, out] a Vector
    void swap(Vector<T>& a) noexcept
    {
        std::cout << "Swap!" << std::endl;
        std::swap(_data, a._data);
        std::swap(_size, a._size);
        std::swap(_capacity, a._capacity);
    }
    /// CleanVector
    void clear() noexcept
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
        // std::cout << "Access to [" << index << "] element!" << std::endl;
        return _data[index];
    }
    /**
     * Access operator
     * \param[in] index Index of element
     */
    T operator [](size_t index) const
    {
        if (index >= _size)
            throw "Access error: Index out of range!";
        // std::cout << "Access to value of [" << index << "] element!" << std::endl;
        return _data[index];
    }
    /// \return Iterator to beginning
    const_iterator begin() const {return _data;}
    /// \return Iterator to end
    const_iterator end() const {return _data + _size;}
    iterator insert(const_iterator pos, const T& value)
    {
        if (pos == end())
        {
            std::cout << "Inserting element in the end!" << std::endl;
            resize(_size + 1);
            _data[_size - 1] = value;
            return _data + _size - 1;
        }
        std::cout << "Inserting element!" << std::endl;
        resize(_size + 1);
        T* tmp = _data + _size - 1;
        for (;tmp != pos; tmp--)
            *(tmp) = std::move_if_noexcept(*(tmp - 1));
        *tmp = value;
        return tmp;
    }
    iterator erase(const_iterator pos)
    {
        size_t index = pos - begin();
        for (size_t i = index; i < _size - 1; i++)
            _data[i] = std::move_if_noexcept(_data[i+1]);
        resize(_size - 1);
        return _data;
    }
    /**
     * Change size ofVector
     * \param[in] new_size New size of array
     */
    void resize(size_t new_size)
    {
        std::cout << "Resize from " << _size << " to " << new_size << "!" << std::endl;
        if (_capacity == 0)
        {
            _capacity = new_size + 100;
            _data = new T[_capacity];
            _size = new_size;
        }
        else
        {
            if (new_size <= _capacity - 1)
                _size = new_size;
            else
            {
                T* tmp = new T[new_size + 100];
                for (size_t i = 0;i < _size; i++)
                    tmp[i] = _data[i];
                clear();
                _data = tmp;
                _size = new_size;
                _capacity = new_size + 100;
            }
        }
    }
    /// Output method
    void output()
    {
        std::cout << "[";
        for (size_t i = 0;i < _size - 1;i++)
            std::cout << _data[i] << ", ";
        std::cout << _data[_size - 1] << "]" << std::endl;
    }
};
template<typename T>
/// Output overload for Vector
std::ostream& operator<<(std::ostream& os, const Vector<T>& obj)
{
    std::cout << "[";
    if (obj.size() > 0)
    {
        for (size_t i = 0;i < obj.size() - 1;i++)
            std::cout << obj[i] << ", ";
        std::cout << obj[obj.size() - 1];
    }
    else
        std::cout << " ";
    std::cout << "]";
    return os;
}
