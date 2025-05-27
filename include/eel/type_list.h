#ifndef EEL_TYPE_LIST_H
#define EEL_TYPE_LIST_H

#include "type_traits.h"
#include "utility.h"
#include <functional>
#include <tuple>

namespace eel {
template<typename... Ts>
class type_list;

namespace detail {

template<typename... T>
struct TypeList {};

template<typename TList, std::size_t I>
struct TypeListAt;

template<typename TFront, typename... TBack>
struct TypeListAt<TypeList<TFront, TBack...>, 0> {
    using type = TFront;
};

template<typename TFront, typename... TBack, std::size_t I>
struct TypeListAt<TypeList<TFront, TBack...>, I> {
    using type = typename TypeListAt<TypeList<TBack...>, I - 1>::type;
};

template<typename TList, std::size_t... I>
constexpr auto makeTypeListSlice(std::index_sequence<I...>) -> type_list<typename TypeListAt<TList, I>::type...>;

} //namespace detail

template<typename... Ts>
class type_list {
    using list = detail::TypeList<Ts...>;

public:
    constexpr type_list() = default;

    template<typename... TTypeListElems>
    constexpr type_list(std::tuple<TTypeListElems...>){}

    static constexpr int size()
    {
        return sizeof...(Ts);
    };

    template<std::size_t I>
    static constexpr auto at()
    {
        return type_identity<typename detail::TypeListAt<list, I>::type>{};
    }

    template<std::size_t First, std::size_t Size>
    static constexpr auto slice()
    {
        static_assert(First + Size <= size());
        return decltype(detail::makeTypeListSlice<list>(make_index_range<First, First + Size>{})){};
    }

    template<typename TFunc>
    static constexpr void for_each(TFunc&& func)
    {
        for_each_impl(std::make_index_sequence<size()>{}, func);
    }

private:
    template<std::size_t... Is, typename TFunc>
    static constexpr void for_each_impl(std::index_sequence<Is...>, TFunc&& func)
    {
        (func(at<Is>()), ...);
    }

};

template<typename... Ts>
type_list(std::tuple<Ts...>) -> type_list<Ts...>;

template<typename... Ts>
type_list(std::tuple<type_identity<Ts>...>) -> type_list<Ts...>;

template<std::size_t... I, typename... TLhs, typename... TRhs>
constexpr bool compareImpl(std::index_sequence<I...>, const type_list<TLhs...>& lhs, const type_list<TRhs...>& rhs)
{
    return (std::is_same_v<decltype(lhs.template at<I>()), decltype(rhs.template at<I>())> && ...);
}

template<typename... TLhs, typename... TRhs>
constexpr bool operator==(const type_list<TLhs...>& lhs, const type_list<TRhs...>& rhs)
{
    if constexpr (type_list<TLhs...>::size() != type_list<TRhs...>::size())
        return false;
    else
        return compareImpl(std::make_index_sequence<type_list<TLhs...>::size()>{}, lhs, rhs);
}


template<std::size_t I, typename... TListArgs>
constexpr auto get(const type_list<TListArgs...>&)
{
    return type_list<TListArgs...>::template at<I>();
}

template<typename... Args>
struct to_tuple<type_list<Args...>> {
    using type = std::tuple<Args...>;
};

template<typename T>
using to_tuple_t = typename to_tuple<T>::type;

template<typename... Args>
struct to_type_id_tuple<type_list<Args...>> {
    using type = std::tuple<type_identity<Args>...>;
};

template<typename T>
using to_type_id_tuple_t = typename to_type_id_tuple<T>::type;

} //namespace eel

#endif //EEL_TYPE_LIST_H
