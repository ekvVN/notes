//
// Created by ekvvn on 06.09.17.
//

#ifndef UTILS_TESTVARIADICTEMPLATE_H
#define UTILS_TESTVARIADICTEMPLATE_H

#include <cstddef>
#include <tuple>
#include <memory>

enum coder_type
{
    coder1,
    coder2,
    coder3,
    coder4
    // ...
};

template <coder_type type, int TMagic, typename TValue>
class coder : public std::vector<TValue>
{
    unsigned char *_data;
    size_t _size;
public:
    coder(unsigned char *data, size_t size) : _data(data), _size(size) { }

    coder(std::initializer_list<TValue> list)
            : std::vector<TValue>(list) { }
};

class CC
{
public:
    using coder1 = coder<coder_type::coder1, 6, unsigned char>;
    using coder2 = coder<coder_type::coder1, 8, unsigned char>;
    using coder3 = coder<coder_type::coder1, 10, unsigned short>;
    using coder4 = coder<coder_type::coder1, 14, unsigned short>;

};

template <template <typename, typename...> class ContainerType,
        typename ValueType, typename... Args>
void print_container(const ContainerType<ValueType, Args...>& c) {
    for (const auto& v : c) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}

template <template <typename, typename> class ContainerType,
        typename SrcEncoder,
        typename DstEncoder>
void encode(const ContainerType<SrcEncoder, DstEncoder>& c) {
    for (const auto& v : c) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}

class IVideoType
{
public:
    virtual size_t bit_count() = 0;
    virtual size_t max_value() = 0;
};

template<size_t TBitCount>
class VideoTypeIr : public IVideoType
{

public:
    size_t bit_count() override
    {
        return TBitCount;
    }
    size_t max_value() override
    {
        return (1 << TBitCount) - 1;
    }
};

template <typename Encoder>
struct EncoderConf
{
    std::shared_ptr<Encoder> _encoder;
    std::shared_ptr<IVideoType> _videoType;

public:
    EncoderConf(std::shared_ptr<Encoder> encoder, std::shared_ptr<IVideoType> videoType)
    {
        _encoder = encoder;
        _videoType = videoType;
    }

    std::shared_ptr<Encoder> encoder()
    { return _encoder; }

    std::shared_ptr<IVideoType> videoType()
    { return _videoType; }
};

template <typename SrcEncoder, typename DstEncoder>
void encode(EncoderConf<SrcEncoder> &srcConf, EncoderConf<DstEncoder> &dstConf, int pixCount)
{
    auto src = srcConf.encoder();
    auto dst = dstConf.encoder();
    auto srcType = srcConf.videoType();
    auto dstType = dstConf.videoType();

    auto srcIt = src->begin();
    auto dstIt = dst->begin();
    for (int i = 0; i < pixCount; ++i, ++srcIt, ++dstIt)
    {
        auto srcValue = *srcIt & srcType->max_value();
        auto dstValue = srcValue & dstType->max_value();
        *dstIt = dstValue;
    }
}

template <typename SrcEncoder, typename DstEncoder>
void encode(SrcEncoder &src, IVideoType *srcType, DstEncoder &dst, IVideoType *dstType, int pixCount)
{
    auto srcIt = src.begin();
    auto dstIt = dst.begin();
    for (int i = 0; i < pixCount; ++i, ++srcIt, ++dstIt)
    {
        auto srcValue = *srcIt & srcType->max_value();
        auto dstValue = srcValue & dstType->max_value();
        *dstIt = dstValue;
    }
}

template <typename SrcEncoder, typename DstEncoder>
void encode(SrcEncoder &src, DstEncoder &dst, int pixCount)
{
    auto srcIt = src.begin();
    auto dstIt = dst.begin();
    for (int i = 0; i < pixCount; ++i, ++srcIt, ++dstIt)
    {
        auto srcValue = *srcIt;
        auto dstValue = srcValue;
        *dstIt = dstValue;
    }
}

#endif //UTILS_TESTVARIADICTEMPLATE_H
