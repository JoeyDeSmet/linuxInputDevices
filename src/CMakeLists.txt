add_library( linuxKeyboardEvents STATIC )

target_include_directories(linuxKeyboardEvents INTERFACE 
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources( linuxKeyboardEvents
  PRIVATE
    keyboard.cpp
)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/include
)
