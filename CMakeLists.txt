cmake_minimum_required(VERSION 4.0)
project(MsgKor)

set(CMAKE_CXX_STANDARD 26)

add_executable(MsgKor main.cpp
        inputer.cpp
        inputer.h
        stringMethods.cpp
        stringMethods.h
        korobochka.cpp
        korobochka.h)
