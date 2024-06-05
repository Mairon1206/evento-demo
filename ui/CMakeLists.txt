find_package(Slint QUIET)

set(SLINT_STYLE "material" CACHE STRING "The name of the linting style to use" FORCE)

if (NOT Slint_FOUND)
  message("Slint could not be located in the CMake module search path. Downloading it from Git and building it locally")
  include(FetchContent)
  FetchContent_Declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    # `release/1` will auto-upgrade to the latest Slint >= 1.0.0 and < 2.0.0
    # `release/1.0` will auto-upgrade to the latest Slint >= 1.0.0 and < 1.1.0
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
  )
  FetchContent_MakeAvailable(Slint)
endif (NOT Slint_FOUND)

add_library(evento-ui SHARED lib.cc)

target_link_libraries(evento-ui PRIVATE Slint::Slint)

target_include_directories(evento-ui PUBLIC include)

slint_target_sources(evento-ui 
    Window/MainWindow.slint
)

set_property(TARGET evento-ui PROPERTY SLINT_EMBED_RESOURCES embed-files)