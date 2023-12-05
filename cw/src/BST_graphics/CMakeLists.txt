set(target_name bst_graphics)

add_library(${target_name} STATIC
  BST_graphics.cpp
)

include(CompileOptions)
set_compile_options(${target_name})


target_link_libraries(
  ${target_name}
  PRIVATE
  sfml-graphics
  sfml-system
  sfml-window
  line
)

include_directories(${CMAKE_SOURCE_DIR}/include)
