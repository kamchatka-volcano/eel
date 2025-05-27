cmake_minimum_required(VERSION 3.18)
project(test_eel)

if(EEL_TEST_RELEASE)
    add_subdirectory(release)
endif()

SealLake_GoogleTest(
        SOURCES
            test_string.cpp
            test_traits.cpp
            test_type_list.cpp
            test_functional.cpp
            test_utility.cpp
            test_member.cpp
            test_indirect_member.cpp
        LIBRARIES
            eel::eel
)