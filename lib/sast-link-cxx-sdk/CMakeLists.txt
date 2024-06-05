cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(sast-link VERSION 0.1.0 LANGUAGES CXX)

if(NOT DEFINED BUILD_EXAMPLE)
    option(BUILD_EXAMPLE "Build example executables" OFF)
endif()

find_package(Boost REQUIRED COMPONENTS system url beast)
find_package(OpenSSL 3.3.0 REQUIRED)

add_subdirectory(src/Network)
add_subdirectory(src/Controller)

add_library(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    controller
    server
)

if(BUILD_EXAMPLE_EXECUTABLE)
    add_subdirectory(example)
endif()
