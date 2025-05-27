#ifndef EEL_CONTRACT_H
#define EEL_CONTRACT_H

#include "string_utils.h"
#include <stdexcept>
#include <string_view>

#if (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L) || (!defined(_MSVC_LANG) && __cplusplus >= 202002L)
#define EEL_CPP20
#endif

#ifdef EEL_CPP20
#include <source_location>
#endif

namespace eel {

struct source_location {
#ifdef EEL_CPP20
    source_location(
            std::string_view fileName = std::source_location::current().file_name(),
            int lineNumber = std::source_location::current().line())
        : fileName{fileName}
        , lineNumber{lineNumber}
    {
    }
#endif
    std::string_view fileName;
    int lineNumber{};
};

#define EEL_LINE                                                                                                       \
    eel::source_location                                                                                               \
    {                                                                                                                  \
        __FILE__, __LINE__                                                                                             \
    }

namespace detail {

constexpr void contractCheck(bool expressionResult, std::string_view message, const source_location& location)
{
    if (!expressionResult)
        throw std::logic_error{concat(message, " at ", location.fileName, ":", std::to_string(location.lineNumber))};
}

} //namespace detail

constexpr void precondition(
        bool expressionResult,
        const source_location& location
#ifdef EEL_CPP20
        = {}
#endif
)
{
    detail::contractCheck(expressionResult, "Broken precondition", location);
}

constexpr void postcondition(
        bool expressionResult,
        const source_location& location
#ifdef EEL_CPP20
        = {}
#endif
)
{
    detail::contractCheck(expressionResult, "Broken postcondition", location);
}

constexpr void invariant(
        bool expressionResult,
        const source_location& location
#ifdef EEL_CPP20
        = {}
#endif
)
{
    detail::contractCheck(expressionResult, "Broken invariant", location);
}

constexpr void verify(
        bool expressionResult,
        const source_location& location
#ifdef EEL_CPP20
        = {}
#endif
)
{
  detail::contractCheck(expressionResult, "Verification failed", location);
}

} //namespace eel

#endif //EEL_CONTRACT_H