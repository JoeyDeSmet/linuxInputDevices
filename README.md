# Linux Keyboard Events

This is a C++ class that enables you to handle keyboard events in your application. You can register callback functions for specific key press and key release events, and the class will handle the event loop and call the appropriate callback when an event occurs.

## Usage

You can create a KeyBoardEvents object and register callback functions using the on_key_down and on_key_up functions for single keys:

```cpp
#include <keyboard.hpp>

// This should be your keyboard layout
using namespace KeyboardLayouts::AZERTY;

Keyboard keyboard;

keyboard.on_key_down(KeyCode::A, [](){
  std::cout << "A key was pressed" << std::endl;
});

keyboard.on_key_up(KeyCode::A, [](){
  std::cout << "A key was released" << std::endl;
});

```

You can also register callback function for 2-key combination using the on_alt_key_down function:

```cpp
keyboard.on_alt_key_down(KeyCode::LEFTCTRL, KeyCode::C, [](){
  std::cout << "You pressed CRTL and C" << std::endl;
});
```

The key codes are defined in the keyboard-layout.hpp file. 
The callback function will be called when the corresponding event occurs.

**To be implemented**
You can also remove registered events using the remove_events function:

```cpp
keyboard.remove_events(KeyCode::A);
```

This will remove the callback functions registered for the KeyCode::A key, for both up and down events.

## **Note**

The KeyBoardEvents class currently only supports reading events from the /dev/input/event4 device. 
If you want to use a different device, you will need to modify the constructor of the KeyBoardEvents class.

# License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
