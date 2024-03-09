cmake_minimum_required(VERSION 3.20.0)
project(apl-compiler CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(apl-compiler main.cpp Lexer.cpp Parser.cpp)
target_link_libraries(apl-compiler)
