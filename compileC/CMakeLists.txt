cmake_minimum_required(VERSION 3.21)
project(compileC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE  Debug)

add_executable(${PROJECT_NAME} src/main.cpp src/Lexer.cpp src/Lexer.h src/Parser.cpp src/Parser.h src/CodeGen.cpp src/CodeGen.h src/AstNode.cpp src/AstNode.h src/PrintVisitor.cpp src/PrintVisitor.h src/Diag.cpp src/Diag.h)
