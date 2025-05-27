cmake_minimum_required(VERSION 3.18)
project(eel VERSION 0.1.0 DESCRIPTION "eel - everyday extension library")
include(external/seal_lake)

SealLake_Bundle(
        NAME eel-utfcpp
        GIT_REPOSITORY https://github.com/nemtrif/utfcpp.git
        GIT_TAG v3.2.3
        SKIP_LOAD
        DESTINATION include/eel/detail/external
        FILES source/utf8.h
        DIRECTORIES source/utf8
        TEXT_REPLACEMENTS
        "namespace utf8" "namespace eel::utf8"
        UTF8_ EEL_UTF8_
)

SealLake_HeaderOnlyLibrary(
        COMPILE_FEATURES cxx_std_17
)
SealLake_OptionalSubProjects(tests)

