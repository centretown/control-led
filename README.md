# Glow
An led strip application.

---
### Building
---
#### Prerequisites:
- Conan version 1.58.0
- cmake version 3.25.2
- c++ build environment
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0

#### Install:
```sh
git clone https://github.com/centretown/glow.git`
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