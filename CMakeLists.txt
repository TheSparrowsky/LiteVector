cmake_minimum_required(VERSION 3.16)
project(LiteVector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LiteVector
	src/main.cpp
	src/LiteVector.h
	src/LiteVector.tpp
)
