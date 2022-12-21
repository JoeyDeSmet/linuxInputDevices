# Linux Input Devices

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Simple c++ library that makes it easy to assign events for different input devices on linux systems.

# Contents
- [Keyboard](#keyboard)
  - [Using keyboard layouts](#using-keyboard-layouts)
  - [Creating events](#creating-event-callbacks)
  - [Removing events](#removeing-events)
- [Build and install](#build-and-install)
- [Example](#example)

# Keyboard

The keyboard class enables you to setup different callback functions, when a keyboard event occurs.
This class creates it's own thread where it will listen for keyboard input events, and exectute your defined callback.

## Usage

You can create a Keyboard object and register callback functions using the on method.

### Using keyboard layouts

Keycodes for a *QWERTY* and *AZERTY* keyboard are included in the `keyboard-layouts.hpp` file.

Both of them are enum classes called KeyCode, so to use the one on your device just define is as the following:

```cpp
#include "keyboard-layouts.hpp"

using namespace KeyboardLayouts::AZERTY;
```

### Creating event callbacks

To define a callback function for an event you can you the `on(KeyboardEvent, callback)` method.

```cpp
#include "keyboard.hpp"
#include "keyboard-events.hpp"

using namespace InputDevices;

Keyboard keyboard;

// Create a keyboardEvent struct for when the key A is being held down
KeyboardEvent event = {
  KeyboardEvents::KeyHeld,
  (char) KeyCode::A,
  0
};

// Add the event to the keyboard
keyboard.on(event, []() {
  std::cout << "A key being held down\n";
});
```

I have also provided some handy helper methods to do this. So the folling code does the same as the above code but is a bit shorter.

```cpp
keyboard.on_key_held(KeyCode::A, []() {
  std::cout << "A key being held down\n";
});
```

### Removeing events

There are two ways to delete an define event.

1. `remove_events(KeyCode)`

    This will remove all events where KeyCode::A is being used.

```cpp
keyboard.remove_events(KeyCode::A);
```

2. `remove_event(KeyboardEvent)`

    This will remove a specific event.

```cpp
keyboard.remove_event(event);
```

# Build and install 

This projects builds a static library using cmake. To build and install do the following.

```bash
mkdir build
cd build

cmake ..

make
sudo make install
```

# Example

If you want to build the example, replace the following lines from the build process.

```bash
# From
cmake ..

# To
cmake -DBUILD_EXAMPLE=True
```

The example listens to keybboard differen keyboard events and prints lines to the terminal.

The binary file will be placed in de `build/example/` directory as `exampleKeyboard`.

# License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.
