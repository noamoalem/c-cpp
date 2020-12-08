cmake_minimum_required(VERSION 3.16)
project(ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex1 main.cpp
        MlpNetwork.cpp Digit.h Matrix.cpp Matrix.h Activation.cpp Activation.h
        Dense.cpp Dense.h)