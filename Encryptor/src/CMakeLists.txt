cmake_minimum_required(VERSION 3.10)

# set the project name
project(EncryptorCMake)

cmake_minimum_required(VERSION 3.10)




# add the executable
add_executable(Encryptor char.cpp InputParser.cpp main.cpp MyRSA.cpp ppcm_pgcd.cpp ../rc/Encryptor.rc)


include_directories(../dependencies/include)