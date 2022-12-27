# Encryptor
A simple commandline tool that encrypts a file using RSA encryption.


# TextToCode
Another commandline tool that parses a text file to a C++ void function which couts the content.

## Build
Use CMake to build the projects. Simply run ```cmake . && make```. By default, cmake will only build Encryptor and not TextToCode. If you want to build both projects, then run ```cmake -DBUILD_TEXTTOCODE=TRUE . && make```

