cmake_minimum_required(VERSION 3.10)
project(helloWorld)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(SOURCE_FILES main.cpp TServer.cpp TServer.h TEPollServer.cpp TEPollServer.h TTcpBase.cpp TTcpBase.h)
add_executable(testTcp ${SOURCE_FILES})