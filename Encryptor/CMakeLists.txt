cmake_minimum_required(VERSION 3.10)

# set the project name
project(Encryptor)

#dependencies
add_subdirectory(dependencies/MyRSA)

file(GLOB Encryptor_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(Encryptor ${Encryptor_SOURCES})

#MyRSA
target_include_directories(Encryptor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/MyRSA/src)




