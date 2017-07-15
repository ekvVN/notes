#ifndef UTILS_VAL_CONTAINER_H
#define UTILS_VAL_CONTAINER_H

#include <c++/iterator>

/**
 * Контейнер для упакованных значений
 * @tparam TBitCount - Количество бит на элемент
 * @tparam TDataType - Тип указателя на массив байт
 * @tparam TValueType - Тип значения
 */
template<size_t TBitCount, typename TDataType, typename TValueType>
//    typename std::enable_if<std::is_integral<TValueType>::value, int>::type = 0>
class val_container {
public:
    // Количество элементов умещающихся в целое количество байт
    static size_t vals_count_in_block;
    // Количество байт умещающиее целое количество элементов, размер которых TBitCount в битах
    static size_t bytes_count_in_block;
    // Максимальное значение
    static TValueType max_value;

protected:
    using data_type = TDataType;

    // Указатель на начало данных
    data_type* _data;
    // Размер данных, в байтах
    size_t _size;

public:
    template<typename TValue>
    class val_iterator : public std::iterator<std::random_access_iterator_tag, TValue, int> {
        friend class val_container;

    protected:
        // Указатель на начало данных
        TDataType* _it_data;
        // Индекс текущего элемента
        size_t _val_idx;
//        val_proxy _px;

        val_iterator(TDataType* data) : _it_data(data), _val_idx(0){}
        val_iterator(TDataType* data, unsigned int val_idx) : _it_data(data), _val_idx(val_idx){}

    public:
        //template<typename TValue>
        //class val_proxy : public std::iterator<std::random_access_iterator_tag, TValue, int> {
        //    val_iterator<TValue>* _it;
        //public:
        //    val_proxy(val_iterator<TValue>* it) : _it(it) { }
        //};

        using it_type = val_iterator<TValue>;
        using pointer = TValue*;
        using reference = TValue&;
        using difference_type = typename std::iterator<std::random_access_iterator_tag, TValue, int>::difference_type;

        template<typename V2>
        val_iterator(const val_iterator<V2>& other) : _it_data(other._it_data), _val_idx(other._val_idx) {}

        template<typename V2>
        val_iterator& operator=(const val_iterator<V2>& other) {
            _it_data = other._it_data;
            _val_idx = other._val_idx;
            return *this;
        }

        //reference operator*() const {
        //    //auto tmp = get_value();
        //    return val_proxy(nullptr);
        //}
//
        //pointer operator->() const {
        //    // ToDo
        //    return *this;
        //}

        operator TValue() const {
            return get_value();
        }

        val_iterator& operator++() {
            if(_val_idx == vals_count_in_block - 1){
                _it_data += bytes_count_in_block;
                _val_idx = 0;
            }
            else {
                ++_val_idx;
            }
            return *this;
        }

        val_iterator& operator--() {
            if(_val_idx == 0){
                _it_data -= bytes_count_in_block;
                _val_idx = vals_count_in_block - 1;
            }
            else {
                --_val_idx;
            }
            return *this;
        }

