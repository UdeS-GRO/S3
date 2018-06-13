cmake_minimum_required(VERSION 3.0)

find_package(FLEX   REQUIRED)
find_package(BISON  REQUIRED)

flex_target(lexer   tokens.l    ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)
bison_target(parser parser.y    ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
add_flex_bison_dependency(lexer parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})

add_library(compiler
    ast.cpp
    compiler.cpp
    vm.cpp
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)

add_executable(compiler_test
    compiler_test.cpp
)
target_link_libraries(compiler_test compiler)

add_executable(machine
    machine.cpp
)
target_link_libraries(machine compiler)
