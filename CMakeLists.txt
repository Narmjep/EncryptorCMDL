project(EncryptorCMDL)


#Encryptor
add_subdirectory(Encryptor)
#TextToCode
option(BUILD_TEXTTOCODE "Set this to true to additionally build the TextToCode Program." FALSE)

if(${BUILD_TEXTTOCODE})
message("Building TextToCode")
    add_subdirectory(TextToCode ${CMAKE_CURRENT_BINARY_DIR})
else()
message("Ignoring TextToCode")
endif()

