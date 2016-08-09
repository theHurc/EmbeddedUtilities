cmake_minimum_required(VERSION 2.8.9)
project(CircularBuffer)

include_directories(include)

add_library(CircularBuffer
  src/CircularBuffer.c
)

add_executable( circular_buffer_test
  test/test.c
)
target_link_libraries( circular_buffer_test
 CircularBuffer
)
