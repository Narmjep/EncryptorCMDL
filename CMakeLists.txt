project(EncryptorCMDL)

add_subdirectory(Encryptor)

option(Build_TextToCode FALSE)

if(Build_TextToCode)
message("Building TextToCode")
    add_subdirectory(TxtToCode)
endif()
