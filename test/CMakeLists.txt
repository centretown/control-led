# Tests need to be added as executables first
add_executable(test_grid test_grid.cpp)
add_executable(test_hsvcolor test_hsvcolor.cpp)
add_executable(test_chroma test_chroma.cpp)
add_executable(test_layer test_layer.cpp)
add_executable(test_frame test_frame.cpp)

include_directories(
  ${yaml-cpp_INCLUDE_DIRS}
  ${catch2_INCLUDE_DIRS}
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

enable_testing()

add_test(NAME HSVCOLOR COMMAND test_hsvcolor) # Command can be a target
add_test(NAME CHROMA COMMAND test_chroma) # Command can be a target
add_test(NAME LAYER COMMAND test_layer) # Command can be a target
add_test(NAME FRAME COMMAND test_frame) # Command can be a target
add_test(NAME GRID COMMAND test_grid) # Command can be a target
