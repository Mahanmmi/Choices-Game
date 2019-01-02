cmake_minimum_required(VERSION 3.12)
project(Intro_Programming_Final_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Intro_Programming_Final_Project
        c1.txt
        main.c
        MyFile.c
        MyFile.h
        MyLinkedList.c
        MyLinkedList.h)
