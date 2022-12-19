#pragma once

#include <functional>

namespace InputDevices {

  enum class KeyboardEvents {
    KeyUp,
    KeyDown,
    KeyHeld,

    AltKeyUp,
    AltKeyDown,
    AltKeyHeld
  };

  class KeyboardEvent {

    public:
      KeyboardEvents type;
      
    public:
      char code0 = 0;
      char code1 = 0;

    public:
      bool operator==(const KeyboardEvent& other) const {
        return (type == other.type) 
            && (code0 == other.code0)
            && (code1 == other.code1);
      }

  };

}


namespace std {

  template <>
  struct hash<InputDevices::KeyboardEvent> 
  {
    std::size_t operator()(const InputDevices::KeyboardEvent& k) const 
    {
      return (hash<char>()((char) k.type) 
            ^ hash<char>()(k.code0) >> 1) 
            ^ hash<char>()(k.code1);
    }
  };

}

