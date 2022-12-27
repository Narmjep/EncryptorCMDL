# Encryptor
A simple commandline tool that encrypts a file using RSA encryption.
Run
```bash
./Encryptor -h
```
to view the [help page](https://github.com/Narmjep/EncryptorCMDL/blob/CMake/Encryptor/rc/help.txt)

# TextToCode
Another commandline tool that parses a text file to a C++ void function which couts the content.
Run
```bash
./Encryptor -h
```
to view the [help page](https://github.com/Narmjep/EncryptorCMDL/blob/CMake/TextToCode/rc/Help.txt)

## Build
Use CMake to build the projects. Simply run:
```bash
cmake . && make
```
By default, cmake will only build Encryptor and not TextToCode. If you want to build both projects, then run 
```bash
cmake -DBUILD_TEXTTOCODE=TRUE . && make
```

