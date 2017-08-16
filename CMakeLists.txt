cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 14)

macro(build basename)
  add_executable(${basename} ${basename}.cpp)
  target_link_libraries(${basename} pthread)
endmacro()

build(hello_worlds)
build(hello_worlds_max_threads)
build(functor_launch)
build(lambda_launch)
build(identifying_threads)
