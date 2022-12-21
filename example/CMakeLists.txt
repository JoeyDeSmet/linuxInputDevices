add_executable(exampleKeyboard
  main.cpp
)

target_link_libraries(exampleKeyboard PUBLIC
  linuxInputDevices
)

