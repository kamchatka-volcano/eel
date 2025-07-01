cmake_minimum_required(VERSION 3.18)
project(eel VERSION 0.3.0 DESCRIPTION "eel - everyday extension library")
include(seal_lake.cmake)

SealLake_v040_HeaderOnlyLibrary(
    COMPILE_FEATURES cxx_std_17
)

