cmake_minimum_required(VERSION 3.25)

project(
  Glow
  VERSION 0.4
  LANGUAGES CXX)

configure_file(GlowConfig.h.in ../src/GlowConfig.h)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# remove yaml for micro controllers
# add_definitions("-std=c++14 -DSTRIP_YAML")

# include yaml
add_definitions("-std=c++14")

include(CTest)

include_directories(src)

add_library(GlowLib
  src/esphome/components/light/esp_hsv_color.cpp
  src/esphome/components/light/esp_hsv_color.h
  src/esphome/core/color.h
  src/esphome/core/helpers.h
  src/esphome/core/optional.h
  src/base.h
  src/HSVColor.h
  src/HSVColor.cpp
  src/Chroma.h
  src/Chroma.cpp
  src/Grid.h
  src/Grid.cpp
  src/Layer.h
  src/Layer.cpp
  src/Frame.h
  src/Frame.cpp
  src/PaletteColor.h
  src/PaletteColor.cpp
  src/Palette.h
  src/Palette.cpp
  src/Filer.h
  src/DisplayANSI.h
)

add_executable(glow
  src/glow.cpp
  src/palette_builder.h
  src/palette_builder.cpp
)

# method 1 conan.cmake generator
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()
# if(TARGET yaml-cpp)
# target_link_libraries(glow ${yaml-cpp_LIBRARIES} GlowLib)

# if(TARGET Catch2)
# add_subdirectory(test)
# endif()
# endif()

# method 2 conan.cmake_find_package generator
find_package(yaml-cpp)
find_package(Catch2)

if(yaml-cpp_FOUND)
  include_directories(${yaml-cpp_INCLUDE_DIRS})
  target_link_libraries(glow ${yaml-cpp_LIBRARIES} GlowLib)

  if(Catch2_FOUND)
    add_subdirectory(test)
  endif()
endif()
