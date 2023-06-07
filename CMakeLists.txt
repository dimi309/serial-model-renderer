cmake_minimum_required(VERSION 3.15.0)

project(srender)

file(COPY "resources" DESTINATION "${PROJECT_BINARY_DIR}/bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

if(MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")
endif()

subdirs(small3d)
subdirs(src)
