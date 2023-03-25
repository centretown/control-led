# Glow
An led strip application.

---
## Building
---
### Environment:
#### C++ build environment
- Micro Controller Code uses C++11/C++14
- Command line utility uses C++20

https://linuxhint.com/install-build-essential-ubuntu/

```sh
sudo apt install build-essential
gcc --version
# gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0

```
#### Cmake version 3.26.1
https://cmake.org/download/
```sh
cmake --version
# cmake version 3.26.1
```
#### Conan package manager version 2.0.2
https://conan.io/downloads.html
```sh
conan --version
```

#### Install:
```sh
git clone https://github.com/centretown/glow.git
cd glow
conan install . --output-folder=build --build=missing
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
```
#### Build:
```sh
cd build
cmake --build .
```
#### Test:
```sh
cd build
ctest -V
```

#### Run:
```sh
# command line utility
build/glow
# micro-controller emulator
build/glow-play/glow-play
```
---