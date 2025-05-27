#ifndef EEL_PATH_H
#define EEL_PATH_H

#include "wstringconv.h"
#include <filesystem>
#include <string>
#include <string_view>

namespace eel {

inline std::filesystem::path make_path(std::string_view str)
{
#ifdef _WIN32
    return to_wstring(str);
#else
    return str;
#endif
}

inline std::string to_string(const std::filesystem::path& path)
{
#ifdef _WIN32
    return from_wstring(path.wstring());
#else
    return path.string();
#endif
}

} //namespace eel

#endif //EEL_PATH_H
