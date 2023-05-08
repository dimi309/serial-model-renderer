cmake_minimum_required(VERSION 3.0.2)

project(srender)

file(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")
endif()

set(DEPS_PATH "${CMAKE_SOURCE_DIR}/small3d/deps")
set(CMAKE_PREFIX_PATH ${DEPS_PATH})

subdirs(small3d)
subdirs(src)
