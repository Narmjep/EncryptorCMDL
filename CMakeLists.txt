project(EncryptorCMDL)

IF(POLICY CMP0012)
    CMAKE_POLICY(SET CMP0012 NEW)
ENDIF()

add_subdirectory(Encryptor)

option(BUILD_TEXTTOCODE "Set this to true to additionally build the TextToCode Program." TRUE)

if(${BUILD_TEXTTOCODE})

message("Building TextToCode")
    add_subdirectory(TextToCode)
else()
message("Ignoring TextToCode")
endif()
