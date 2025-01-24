#set required version
cmake_minimum_required(VERSION 3.13)

#name
project(BinaryTree LANGUAGES C)

add_subdirectory(Source)

add_executable(main main.c)
target_link_libraries(main BinaryTree)
