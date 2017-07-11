//
// Created by User on 11.07.2017.
//

#ifndef UTILS_OFFSET_OF
#define UTILS_OFFSET_OF

#include <cstddef>
#include <type_traits>
#include <typeindex>

template <typename TMember, typename TClass>
struct offset_of_impl
{
    static TClass object;

    static constexpr size_t offset(TMember TClass::*member)
    {
        return address_of_member(member) - address_of_class();
    }

private:
    static constexpr size_t address_of_class()
    {
        return size_t(&(offset_of_impl<TMember, TClass>::object));
    }

    static constexpr size_t address_of_member(TMember TClass::*member)
    {
        return size_t(&(object.*member));
    }
};

template <typename T1, typename T2>
T2 offset_of_impl<T1, T2>::object;

template <typename TMember, typename TClass>
inline constexpr size_t offset_of(TMember TClass::*member)
{
    static_assert(std::is_standard_layout<TClass>(), "Class must have standard layout");
    return offset_of_impl<TMember, TClass>::offset(member);
}

#endif //UTILS_OFFSET_OF
