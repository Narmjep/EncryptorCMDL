cmake_minimum_required(VERSION 3.10)


project(Precalculator)

file(GLOB Precalculator_SOURCES
    src/*.cpp
)

add_executable(precalculator ${Precalculator_SOURCES})

add_dependencies(precalculator MyRSA::MyRSA)

target_link_libraries(precalculator MyRSA::MyRSA)
