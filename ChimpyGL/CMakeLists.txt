cmake_minimum_required(VERSION 3.20.0)

set(ENGINE_PATH ".")
file(GLOB_RECURSE ENGINE_SOURCES ${ENGINE_PATH}/*.cpp)

add_library(ChimpyGL STATIC ${ENGINE_SOURCES})

target_include_directories(ChimpyGL PUBLIC .)

include(GenerateExportHeader)
generate_export_header(ChimpyGL)

target_link_libraries(ChimpyGL PUBLIC
        quickjs
        SDL2::SDL2
        SDL2_image::SDL2_image
#        spdlog::spdlog
        EnTT
#        fmt::fmt
        box2d
        asio
)
