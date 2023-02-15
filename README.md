# Glow
An led strip application.

---
## Building
---
### Prerequisites:
#### C++ build environment
https://linuxhint.com/install-build-essential-ubuntu/
```sh
# gcc 9.4.0: (Ubuntu 9.4.0-1ubuntu1~20.04.1)
sudo apt install build-essential
gcc --version
```
#### cmake version 3.25.2 
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
build/glow
```
---