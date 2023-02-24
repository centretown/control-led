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

https://linuxconfig.org/how-to-switch-between-multiple-gcc-and-g-compiler-versions-on-ubuntu-20-04-lts-focal-fossa
```sh
sudo apt install build-essential
gcc --version
# gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
sudo apt install gcc-10
sudo apt install g++-10
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 9
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-10 10
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-10 10
gcc --version
# gcc (Ubuntu 10.3.0-1ubuntu1~20.04) 10.3.0

```
#### Cmake version 3.25.2 
https://cmake.org/download/
```sh
cmake --version
```
#### Conan package manager version 1.58.0
https://conan.io/downloads.html
```sh
conan --version
```

#### Install:
```sh
git clone https://github.com/centretown/glow.git
cd glow
mkdir build
cd build
conan install ..
cmake ..
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