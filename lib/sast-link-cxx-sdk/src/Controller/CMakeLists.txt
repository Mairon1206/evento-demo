file(GLOB_RECURSE SOURCES *.cc *.h)

add_compile_definitions(HTML_DIR="${CMAKE_CURRENT_SOURCE_DIR}/html")

add_library(controller OBJECT ${SOURCES})

target_include_directories(controller PUBLIC include)

target_link_libraries(controller PUBLIC
    server
)