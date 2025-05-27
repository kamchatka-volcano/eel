#ifndef EEL_UTILITY_H
#define EEL_UTILITY_H

#include "contract.h"
#include "type_traits.h"
#include <cstddef>
#include <exception>
#include <type_traits>
#include <utility>

namespace eel {

[[noreturn]] inline void unreachable() noexcept
{
    std::terminate();
}

template<typename T>
inline constexpr auto dependent_false = false;

using ssize_t = std::common_type_t<ptrdiff_t, std::make_signed_t<std::size_t>>;
using index_t = ssize_t;

template<class C>
constexpr auto ssize(const C& c) -> std::common_type_t<ptrdiff_t, std::make_signed_t<decltype(c.size())>>
{
    using R = std::common_type_t<ptrdiff_t, std::make_signed_t<decltype(c.size())>>;
    return static_cast<R>(c.size());
}

template<class T, std::ptrdiff_t N>
constexpr ptrdiff_t ssize(const T (&)[N]) noexcept
{
    return N;
}

namespace detail {
template<std::size_t N, std::size_t... Ints>
constexpr auto shiftSequence(std::index_sequence<Ints...>) -> std::index_sequence<N + Ints...>;
}

template<std::size_t Begin, std::size_t End>
using make_index_range = decltype(detail::shiftSequence<Begin>(std::make_index_sequence<End - Begin>()));

template<typename T>
constexpr decltype(auto) deref(T&& obj)
{
    static_assert(is_dereferencable_v<T>, "Object passed to eel::deref() must be dereferencable through operator*");
    static_assert(std::is_convertible_v<T, bool>, "Object passed to eel::deref() must be convertible to bool");

    precondition(obj, EEL_LINE);
    return *obj;
}

} //namespace eel

#endif //EEL_UTILITY_H