cmake_minimum_required(VERSION 3.10)

# set the project name
project(EncryptorCMDL)

file(GLOB sources
    src/*.cpp
)

add_executable(Encryptor ${sources})

#MyRSA
set(MyRSA_BUILD_SHARED TRUE)
add_subdirectory(dependencies/MyRSA)
add_dependencies(Encryptor MyRSA::MyRSA)

get_property(MyRSA_INCLUDE_DIRS TARGET MyRSA PROPERTY INCLUDE_DIRS)
target_link_directories(Encryptor PRIVATE ${MyRSA_INCLUDE_DIRS})

target_link_libraries(Encryptor MyRSA::MyRSA)

file(GLOB MyRSA_Dlls ${CMAKE_CURRENT_BINARY_DIR}/dependencies/MyRSA/*.dll)
if(${MyRSA_BUILD_SHARED})
add_custom_command(
    TARGET Encryptor
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_BINARY_DIR}/dependencies/MyRSA/libMyRSA.dll ${CMAKE_CURRENT_BINARY_DIR}
    )
endif()

