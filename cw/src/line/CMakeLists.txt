set(target_name line)

add_library(${target_name} STATIC
  line.cpp)

include(CompileOptions)
set_compile_options(${target_name})

target_link_libraries(
  ${target_name}
  PRIVATE
    sfml-graphics
    sfml-system
    sfml-window
)

include_directories(${CMAKE_SOURCE_DIR}/include)
