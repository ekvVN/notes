#ifndef UTILS_VAL_CONTAINER_H
#define UTILS_VAL_CONTAINER_H

#include <c++/iterator>

template<size_t TBitCount, typename TDataType, typename TValueType>
struct val_help
{
    // Количество элементов умещающихся в целое количество байт
    static size_t vals_count_in_block;
    // Количество байт умещающиее целое количество элементов, размер которых TBitCount в битах
    static size_t bytes_count_in_block;

    static TValueType max_value;

    static bool init()
    {
        vals_count_in_block = 0;
        bytes_count_in_block = 0;
        max_value = 1;

        constexpr size_t value_size_in_bits = sizeof(TValueType) * 8;
        static_assert(TBitCount >= 1, "TBitCount must be at least 1 bit");
        static_assert(TBitCount <= value_size_in_bits, "TValueType doesn't have enough bit");
        static_assert(sizeof(TDataType) == 1, "sizeof TDataType must be 1 byte");

        size_t bits = 0;
        size_t data_size_in_bits = sizeof(TDataType) * 8;
        do {
            vals_count_in_block++;
            bits += TBitCount;
        } while (bits % data_size_in_bits != 0);

        bytes_count_in_block = bits / 8;
        max_value = (1 << TBitCount) - 1;

        return true;
    }
};

template<size_t TBitCount, typename TDataType, typename TValueType>
size_t val_help<TBitCount, TDataType, TValueType>::vals_count_in_block = 0;

template<size_t TBitCount, typename TDataType, typename TValueType>
size_t val_help<TBitCount, TDataType, TValueType>::bytes_count_in_block = 0;

template<size_t TBitCount, typename TDataType, typename TValueType>
TValueType val_help<TBitCount, TDataType, TValueType>::max_value = 1;

template<size_t TBitCount, typename TDataType, typename TValueType>
class val_reference
{
    using h = val_help<TBitCount, TDataType, TValueType>;
    TDataType* _data;
    size_t _val_idx;

public:
    val_reference() : _data(nullptr), _val_idx(0) {}
    val_reference(TDataType* data, size_t val_idx) : _data(data), _val_idx(val_idx) {}

    operator TValueType() const
    { return get_value(); }

    val_reference& operator=(TValueType val)
    {
        set_value(val);
        return *this;
    }

    val_reference& operator=(const val_reference rhs) const
    { return *this = TValueType(rhs); }

    bool operator==(const val_reference rhs) const
    { return TValueType(*this) == TValueType(rhs); }

    bool operator<(const val_reference rhs) const
    { return TValueType(*this) < TValueType(rhs); }

    // ToDo other operation

    size_t idx() const
    { return _val_idx; }
private:

    TValueType get_value() const
    {
        size_t end_bit_idx = (_val_idx + 1) * TBitCount;
        size_t end_byte_idx = end_bit_idx / 8;

        size_t data_shift = 8 - end_bit_idx % 8;
        size_t lo_shift = data_shift;
        size_t hi_shift = sizeof(TValueType) * 8 - data_shift;

        auto value_pos = (TValueType*)(_data + end_byte_idx);
        TValueType lo = *value_pos >> lo_shift;
        TValueType hi = _val_idx > 0 ? *(value_pos - 1) << hi_shift : 0;

        return (hi | lo) & h::max_value;
    }

    void set_value(TValueType value)
    {
        TValueType val = value & h::max_value;

        size_t end_bit_idx = (_val_idx + 1) * TBitCount;
        size_t end_byte_idx = end_bit_idx / 8;

        size_t data_shift = 8 - end_bit_idx % 8;
        size_t lo_shift = data_shift;
        size_t hi_shift = sizeof(TValueType) * 8 - data_shift;

        auto value_pos = static_cast<TValueType*>(_data + end_byte_idx);

        TValueType &lo = *value_pos;
        lo = (lo & ~(h::max_value << lo_shift)) | (val << lo_shift);

        if(_val_idx > 0)
        {
            TValueType &hi = *(value_pos - 1);
            hi = (hi & ~(h::max_value >> hi_shift)) | (val >> hi_shift);
        }
    }
};

template<size_t TBitCount, typename TDataType, typename TValueType>
class val_iterator : public std::iterator<std::random_access_iterator_tag, TValueType>
{
    using h = val_help<TBitCount, TDataType, TValueType>;
    TDataType *_data;
    size_t _val_idx;

public:
    using reference = val_reference<TBitCount, TDataType, TValueType>;
    using pointer = val_reference<TBitCount, TDataType, TValueType>*;
    using iterator = val_iterator<TBitCount, TDataType, TValueType>;
    using difference_type = int;

    val_iterator(TDataType* data) : _data(data), _val_idx(0){}
    val_iterator(TDataType* data, unsigned int val_idx) : _data(data), _val_idx(val_idx){}
    val_iterator(const iterator& rhs) : _data(rhs._data), _val_idx(rhs._val_idx) {}

