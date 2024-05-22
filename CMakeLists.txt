cmake_minimum_required(VERSION 3.5)

project(tetris)


find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main src/main.cpp)
include_directories(include)

target_link_libraries(
    main
    PRIVATE
    sfml-graphics
    sfml-audio
)

