add_executable(srender main.cpp)

target_link_libraries(srender PUBLIC small3d)

if(MSVC)
  set_target_properties(srender PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    "${PROJECT_BINARY_DIR}/bin")
endif()
