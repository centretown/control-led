# Tests need to be added as executables first
add_executable(test_grid test_grid.cpp)
add_executable(test_hsvcolor test_hsvcolor.cpp)
add_executable(test_chroma test_chroma.cpp)
add_executable(test_layer test_layer.cpp)
add_executable(test_frame test_frame.cpp)
add_executable(test_build_palette
  test_build_palette.cpp
  ../src/palette_builder.h
  ../src/palette_builder.cpp
)
add_executable(test_filer test_filer.cpp)
add_executable(test_json test_json.cpp)
add_executable(test_light test_light.cpp)

include_directories(
  ${yaml-cpp_INCLUDE_DIRS}
  ${catch2_INCLUDE_DIRS}
)

target_link_libraries(test_filer PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_grid PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_hsvcolor PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_layer PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_frame PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_chroma PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_build_palette PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

target_link_libraries(test_json PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  nlohmann_json::nlohmann_json
  GlowLib
)

target_link_libraries(test_light PRIVATE
  ${yaml-cpp_LIBRARIES}
  ${catch2_LIBRARIES}
  GlowLib
)

enable_testing()

add_test(NAME FILER COMMAND test_filer)
add_test(NAME HSVCOLOR COMMAND test_hsvcolor)
add_test(NAME PALETTE COMMAND test_build_palette)
add_test(NAME JSON COMMAND test_json)
add_test(NAME LAYER COMMAND test_layer)
add_test(NAME LIGHT COMMAND test_light)
add_test(NAME FRAME COMMAND test_frame)
add_test(NAME CHROMA COMMAND test_chroma)
add_test(NAME GRID COMMAND test_grid)
