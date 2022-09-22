cmake_minimum_required(VERSION 3.2)
project(expes)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Where to find the Find*.cmake files
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})


# Get the vectorpack lib
find_package(Vectorpack)

add_executable(main_multidim src/main_multidim.cpp
    src/algo_lists.hpp
)
target_link_libraries(main_multidim PRIVATE Vectorpack)


add_executable(main_1dim src/main_1dim.cpp)
target_link_libraries(main_1dim PRIVATE Vectorpack)

