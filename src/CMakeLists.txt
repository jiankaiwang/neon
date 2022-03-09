cmake_minimum_required(VERSION 3.0)

project(deinterleave VERSION 1.0.0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -o3")

set(OpenCV_DIR ${CMAKE_SOURCE_DIR}/../opencv/build)
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config: ${OpenCV_DIR}")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

add_executable(deinterleave deinterleave.cc)

include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(deinterleave PUBLIC ${OpenCV_LIBS})
