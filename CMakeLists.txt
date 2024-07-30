cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (POLICY CMP0167)
  cmake_policy(SET CMP0167 OLD)
endif()

project(demo VERSION 0.1.0 LANGUAGES CXX)

find_package(spdlog REQUIRED)
find_package(Boost REQUIRED COMPONENTS system url beast)
find_package(OpenSSL 3.3.0 REQUIRED)
find_package(nlohmann_json REQUIRED)

add_compile_definitions(BOOST_ASIO_HAS_CO_AWAIT)

add_subdirectory(lib/sast-link-cxx-sdk)
add_subdirectory(ui)
add_subdirectory(src/Network)

add_executable(demo src/main.cc)

target_link_libraries(
    demo PRIVATE
    spdlog::spdlog
    evento-net
    evento-ui
)

# On Windows, copy the Slint DLL next to the application binary so that it's found.
if (WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:evento-ui> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

