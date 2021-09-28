cmake_minimum_required(VERSION 3.12)
project(Assignment2)
add_executable(Assignment2 Assignment2.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Assignment2 PRIVATE /W4 /permissive-)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(Assignment2 PRIVATE -Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "CLANG")
    target_compile_options(Assignment2 PRIVATE -Wall -Wextra -pedantic)
endif()

set_property(TARGET Assignment2 PROPERTY CXX_STANDARD 20)

set(SOURCE_FILES Assignment2.cpp)

find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    message("clang-format found at: " ${CLANG_FORMAT})

    unset(SOURCE_FILES_PATHS)

    foreach(SOURCE_FILE ${SOURCE_FILES})
        get_source_file_property(WHERE ${SOURCE_FILE} LOCATION)
        set(SOURCE_FILES_PATHS ${SOURCE_FILES_PATHS} ${WHERE})
    endforeach()

    add_custom_target(
        ClangFormat
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${SOURCE_FILES_PATHS})

    add_dependencies(Assignment2 ClangFormat)
endif()