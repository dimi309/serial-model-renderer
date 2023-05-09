add_executable(srender main.cpp)

target_include_directories(srender PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../small3d/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/../small3d/deps/include")

target_link_libraries(srender PUBLIC small3d)

if(APPLE)
  set_target_properties(srender PROPERTIES LINK_FLAGS "-framework \
		AudioUnit -framework AudioToolbox -framework CoreAudio -framework Cocoa \
		-framework IOKit -framework CoreVideo")
endif()

if(MSVC)
  set_target_properties(srender PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    "${PROJECT_BINARY_DIR}/bin")
endif()
