cmake_minimum_required(VERSION 3.10)

# set the project name
project(EncryptorCMDL)

file(GLOB Encryptor_SOURCES
    src/*.cpp
)

add_executable(Encryptor ${Encryptor_SOURCES})

#MyRSA
set(MyRSA_BUILD_SHARED FALSE)
add_subdirectory(dependencies/MyRSA)
add_dependencies(Encryptor MyRSA::MyRSA)

#Linking
get_property(MyRSA_INCLUDE_DIRS TARGET MyRSA PROPERTY INCLUDE_DIRS)
target_link_directories(Encryptor PRIVATE ${MyRSA_INCLUDE_DIRS})
target_link_libraries(Encryptor MyRSA::MyRSA)

#Precalculator
add_subdirectory(Precalculator)

file(GLOB MyRSA_Dlls ${CMAKE_CURRENT_BINARY_DIR}/dependencies/MyRSA/*.dll)





