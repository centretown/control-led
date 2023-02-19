cmake_minimum_required(VERSION 3.25)

project(
  Player
  VERSION 0.3
  LANGUAGES CXX)

# remove yaml for micro controllers

# include yaml
# add_definitions("-std=c++17" "-DDATA_DIR=\"${PROJECT_SOURCE_DIR}/test_data\"")
add_definitions("-std=c++11" "-DMICRO_CONTROLLER")

add_library(PlayerLib

  # src/esphome/components/light/esp_hsv_color.cpp
  # src/esphome/components/light/esp_hsv_color.h
  # src/esphome/core/color.h
  # src/esphome/core/helpers.h
  # src/esphome/core/optional.h
  ../src/base.h
  ../src/RGBColor.h
  ../src/RGBColor.cpp
  ../src/HSVColor.h
  ../src/HSVColor.cpp
  ../src/Chroma.h
  ../src/Chroma.cpp
  ../src/Grid.h
  ../src/Grid.cpp
  ../src/Layer.h
  ../src/Layer.cpp
  ../src/Frame.h
  ../src/Frame.cpp
  ../src/PaletteColor.h
  ../src/PaletteColor.cpp
  ../src/Palette.h
  ../src/Palette.cpp
  ../src/DisplayANSI.h
  ../src/HostLight.h
)

add_executable(player
  player.cpp
  library.h
  library.cpp
)

target_link_libraries(player
  PlayerLib
)

