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

install (
  TARGETS 
    linuxKeyboardEvents
  
  LIBRARY 
    DESTINATION lib
  
  ARCHIVE 
    DESTINATION lib
  
  RUNTIME 
    DESTINATION bin
  
  INCLUDES 
    DESTINATION include
)

install(
  FILES 
    include/keyboard.hpp 
    include/keyboard-events.hpp 
    include/keyboard-layouts.hpp
  DESTINATION 
    include/linuxKeyboardEvents/
)
