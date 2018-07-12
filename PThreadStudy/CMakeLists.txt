set(SOURCE_FILES main.cpp)

add_executable(testThread ${SOURCE_FILES})
target_link_libraries(testThread pthread)