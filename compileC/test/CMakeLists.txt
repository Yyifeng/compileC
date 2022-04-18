cmake_minimum_required(VERSION 3.21)
project(compileC_TEST)

set(CMAKE_CXX_STANDARD 17)

include_directories(. ../src)

add_executable(${PROJECT_NAME} main.cpp test.cpp ../src/Parser.cpp ../src/Lexer.cpp ../src/AstNode.cpp ../src/PrintVisitor.cpp ../src/Diag.cpp)