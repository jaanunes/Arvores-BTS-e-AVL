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
add_executable(exercicio1 exercicios/exercicio1.cpp)
add_executable(exercicio2 exercicios/exercicio2.cpp)
add_executable(exercicio3 exercicios/exercicio3.cpp)