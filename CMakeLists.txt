cmake_minimum_required(VERSION 3.15)
project(untitled1)

set(CMAKE_CXX_STANDARD 11)


add_executable(untitled1 main.cpp Command.cpp Commands.h Client.cpp Client.h Server.cpp Server.h symbolTable.cpp symbolTable.h Parser.cpp Parser.h)