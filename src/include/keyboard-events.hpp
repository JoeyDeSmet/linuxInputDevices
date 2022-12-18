#pragma once

#include <functional>

enum class KeyboardEvents {
  KeyUp,
  KeyDown,
  KeyRepeat,

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

namespace std {

  template <>
  struct hash<KeyboardEvent> 
  {
    std::size_t operator()(const KeyboardEvent& k) const 
    {
      return (hash<char>()((char) k.type) 
            ^ hash<char>()(k.code0) >> 1) 
            ^ hash<char>()(k.code1);
    }
  };

}