        val_iterator operator++(int) {
            val_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        val_iterator operator--(int) {
            val_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        val_iterator& operator+=(const difference_type& n) {
            auto idx = _val_idx + n;
            _it_data += (idx / vals_count_in_block) * bytes_count_in_block;
            _val_idx += idx % vals_count_in_block;
            return *this;
        }

        val_iterator operator+(const difference_type& n) const {
            val_iterator tmp(*this);
            tmp += n;
            return tmp;
        }

        val_iterator& operator-=(const difference_type& n) {
            // ToDo
            if(n <= _val_idx)
            {
                _val_idx -= n;
                return *this;
            }

            auto idx = _val_idx + n;
            auto diff_idx = (n % vals_count_in_block)- _val_idx;
            _it_data += (idx / vals_count_in_block) * bytes_count_in_block;
            _val_idx += vals_count_in_block - diff_idx;
            return *this;
        }

        val_iterator operator-(const difference_type& n) const {
            val_iterator tmp(*this);
            tmp -= n;
            return tmp;
        }

        reference operator[](const difference_type& n) const {
            // ToDo
            return (*_it_data)[_val_idx + n];
        }

        bool operator==(const val_iterator& other) const {
            return _it_data == other._it_data && _val_idx == other._val_idx;
        }

        bool operator!=(const val_iterator& other) const {
            return !(*this == other);
        }

        bool operator<(const val_iterator& other) const {
            return _it_data == other._it_data
                   ? _val_idx < other._val_idx
                   : _it_data < other._it_data;
        }

        bool operator<=(const val_iterator& other) const {
            return *this < other || *this == other;
        }

        bool operator>(const val_iterator& other) const {
            return !(*this <= other);
        }

        bool operator>=(const val_iterator& other) const {
            return !(*this < other);
        }

//        difference_type operator+(const val_iterator& other) const {
//            // ToDo
//            return _val_idx + other._val_idx;
//        }
//
//        difference_type operator-(const val_iterator& other) const {
//            // ToDo
//            return _val_idx - other._val_idx;
//        }

        TValue get_value() const
        {
            size_t end_bit_idx = (_val_idx + 1) * TBitCount;
            size_t end_byte_idx = end_bit_idx / 8;

            size_t data_shift = 8 - end_bit_idx % 8;
            size_t lo_shift = data_shift;
            size_t hi_shift = sizeof(TValue) * 8 - data_shift;

            auto value_pos = static_cast<TValue*>(_it_data + end_byte_idx);
            TValue lo = *value_pos >> lo_shift;
            TValue hi = _val_idx > 0 ? *(value_pos - 1) << hi_shift : 0;

            return (hi | lo) & max_value;
        }

        void set_value(TValue value) const
        {
            TValue val = value & max_value;

            size_t end_bit_idx = (_val_idx + 1) * TBitCount;
            size_t end_byte_idx = end_bit_idx / 8;

            size_t data_shift = 8 - end_bit_idx % 8;
            size_t lo_shift = data_shift;
            size_t hi_shift = sizeof(TValue) * 8 - data_shift;

            auto value_pos = static_cast<TValue*>(_it_data + end_byte_idx);

            TValue &lo = *value_pos;
            lo = (lo & ~(max_value << lo_shift)) | (val << lo_shift);

            if(_val_idx > 0)
            {
                TValue &hi = *(value_pos - 1);
                hi = (hi & ~(max_value >> hi_shift)) | (val >> hi_shift);
            }
        }
    };

    using iterator = val_iterator<TValueType>;
    using const_iterator = val_iterator<const TValueType>;

    val_container(TDataType* data, size_t size) : _data(data), _size(size)
    {
        static_assert(sizeof(TDataType) == 1, "sizeof TDataType must be 1 byte");
        static_assert(TBitCount >= 1, "TBitCount must be at least 1 bit");

        static volatile bool s = init(size);

        if(size % bytes_count_in_block != 0)
            throw std::invalid_argument(std::string("size: ") +  std::to_string(size)+ " % " + std::to_string(bytes_count_in_block) + " != 0");
    }
    val_container(TDataType& data, size_t size) : val_container(&data, size) {}

    iterator begin() {
        return iterator(_data);
    }

    const_iterator begin() const {
        return const_iterator(_data);
    }

    const_iterator cbegin() const {
        return const_iterator(_data);
    }

    iterator end() {
        return iterator(_data + _size);
    }

    const_iterator end() const {
        return const_iterator(_data + _size);
    }

    const_iterator cend() const {
        return const_iterator(_data + _size);
    }
private:
    static bool init(size_t size)
    {
        size_t bits = 0;
        size_t data_size_in_bits = sizeof(TDataType) * 8;
        do
        {
            vals_count_in_block++;
            bits += TBitCount;
        }
        while(bits % data_size_in_bits != 0);

        bytes_count_in_block = bits / 8;
        max_value <<=  TBitCount;
        max_value--;

        return true;
    }
};

template<size_t TBitCount, typename TDataType, typename TValueType>
size_t val_container<TBitCount, TDataType, TValueType>::vals_count_in_block = 0;

template<size_t TBitCount, typename TDataType, typename TValueType>
size_t val_container<TBitCount, TDataType, TValueType>::bytes_count_in_block = 0;

template<size_t TBitCount, typename TDataType, typename TValueType>
TValueType val_container<TBitCount, TDataType, TValueType>::max_value = 1;

#endif //UTILS_VAL_CONTAINER_H
