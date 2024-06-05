file(GLOB_RECURSE SOURCES *.cc *.h)

add_library(server OBJECT ${SOURCES})

target_include_directories(server PUBLIC include)

target_link_libraries(server INTERFACE
    Boost::system
)

target_link_libraries(server PRIVATE
    Boost::url
    OpenSSL::SSL OpenSSL::Crypto
)