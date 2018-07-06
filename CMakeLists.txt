cmake_minimum_required(VERSION 3.10)
project(helloWorld)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(client)

add_subdirectory(server)