    iterator& operator=(const iterator& rhs)
    {
        _data = rhs._data;
        _val_idx = rhs._val_idx;
        return *this;
    }

    reference operator*() const
    { return reference(_data, _val_idx); }

    reference operator[](const difference_type& n) const
    { return *(*this + n); }

    iterator& operator++()
    {
        if(_val_idx == h::vals_count_in_block - 1)
        {
            _data += h::bytes_count_in_block;
            _val_idx = 0;
        }
        else
        {
            ++_val_idx;
        }
        return *this;
    }

    iterator& operator--()
    {
        if(_val_idx == 0)
        {
            _data -= h::bytes_count_in_block;
            _val_idx = h::vals_count_in_block - 1;
        }
        else
        {
            --_val_idx;
        }
        return *this;
    }

    iterator operator++(int)
    {
        iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    iterator operator--(int)
    {
        iterator tmp(*this);
        --(*this);
        return tmp;
    }

    iterator& operator+=(const difference_type& n)
    {
        auto idx = _val_idx + n;
        _data += (idx / h::vals_count_in_block) * h::bytes_count_in_block;
        _val_idx = idx % h::vals_count_in_block;
        return *this;
    }

    iterator operator+(const difference_type& n) const
    {
        iterator tmp(*this);
        tmp += n;
        return tmp;
    }

    iterator& operator-=(const difference_type& n)
    {
        if(n <= _val_idx)
        {
            _val_idx -= n;
            return *this;
        }

        auto diff_idx = (n % h::vals_count_in_block) - _val_idx;
        auto idx = n - diff_idx;
        _data -= (idx / h::vals_count_in_block + 1) * h::bytes_count_in_block;
        _val_idx = h::vals_count_in_block - diff_idx;
        return *this;
    }

    iterator operator-(const difference_type& n) const
    {
        iterator tmp(*this);
        tmp -= n;
        return tmp;
    }

    bool operator==(const iterator& rhs) const
    {
        return _data == rhs._data && _val_idx == rhs._val_idx;
    }

    bool operator!=(const iterator& rhs) const
    {
        return !(*this == rhs);
    }

    bool operator<(const iterator& rhs) const
    {
        return _data == rhs._data
            ? _val_idx < rhs._val_idx
            : _data < rhs._data;
    }

    bool operator<=(const iterator& rhs) const
    {
        return *this < rhs || *this == rhs;
    }

    bool operator>(const iterator& rhs) const
    {
        return !(*this <= rhs);
    }

    bool operator>=(const iterator& rhs) const
    {
        return !(*this < rhs);
    }
};

/**
 * Контейнер для упакованных значений
 * @tparam TBitCount - Количество бит на элемент
 * @tparam TDataType - Тип указателя на массив байт
 * @tparam TValueType - Тип значения
 */
template<size_t TBitCount, typename TDataType, typename TValueType,
    typename std::enable_if<std::is_integral<TValueType>::value, int>::type = 0>
class val_container
{
    using h = val_help<TBitCount, TDataType, TValueType>;
    TDataType* _data;
    size_t _size;

public:
    using value_type = TValueType;
    using size_type = size_t;
    using difference_type = int;
    using reference = val_reference<TBitCount, TDataType, TValueType>;
    using const_reference = TValueType;
    using pointer = val_reference<TBitCount, TDataType, TValueType>*;
    using const_pointer = const TValueType*;
    using iterator = val_iterator<TBitCount, TDataType, TValueType>;
    using const_iterator = val_iterator<TBitCount, TDataType, const TValueType>;

    val_container(TDataType* data = nullptr, size_t size = 0) : _data(data), _size(size)
    {
        static_assert(sizeof(TDataType) == 1, "sizeof TDataType must be 1 byte");
        static_assert(TBitCount >= 1, "TBitCount must be at least 1 bit");

        static volatile bool s = h::init();

        if(size % h::bytes_count_in_block != 0)
            throw std::invalid_argument(std::string("size: ") +  std::to_string(size)+ " % " + std::to_string(h::bytes_count_in_block) + " != 0");
    }
    val_container(TDataType& data, size_t size) : val_container(&data, size) {}

    iterator begin()
    { return iterator(_data); }

    const_iterator begin() const
    { return const_iterator(_data); }

    const_iterator cbegin() const
    { return const_iterator(_data); }

    iterator end()
    { return iterator(_data + _size); }

    const_iterator end() const
    { return const_iterator(_data + _size); }

    const_iterator cend() const
    { return const_iterator(_data + _size); }

    size_type size() const
    { return _size; }

    bool empty() const
    { return begin() == end(); }

    reference operator[](size_type n)
    { return *(iterator(_data) + n); }

    const_reference operator[](size_type n) const
    { return *(const_iterator(_data) + n); }
};

#endif //UTILS_VAL_CONTAINER_H
