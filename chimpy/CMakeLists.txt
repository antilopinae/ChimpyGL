cmake_minimum_required(VERSION 3.20.0)

include_directories(include)

set(ENGINE_PATH ".")
file(GLOB_RECURSE ENGINE_SOURCES ${ENGINE_PATH}/*.cpp)

add_library(ChimpyGL STATIC ${ENGINE_SOURCES})

include(GenerateExportHeader)
generate_export_header(ChimpyGL)

add_library(quickjs STATIC IMPORTED)
set_target_properties(quickjs PROPERTIES
        IMPORTED_LOCATION "/usr/local/lib/quickjs/libquickjs.a"
        INTERFACE_INCLUDE_DIRECTORIES "/usr/local/include/quickjs"
)

target_link_libraries(ChimpyGL PUBLIC
        quickjs
        SDL2::SDL2
        SDL2_image::SDL2_image
        spdlog::spdlog
        EnTT
        fmt::fmt
        box2d
        asio
)
