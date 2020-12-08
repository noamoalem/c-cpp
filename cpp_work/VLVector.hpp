#ifndef CPP_EXAM_VLVECTOR_HPP
#define CPP_EXAM_VLVECTOR_HPP

#include <iostream>
#include <stdexcept>

#define EMPTY 0
#ifndef CPPWORK_VLVECTOR_HPP
#define CPPWORK_VLVECTOR_HPP
using std::size_t;


/**
 * This class represent generic vector.
 * @tparam T the type of objects.
 * @tparam StaticCapacity A given static capacity.
 */
template<class T, size_t StaticCapacity = 16>
class VLVector
{
private:
    size_t _sCapacity;
    size_t _size;
    size_t _currentCapacity;
    T *_dynamicVector;
    bool _dynamic;
    T _staticVector[StaticCapacity];

    /**
     * This class represent a VLVector iterator.
     */
    class VLVIterator
    {
    private:
        T *_current;
    public:
        typedef T value_type;
        typedef T &reference;
        typedef T *pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        /**
         * Default constructor.
         */
        VLVIterator() : _current(nullptr)
        {
        }

        /**
         * Constructor that initialize iterator to a given position.
         */
        VLVIterator(T *position) : _current(position)
        {
        }

        /**
         * Copy constructor that initialize iterator from given iterator.
         * @param iter other iterator to copy.
         */
        VLVIterator(VLVIterator const &iter) : _current(iter._current)
        {
        }
        /**
         * operator ++ postfix.
         * @return iterator to the next place.
         */
        VLVIterator &operator++()
        {
            ++_current;
            return *this;
        }
        /**
         * operator ++ prefix.
         * @return iterator to the current place.
         */
        VLVIterator operator++(int)
        {
            VLVIterator temp = *this;
            ++_current;
            return temp;
        }
        /**
         * operator -- prefix.
         * @return iterator to the backward place.
         */
        VLVIterator &operator--()
        {
            --_current;
            return *this;
        }
        /**
         * operator -- postfix.
         * @return iterator to the current place.
         */
        VLVIterator operator--(int)
        {
            VLVIterator temp = *this;
            _current--;
            return temp;
        }
        /**
         * operator +=.
         * @param num the number to move forward the iterator.
         * @return iterator to current place + num.
         */
        VLVIterator &operator+=(const int &num)
        {
            _current + num;
            return *this;
        }
        /**
         * operator -=.
         * @param num the number to move backward the iterator.
         * @return iterator to current place - num.
         */
        VLVIterator &operator-=(const int &num)
        {
            _current - num;
            return *this;
        }
        /**
         * read operator.
         * @return T object.
         */
        T operator*() const
        {
            return *_current;
        }
        /**
         * write operator.
         * @return T object.
         */
        T &operator*()
        {
            return *_current;
        }
        /**
         * @param num number to move forward the iterator.
         * @return iterator that points to current+num.
         */
        VLVIterator operator+(const int &num)
        {
            return VLVIterator(_current + num);
        }
        /**
        * @param num number to move backward the iterator.
        * @return iterator that points to current-num.
        */
        VLVIterator operator-(const int &num)
        {
            return VLVIterator(_current - num);
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if both iterators points the same object.
        */
        bool operator==(const VLVIterator &rhs) const
        {
            return _current == rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if both iterators points different object.
        */
        bool operator!=(const VLVIterator &rhs) const
        {
            return _current != rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to backward object then rhs.
        */
        bool operator<(const VLVIterator &rhs) const
        {
            return _current < rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to forward object then rhs.
        */
        bool operator>(const VLVIterator &rhs) const
        {
            return _current > rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to backward or the same object as rhs.
        */
        bool operator<=(const VLVIterator &rhs) const
        {
            return _current < rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to forward or the same object as rhs.
        */
        bool operator>=(const VLVIterator &rhs) const
        {
            return _current >= rhs._current;
        }
        /**
         * @param rhs const iterator.
         * @return the num of object T between iterator to another iterator.
         */
        difference_type operator-(const VLVIterator &rhs) const
        {
            return _current - rhs._current;
        }
    };

    /**
     * This class represent a VLVector const iterator.
     */
    class VLVConstIterator
    {
    private:
        const T *_current;
    public:
        typedef T value_type;
        typedef const T &reference;
        typedef const T *pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;

        /**
         * Default constructor.
         */
        VLVConstIterator() : _current(nullptr)
        {
        }

        /**
         * Constructor that initialize const iterator to a given position.
         */
        VLVConstIterator(T const *position) : _current(position)
        {
        }

        /**
         * Constructor that initialize const iterator from given iterator.
         * @param iter other iterator to copy.
         */
        VLVConstIterator(VLVConstIterator const &iter) : _current(iter._current)
        {
        }
        /**
         * operator ++ postfix.
         * @return const iterator to the next place.
         */
        const VLVConstIterator &operator++()
        {
            ++_current;
            return *this;
        }
        /**
         * operator ++ prefix.
         * @return const iterator to the current place.
         */
        VLVConstIterator operator++(int)
        {
            VLVConstIterator temp = *this;
            ++_current;
            return temp;
        }
        /**
         * operator -- prefix.
         * @return const iterator to the backward place.
         */
        const VLVConstIterator &operator--()
        {
            --_current;
            return *this;
        }
        /**
         * operator -- postfix.
         * @return const iterator to the current place.
         */
        VLVConstIterator operator--(int)
        {
            VLVConstIterator temp = *this;
            --_current;
            return temp;
        }
        /**
         * operator +=.
         * @param num the number to move forward the iterator.
         * @return const iterator to current place + num.
         */
        const VLVConstIterator &operator+=(const int &num)
        {
            _current + num;
            return *this;
        }
        /**
         * operator -=.
         * @param num the number to move backward the iterator.
         * @return const iterator to current place - num.
         */
        const VLVConstIterator &operator-=(const int &num)
        {
            _current - num;
            return *this;
        }
        /**
         * read operator.
         * @return T object.
         */
        T operator*() const
        {
            return *_current;
        }
        /**
         * @param num number to move forward the iterator.
         * @return const iterator that points to current+num.
         */
        VLVConstIterator operator+(const int &num)
        {
            return VLVConstIterator(_current + num);
        }
        /**
        * @param num number to move backward the iterator.
        * @return const iterator that points to current-num.
        */
        VLVConstIterator operator-(const int &num)
        {
            return VLVConstIterator(_current - num);
        }
        /**
         * @param rhs iterator to compare to.
         * @return true if both iterators points the same object.
         */
        bool operator==(const VLVConstIterator &rhs) const
        {
            return _current == rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if both iterators points different object.
        */
        bool operator!=(const VLVConstIterator &rhs) const
        {
            return _current != rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to backward object then rhs.
        */
        bool operator<(const VLVConstIterator &rhs) const
        {
            return _current < rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to forward object then rhs.
        */
        bool operator>(const VLVConstIterator &rhs) const
        {
            return _current > rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to backward or the same object as rhs.
        */
        bool operator<=(const VLVConstIterator &rhs) const
        {
            return _current < rhs._current;
        }
        /**
        * @param rhs iterator to compare to.
        * @return true if iterator points to forward or the same object as rhs.
        */
        bool operator>=(const VLVConstIterator &rhs) const
        {
            return _current >= rhs._current;
        }
        /**
         * @param rhs const iterator.
         * @return the num of object T between iterator to another iterator.
         */
        difference_type operator-(const VLVConstIterator &rhs) const
        {
            return _current - rhs._current;
        }
    };

    /**
     * This method copy the vector values from a given vector.
     * @param dynamic ture if using the dynamic array false otherwise.
     * @param rhsV a given vector to copy.
     */
    void _copyVectorValues(bool _dynamic, const VLVector &rhsV)
    {
        for (size_t i = 0; i < _size; ++i)
        {
            if (_dynamic)
            {
                _dynamicVector[i] = rhsV._dynamicVector[i];
            }
            else
            {
                _staticVector[i] = rhsV._staticVector[i];
            }
        }
    }

    /**
     * This function responsible of moving to the dynamic vector when needed.
     */
    void _staticVectorToDynamic()
    {
        _size++;
        _currentCapacity = (3 * (_size)) / 2;
        _dynamicVector = new T[_currentCapacity];
        for (size_t i = 0; i < _size - 1; ++i)
        {
            _dynamicVector[i] = _staticVector[i];
        }
        _dynamic = true;
    }

    /**
     * This function responsible of increasing the capacity of the dynamic vector when needed.
     */
    void _resizeDynamicVector()
    {
        _size++;
        _currentCapacity = (3 * (_size)) / 2;
        T *temp = new T[_currentCapacity];
        for (size_t i = 0; i < _size - 1; ++i)
        {
            temp[i] = _dynamicVector[i];
        }
        if (_dynamic)
        {
            delete[] _dynamicVector;
        }
        _dynamicVector = new T[_currentCapacity];
        for (size_t i = 0; i < _size - 1; ++i)
        {
            _dynamicVector[i] = temp[i];
        }
        delete[] temp;
    }

    /**
     * This function responsible of moving from the dynamic vector to the static vector when needed.
     */
    void _dynamicVectorToStatic(bool minus)
    {
        size_t m = 0;
        if (minus)
        {
            m = 1;
        }
        for (size_t i = 0; i < _size-m; ++i)
        {
            _staticVector[i] = _dynamicVector[i];
        }
        _currentCapacity = _sCapacity;
        delete[] _dynamicVector;
        _dynamic = false;
    }

public:
    typedef VLVIterator iterator;
    typedef VLVConstIterator const_iterator;

    /**
     * @return iterator that points to the first place of the vector.
     */
    iterator begin()
    {
        if (_dynamic)
        {
            return VLVIterator(&(_dynamicVector[0]));
        }
        else
        {
            return VLVIterator(&(_staticVector[0]));
        }
    }

    /**
     * @return iterator that points to the after last place of the vector.
     */
    iterator end()
    {
        if (_dynamic)
        {
            return VLVIterator(&_dynamicVector[_size]);
        }
        else
        {
            return VLVIterator(&_staticVector[_size]);
        }
    }

    /**
     * @return const iterator that points to the first place of the vector.
     */
    const_iterator begin() const
    {
        if (_dynamic)
        {
            return VLVConstIterator(&_dynamicVector[0]);
        }
        else
        {
            return VLVConstIterator(&_staticVector[0]);
        }
    }

    /**
     * @return const iterator that points to the after last place of the vector.
     */
    const_iterator end() const
    {
        if (_dynamic)
        {
            return VLVConstIterator(&_dynamicVector[_size]);
        }
        else
        {
            return VLVConstIterator(&_staticVector[_size]);
        }
    }

    /**
     * @return const iterator that points to the first place of the vector.
     */
    const_iterator cbegin() const
    {
        if (_dynamic)
        {
            return VLVConstIterator(&(_dynamicVector[0]));
        }
        else
        {
            return VLVConstIterator(&(_staticVector[0]));
        }
    }

    /**
     * @return const iterator that points to the after last place of the vector.
     */
    const_iterator cend() const
    {
        if (_dynamic)
        {
            return VLVConstIterator(&_dynamicVector[_size]);
        }
        else
        {
            return VLVConstIterator(&_staticVector[_size]);
        }
    }

    /**
     * Default constructor.
     */
    VLVector() : _sCapacity(StaticCapacity), _size(EMPTY), _currentCapacity(StaticCapacity),
                 _dynamicVector(nullptr), _dynamic(false)
    {
    }

    /**
     * Copy constructor.
     */
    VLVector(const VLVector &rhsV) : _sCapacity(rhsV._sCapacity),
                                     _size(rhsV._size), _currentCapacity(rhsV._currentCapacity),
                                     _dynamic(rhsV._dynamic)
    {
        if (_size > _sCapacity)
        {
            _dynamicVector = new T[_currentCapacity];
            _dynamic = true;
        }
        _copyVectorValues(_dynamic, rhsV);

    }

    /**
     * Copy from iterator constructor.
     * @tparam InputIterator input iterator.
     * @param first input iterator that point to the first object to copy.
     * @param last input iterator that point to the last object to copy (excluding the last).
     */
    template<class InputIterator>
    VLVector(InputIterator first, InputIterator last) : _sCapacity(StaticCapacity), _size(EMPTY),
                                                        _currentCapacity(StaticCapacity),
                                                        _dynamicVector(nullptr), _dynamic(false)
    {
        while (first != last)
        {
            push_back(*first);
            first++;
        }
    }

    /**
     * Destructure.
     */
    ~VLVector()
    {
        if (_dynamic)
        {
            delete[] _dynamicVector;
        }
    }

    /**
     * @return the current size of the array.
     */
    size_t size()
    {
        return _size;
    }

    /**
     * @return the current capacity of the array.
     */
    size_t capacity()
    {
        return _currentCapacity;
    }

    /**
     * @return true if the vector empty, false otherwise.
     */
    bool empty()
    {
        return _size == EMPTY;
    }

    /**
     * This method return the value of vector in index, throw exception if index is out of range.
     * @param index given index.
     * @return value of vector in index by reference.
     */
    T &at(size_t index) noexcept(false)
    {
        if (index < 0 || index >= _size)
        {
            if (_dynamic)
            {
                delete[] _dynamicVector;
            }
            throw std::out_of_range("Index out of range");
        }
        else if (_dynamic)
        {
            return _dynamicVector[index];
        }
        else
        {
            return _staticVector[index];
        }
    }

    /**
     * This method return the value of vector in index, throw exception if index is out of range.
     * @param index given index.
     * @return value of vector in index by value.
     */
    T at(unsigned long index) const noexcept(false)
    {
        if (index < 0 || index >= _size)
        {
            if (_size > _sCapacity)
            {
                delete[] _dynamicVector;
            }
            throw std::out_of_range("Index out of range");
        }
        else if (_dynamic)
        {
            return _dynamicVector[index];
        }
        else
        {
            return _staticVector[index];
        }
    }

    /**
     * This method add given T object after the last place of vector.
     * @param toAdd T object to add.
     */
    void push_back(const T &toAdd)
    {
        size_t currSize = _size;
        if (currSize + 1 <= _sCapacity)
        {
            _staticVector[_size] = toAdd;
            _size++;
        }
        else if (currSize == _sCapacity)
        {
            _staticVectorToDynamic();
            _dynamicVector[_size - 1] = toAdd;
        }
        else if (currSize == _currentCapacity)
        {
            _resizeDynamicVector();
            _dynamicVector[_size - 1] = toAdd;
        }
        else
        {
            _size++;
            _dynamicVector[_size - 1] = toAdd;
        }
    }

    /**
     * This method delete the last object in the vector.
     */
    void pop_back()
    {
        _size--;
        if (_size == _sCapacity)
        {
            _dynamicVectorToStatic(false);
        }
    }

    /**
     * This method delete all elements from the vector.
     */
    void clear()
    {
        if (_dynamic)
        {
            delete[] _dynamicVector;
            _dynamicVector = nullptr;
        }
        _currentCapacity = _sCapacity;
        _size = 0;
    }

    /**
     * @return pointer to the object data.
     */
    T *data()
    {
        if (_dynamic)
        {
            return _dynamicVector;
        }
        else
        {
            return _staticVector;
        }
    }

    /**
     * @return pointer to the object data, const such that it cannot change the values of vector.
     */
    const T *data() const
    {
        if (_dynamic)
        {
            return _dynamicVector;
        }
        else
        {
            return _staticVector;
        }
    }

    /**
     * Assignment of one vector - rhsV to another.
     * @param rhsV vector to copy.
     * @return reference to the lhs vector.
     */
    VLVector &operator=(const VLVector &rhsV)
    {
        if (this == &rhsV)
        {
            return *this;
        }
        if (_dynamic)
        {
            delete[] _dynamicVector;
        }
        _size = rhsV._size;
        _currentCapacity = rhsV._currentCapacity;
        if (_size > _sCapacity)
        {
            _dynamicVector = new T[_size];
            _dynamic = true;
        }
        _copyVectorValues(_dynamic, rhsV);
        return *this;
    }

    /**
     * @param index the wanted index from vector.
     * @return The value of vector at index, by reference.
     */
    T &operator[](size_t index)
    {
        if (_dynamic)
        {
            return _dynamicVector[index];
        }
        else
        {
            return _staticVector[index];
        }
    }

    /**
     * @param index the wanted index from vector.
     * @return The value of vector at index, by value.
     */
    T operator[](size_t index) const
    {
        if (_dynamic)
        {
            return _dynamicVector[index];
        }
        else
        {
            return _staticVector[index];
        }
    }

    /**
     * Two vectors equal if and only if all of their values equal.
     */
    bool operator==(const VLVector<T> &rhsV) const
    {
        if (_size != rhsV._size)
        {
            return false;
        }
        if (_dynamic)
        {
            for (size_t i = 0; i < _size; ++i)
            {
                if (_dynamicVector[i] != rhsV[i])
                {
                    return false;
                }
            }
        }
        else
        {
            for (size_t i = 0; i < _size; ++i)
            {
                if (_staticVector[i] != rhsV.at(i))
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * Two vectors not equal if at least one of their values different.
     */
    bool operator!=(const VLVector<T> &rhsV) const
    {
        return !(*this == rhsV);
    }
    /**
     * @param position given position.
     * @return The index of position in vector.
     */
    size_t _findIndex(VLVIterator &position)
    {
        T value = *position;
        for (size_t i = 0; i < _size; ++i)
        {
            if (_dynamic)
            {
                if (value == _dynamicVector[i])
                {
                    return i;
                }
            }
            else
            {
                if (value == _staticVector[i])
                {
                    return i;
                }
            }
        }
        return 0;
    }
    /**
 * @param position given position.
 * @return The index of position in vector.
 */
    size_t _findIndex(VLVConstIterator &position)
    {
        T value = *position;
        for (size_t i = 0; i < _size; ++i)
        {
            if (_dynamic)
            {
                if (value == _dynamicVector[i])
                {
                    return i;
                }
            }
            else
            {
                if (value == _staticVector[i])
                {
                    return i;
                }
            }
        }
        return 0;
    }

    /**
     * This method insert given object to the vector, before given position.
     * @param position iterator that points to specific place in the array.
     * @param toAdd object to insert to vector.
     * @return Iterator that points to the added object.
     */
    iterator insert(VLVIterator position, const T &toAdd)
    {
        size_t whereToAdd = _findIndex(position);
        if (_size == _sCapacity)
        {
            _staticVectorToDynamic();
        }
        else if (_size == _currentCapacity)
        {
            _resizeDynamicVector();
        }
        else
        {
            _size++;
        }
        T valueToPush = *position;
        T temp = toAdd;
        if (_dynamic)
        {
            valueToPush = *position;
        }
        else
        {
            valueToPush = _staticVector[whereToAdd];
        }
        for (size_t i = whereToAdd; i < _size; ++i)
        {
            if (_dynamic)
            {
                _dynamicVector[i] = temp;
                temp = valueToPush;
                if (i < _size-2)
                {
                    valueToPush = _dynamicVector[i + 1];
                }

            }
            else
            {
                _staticVector[i] = temp;
                temp = valueToPush;
                if (i < _size-2)
                {
                    valueToPush = _staticVector[i + 1];
                }
            }
        }
        if (_dynamic)
        {
            return VLVIterator(&_dynamicVector[whereToAdd]);
        }
        else
        {
            return VLVIterator(&_staticVector[whereToAdd]);
        }
    }

    /**
     * This method insert given objects to the vector, before given position.
     * @tparam InputIterator input iterator.
     * @param position iterator that points to specific place in the array.
     * @param first iterator to the first object to add.
     * @param last iterator to the first object to add (exclude this object).
     * @return iterator that points to the first object that add.
     */
    template<class InputIterator>
    iterator insert(VLVIterator &position, InputIterator first, InputIterator last)
    {
        size_t whereToAdd = _findIndex(position);
        while (first != last)
        {
            insert(position, *first);
            position++;
            first++;
        }
        if (_dynamic)
        {
            return VLVIterator(&_dynamicVector[whereToAdd]);
        }
        else
        {
            return VLVIterator(&_staticVector[whereToAdd]);
        }
    }
    /**
     * This method insert given object to the vector, before given position.
     * @param position iterator that points to specific place in the array.
     * @param toAdd object to insert to vector.
     * @return const iterator that points to the added object.
     */
    iterator insert(VLVConstIterator position, const T &toAdd)
    {
        size_t whereToAdd = _findIndex(position);
        if (_size == _sCapacity)
        {
            _staticVectorToDynamic();
        }
        else if (_size == _currentCapacity)
        {
            _resizeDynamicVector();
        }
        else
        {
            _size++;
        }
        T valueToPush = *position;
        T temp = toAdd;
        if (_dynamic)
        {
            valueToPush = *position;
        }
        else
        {
            valueToPush = _staticVector[whereToAdd];
        }
        for (size_t i = whereToAdd; i < _size; ++i)
        {
            if (_dynamic)
            {
                _dynamicVector[i] = temp;
                temp = valueToPush;
                if (i < _size-2)
                {
                    valueToPush = _dynamicVector[i + 1];
                }

            }
            else
            {
                _staticVector[i] = temp;
                temp = valueToPush;
                if (i < _size-2)
                {
                    valueToPush = _staticVector[i + 1];
                }
            }
        }
        if (_dynamic)
        {
            return VLVConstIterator(&_dynamicVector[whereToAdd]);
        }
        else
        {
            return VLVConstIterator(&_staticVector[whereToAdd]);
        }
    }
    /**
     * This method insert given objects to the vector, before given position.
     * @tparam InputIterator input iterator.
     * @param position iterator that points to specific place in the array.
     * @param first iterator to the first object to add.
     * @param last iterator to the first object to add (exclude this object).
     * @return iterator that points to the first object that add.
     */
    template<class InputIterator>
    iterator insert(VLVConstIterator &position, InputIterator first, InputIterator last)
    {
        size_t whereToAdd = _findIndex(position);
        while (first != last)
        {
            insert(position, *first);
            position++;
            first++;
        }
        if (_dynamic)
        {
            return VLVConstIterator(&_dynamicVector[whereToAdd]);
        }
        else
        {
            return VLVConstIterator(&_staticVector[whereToAdd]);
        }
    }

    /**
     * This function erase one item.
     * @param position iterator that points to the object to remove.
     * @return Iterator that points to the object that was right to the given position.
     */
    iterator erase(VLVIterator position)
    {
        if (_size - 1 == _sCapacity)
        {
            _dynamicVectorToStatic(true);
        }
        size_t whereToDel = _findIndex(position);
        for (size_t i = whereToDel; i < _size; ++i)
        {
            if (i == _size -1)
            {
                continue;
            }
            else if (_dynamic)
            {
                _dynamicVector[i] = _dynamicVector[i + 1];
            }
            else
            {
                _staticVector[i] = _staticVector[i + 1];
            }
        }
        --_size;
        if (_dynamic)
        {
            return VLVIterator(&(_dynamicVector[whereToDel]));
        }
        else
        {
            return VLVIterator(&(_staticVector[whereToDel]));
        }
    }

    /**
     * This function erase one item.
     * @param position iterator that points to the object to remove.
     * @return Iterator that points to the object that was right to the given position.
     */
    iterator erase(VLVConstIterator position)
    {
        if (_size - 1 == _sCapacity)
        {
            _dynamicVectorToStatic(true);
        }
        size_t whereToDel = _findIndex(position);
        for (size_t i = whereToDel; i < _size; ++i)
        {
            if (i == _size -1)
            {
                continue;
            }
            else if (_dynamic)
            {
                _dynamicVector[i] = _dynamicVector[i + 1];
            }
            else
            {
                _staticVector[i] = _staticVector[i + 1];
            }
        }
        --_size;
        if (_dynamic)
        {
            return VLVConstIterator(&(_dynamicVector[whereToDel]));
        }
        else
        {
            return VLVConstIterator(&(_staticVector[whereToDel]));
        }
    }
    /**
     * This function erase a unknown number of objects.
     * @param first iterator to the first object to delete.
     * @param last iterator to the last object to delete (exclude this object).
     * @return iterator that points to the object right to last.
     */
    iterator erase(VLVIterator first, VLVIterator last)
    {
        size_t numToDelete = _findIndex(last) - _findIndex(first);
        size_t startDeleteFrom = _findIndex(first);
        for (size_t i = startDeleteFrom; i < _size-numToDelete; ++i)
        {
            if (_dynamic)
            {
                _dynamicVector[i] = _dynamicVector[i + numToDelete];
            }
            else
            {
                _staticVector[i] = _staticVector[i + numToDelete];
            }
        }
        _size -= numToDelete;
        if (_size <= _sCapacity && _dynamic)
        {
            _dynamicVectorToStatic(false);
        }
        if (_dynamic)
        {
            return VLVIterator(&_dynamicVector[startDeleteFrom]);
        }
        else
        {
            return VLVIterator(&_staticVector[startDeleteFrom]);
        }
    }
    /**
     * This function erase a unknown number of objects.
     * @param first iterator to the first object to delete.
     * @param last iterator to the last object to delete (exclude this object).
     * @return const iterator that points to the object right to last.
     */
    iterator erase(VLVConstIterator first, VLVConstIterator last)
    {
        size_t numToDelete = _findIndex(last) - _findIndex(first);
        size_t startDeleteFrom = _findIndex(first);
        for (size_t i = startDeleteFrom; i < _size-numToDelete; ++i)
        {
            if (_dynamic)
            {
                _dynamicVector[i] = _dynamicVector[i + numToDelete];
            }
            else
            {
                _staticVector[i] = _staticVector[i + numToDelete];
            }
        }
        _size -= numToDelete;
        if (_size <= _sCapacity && _dynamic)
        {
            _dynamicVectorToStatic(false);
        }
        if (_dynamic)
        {
            return VLVConstIterator(&_dynamicVector[startDeleteFrom]);
        }
        else
        {
            return VLVConstIterator(&_staticVector[startDeleteFrom]);
        }
    }
};

#endif //CPPWORK_VLVECTOR_HPP

#endif //CPP_EXAM_VLVECTOR_HPP
