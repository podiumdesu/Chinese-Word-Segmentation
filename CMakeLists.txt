cmake_minimum_required(VERSION 3.7)
project(c_design)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c maxLength.c trie.c buildDict.c matchUserInput.c shared.c)
add_executable(c_design ${SOURCE_FILES})