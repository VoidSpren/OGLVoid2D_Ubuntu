cmake_minimum_required(VERSION 3.26.0)
project(OGLVoid2D VERSION 0.1.0)

cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(OGLVoid2D
  src/Main.cpp
  src/glad.c
)

target_include_directories(OGLVoid2D PRIVATE
  libs
)

target_link_libraries(OGLVoid2D
  OpenGL::GL
  glfw
)

file(COPY
  resources/
  DESTINATION
  ${CMAKE_CURRENT_BINARY_DIR}
)
