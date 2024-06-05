add_library(evento-net OBJECT network.cc)

target_include_directories(evento-net PUBLIC include)

target_link_libraries(evento-net PRIVATE  
    Boost::boost Boost::system Boost::url Boost::beast
    OpenSSL::Crypto OpenSSL::SSL
    nlohmann_json::nlohmann_json
    sast-link
)