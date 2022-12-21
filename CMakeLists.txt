cmake_minimum_required( VERSION 3.22.0 )

project( linuxInputDevices VERSION 0.0.2 LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set(CMAKE_INSTALL_PREFIX /usr/local/)

set (KEYBOARD_EVENTS_DEFAULT_BUILD_TYPE "Release")
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set (CMAKE_BUILD_TYPE ${KEYBOARD_EVENTS_DEFAULT_BUILD_TYPE})
endif()

if (WIN32)
  message(SEND_ERROR "This project is for linux use only, it won't work on windows")  
endif()

add_compile_options(-Wall -Werror -Wextra -pedantic -O3)

add_subdirectory(src)

if (BUILD_EXAMPLE)
  add_subdirectory(example)
endif()
