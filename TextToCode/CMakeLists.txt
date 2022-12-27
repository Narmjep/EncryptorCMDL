cmake_minimum_required(VERSION 3.10)

# set the project name
project(TTC)

cmake_minimum_required(VERSION 3.10)

file(GLOB sources src/*.cpp)

# add the executable
add_executable(TTC ${sources} rc/TTC.rc)


