## eel

[![build & test (clang, gcc, MSVC)](https://github.com/kamchatka-volcano/eel/actions/workflows/build_and_test.yml/badge.svg?branch=master)](https://github.com/kamchatka-volcano/eel/actions/workflows/build_and_test.yml)

**eel** (everyday extension library) is a header-only collection of utilities for string manipulation, metaprogramming, core guidelines support
and other general-purpose tasks.

### Contents

* `contract.h` - Macros for contract programming, violations lead to `std::terminate()` (the implementation is copied
  from [GSL](https://github.com/microsoft/GSL))
* `functional.h` - Metaprogramming and other helpers for functions and callable objects;
* `interface.h` - `eel::interface`, a private base class that brings the properties for virtual interfaces recommended
  by Core Guidelines (non-copyable, non-movable, has virtual destructor); `eel::access_permission` - a restricted
  member access alternative to the `friend` keyword, based on
  the [badge pattern](https://awesomekling.github.io/Serenity-C++-patterns-The-Badge/) idea.
* `member.h` - A wrapper that allows storing const and reference types members without affecting the parent class's copy
  and move properties (as recommended by Core Guidelines).
* `path.h` - Helpers to follow [ut8everywhere manifesto](https://utf8everywhere.org) by storing UTF-16
  inside `std::filesystem::path` on Windows and UTF-8 on other platforms. All `std::filesystem::path` objects should be
  constructed with `eel::make_path` and converted to a string with `eel::to_string`.
* `string_utils.h` - Basic string utils based on STL algorithms.
* `type_list.h` - A basic type list for metaprogramming.
* `type_traits.h` - A collection of type traits.
* `utility.h` - Miscellaneous helpers, some are from the standard library newer than C++17.
* `wstringconv.h` - UTF-16 to UTF-8 string conversion for Windows, provided by
  the [`utfcpp`](https://github.com/nemtrif/utfcpp) library bundled in the `detail/` directory.

### Installation

Download and link the library from your project's CMakeLists.txt:

```
cmake_minimum_required(VERSION 3.14)

include(FetchContent)

FetchContent_Declare(eel
    GIT_REPOSITORY "https://github.com/kamchatka-volcano/eel.git"
    GIT_TAG "origin/master"
)

#uncomment if you need to install eel with your target
#set(INSTALL_EEL ON)
FetchContent_MakeAvailable(eel)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE eel::eel)
```

To install the library system-wide, use the following commands:
```
git clone https://github.com/kamchatka-volcano/eel.git
cd eel
cmake -S . -B build
cmake --build build
cmake --install build
```

After installation, you can use the `find_package()` command to make the installed library available inside your
project:
```
find_package(eel 1.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE eel::eel)
```


### Running tests
```
cd eel
cmake -S . -B build -DENABLE_TESTS=ON
cmake --build build
cd build/tests && ctest
```

### License
**eel** is licensed under the [MS-PL license](/LICENSE.md)  
