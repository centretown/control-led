cmake_minimum_required(VERSION 3.25)

project(
  Glow
  VERSION 0.5
  LANGUAGES CXX)

set(DATA_DIR "\"${PROJECT_SOURCE_DIR}/data\"")
set(TEST_DATA_DIR "\"${PROJECT_SOURCE_DIR}/test_data\"")

configure_file(GlowConfig.h.in ${PROJECT_SOURCE_DIR}/src/GlowConfig.h)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# include yaml
add_definitions("-DDATA_DIR=${DATA_DIR}" "-DTEST_DATA_DIR=${TEST_DATA_DIR}")

include(CTest)

include_directories(src)

add_library(GlowLib
  src/base.h
  src/RGBColor.h
  src/RGBColor.cpp
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
  src/Filer.cpp
  src/ansi_stream.h
  src/ansi_stream.cpp
  src/HostLight.h
  src/build_catalog.h
  src/build_catalog.cpp
)

add_executable(glow
  src/glow.cpp
  src/glow_show.h
  src/glow_show.cpp
  src/glow_file.h
  src/glow_file.cpp
)

# conan.CMakeDeps
find_package(yaml-cpp)
find_package(Catch2)
find_package(nlohmann_json)
find_package(cxxopts)

# assume packages found
include_directories(
  ${yaml-cpp_INCLUDE_DIRS}
  ${nlohmann_json_INCLUDE_DIRS}
  ${cxxopts_INCLUDE_DIRS}
)

target_link_libraries(glow
  ${yaml-cpp_LIBRARIES}
  nlohmann_json::nlohmann_json
  cxxopts::cxxopts
  GlowLib
)

target_compile_features(glow PUBLIC cxx_std_20)

add_subdirectory(test)

add_custom_target(generate_code) 

add_custom_command(
  TARGET glow POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_SOURCE_DIR}/src/base.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/RGBColor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/RGBColor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/HSVColor.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/HSVColor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Chroma.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Chroma.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Grid.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Grid.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Layer.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Layer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Frame.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Frame.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/custom/glow/)

add_custom_command(
  TARGET glow POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${DATA_DIR}/generated/catalog.cpp
  ${DATA_DIR}/generated/catalog.h
  ${CMAKE_CURRENT_SOURCE_DIR}/custom/glow/)

add_custom_command(
  TARGET glow POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${DATA_DIR}/generated/catalog.cpp
  ${DATA_DIR}/generated/catalog.h
  ${CMAKE_CURRENT_SOURCE_DIR}/generated/)
    
add_custom_command(
  TARGET glow POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${DATA_DIR}/generated/*.yml
  ${CMAKE_CURRENT_SOURCE_DIR}/custom/)

add_subdirectory(glow-play)
