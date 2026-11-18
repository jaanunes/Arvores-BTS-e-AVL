cmake_minimum_required(VERSION 4.3)
project(ed2_arvores)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

# Cada questão é um executável independente
add_executable(arvores
        main.cpp
        src/BST.cpp
        src/AVL.cpp
)
