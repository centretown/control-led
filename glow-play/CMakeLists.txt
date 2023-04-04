cmake_minimum_required(VERSION 3.25)

project(
  Player
  VERSION 0.3
  LANGUAGES CXX)

# remove yaml for micro controllers
add_definitions("-DMICRO_CONTROLLER")

include_directories(
  ../generated
  ../src
)

add_library(PlayerLib
  ../src/base.h
  ../src/RGBColor.h
  ../src/RGBColor.cpp
  ../src/HSVColor.h
  ../src/HSVColor.cpp
  ../src/Chroma.h
  ../src/Chroma.cpp
  ../src/Pivot.h
  ../src/Pivot.cpp
  ../src/Grid.h
  ../src/Grid.cpp
  ../src/Layer.h
  ../src/Layer.cpp
  ../src/Frame.h
  ../src/Frame.cpp
  ../src/ansi_stream.h
  ../src/ansi_stream.cpp
  ../src/HostLight.h
)

add_executable(glow-play
  play.cpp
  ../generated/catalog.h
  ../generated/catalog.cpp
)

include_directories(
  ../generated
)

target_link_libraries(glow-play
  cxxopts::cxxopts
  PlayerLib
)

target_compile_features(glow-play PRIVATE cxx_std_11)
