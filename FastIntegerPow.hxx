#pragma once

#include <cstdint>

#include <array>
#include <utility>

template <uintmax_t N, uintmax_t Exp>
struct IntegerPower
{
    static constexpr uintmax_t value = (Exp%2==1)
        ? N*IntegerPower<N*N, (Exp-1)/2>::value
        : IntegerPower<N*N, Exp/2>::value;
};

template <uintmax_t N>
struct IntegerPower<N, 0>
{
    static constexpr uintmax_t value = 1;
};

template <uintmax_t N, uintmax_t MaxExp, uintmax_t... I>
constexpr std::array<uintmax_t, MaxExp>
ExpValueList(std::index_sequence<I...>)
{
    return {{ IntegerPower<N, I>::value... }};
}

//! @brief Compile Time FastIntegerPow, construct table of N^[0, MaxExp) at first call.
template <uintmax_t N, uintmax_t MaxExp>
uintmax_t
FastIntegerPow(std::size_t exp)
{
    static auto valueList = ExpValueList<N, MaxExp>(std::make_index_sequence<MaxExp>{});
    return valueList[exp];
}
