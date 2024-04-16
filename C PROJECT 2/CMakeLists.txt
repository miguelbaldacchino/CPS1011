cmake_minimum_required(VERSION 3.26)
project(C_PROJECT_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Question_2a
        TestGenSet1.c
        GenSet1.c
        )

add_library(GenSet2 SHARED GenSet2.c GenSet2.h)

add_executable(Question_2b
        TestGenSet2.c
        )

target_link_libraries(Question_2b GenSet2)
