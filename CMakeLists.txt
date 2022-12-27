project(EncryptorCMDL)

add_subdirectory(Encryptor)

option(BUILD_TextToCode FALSE)

if(${BUILD_TextToCode})
message("Building TextToCode")
    add_subdirectory(TxtToCode)
endif()
