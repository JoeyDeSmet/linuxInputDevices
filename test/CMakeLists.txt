add_executable(keyboardEventTests
  main.cpp
)

target_link_libraries(keyboardEventTests PUBLIC
  linuxInputDevices
)

