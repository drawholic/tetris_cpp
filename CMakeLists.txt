cmake_minimum_required(VERSION 3.5)

project(tetris)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
include_directories(include)

add_executable(main src/main.cpp src/Field.cpp src/Figure.cpp src/Square.cpp src/Interface.cpp
# src/another.cpp 
)

target_link_libraries(
    main
    PRIVATE
    sfml-graphics
    sfml-audio
)

