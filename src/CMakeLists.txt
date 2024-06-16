add_library(Core STATIC Lexer.cpp Parser.cpp)

add_executable(apl-repl apl-repl.cpp)
target_link_libraries(apl-repl Core PkgConfig::readline)
