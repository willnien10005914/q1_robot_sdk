cmake_minimum_required(VERSION 3.16)
project(q1_robot_sdk VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_EXAMPLES "Build Q1 examples" ON)
option(Q1_ENABLE_MOCK "Enable mock DDS path" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

add_library(q1_sdk INTERFACE)
target_include_directories(q1_sdk INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

if (BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(TARGETS q1_sdk EXPORT q1_sdkTargets)
install(EXPORT q1_sdkTargets
  FILE q1_sdkTargets.cmake
  NAMESPACE q1::
  DESTINATION lib/cmake/q1_sdk)
