set(target_name app)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
    ${target_name}
    PRIVATE
    main.cpp
)

find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

target_link_libraries(
  ${target_name}
  PRIVATE
  sfml-graphics
  sfml-system
  sfml-window
  ImGui-SFML::ImGui-SFML
  bst_graphics
  line
)

include_directories(${CMAKE_SOURCE_DIR}/include)
