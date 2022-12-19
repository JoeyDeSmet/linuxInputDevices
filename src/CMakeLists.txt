add_library( linuxInputDevices STATIC )

target_include_directories(linuxInputDevices INTERFACE 
  ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(linuxInputDevices
  PRIVATE
    keyboard.cpp
)

include_directories(
  ${CMAKE_CURRENT_LIST_DIR}/include
)

install (
  TARGETS 
    linuxInputDevices
  
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
    include/linuxInputDevices/
)
