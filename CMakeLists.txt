cmake_minimum_required(VERSION 3.15)
project(untitled1)

#set(CMAKE_CXX_STANDARD 11)
#set(CMMAKE_CXX_FLAGS "-std=c++11 -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(untitled1 main.cpp Command.cpp Command.h Client.cpp Client.h Server.cpp Server.h CommandMap.cpp CommandMap.h Parser.cpp Parser.h Lexer.cpp Lexer.h Expressions.cpp Expressions.h Interpreter.h Interpreter.cpp DefineVarCommand.cpp SymbolTable.h SymbolTable.cpp SimIncomingInfo.h SimIncomingInfo.cpp VarAssignCommand.cpp SleepCommand.cpp PrintCommand.cpp OpenServerCommand.cpp)
