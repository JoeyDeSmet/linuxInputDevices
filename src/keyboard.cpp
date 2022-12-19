#include <keyboard.hpp>

#include <iostream>

namespace InputDevices {

  Keyboard::Keyboard() 
    : m_held_keys(90)
  {
    std::string path = "/dev/input/";

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
      if (entry.is_directory()) continue;

      if (entry.path().string().find("event") != std::string::npos) {
        m_keyboard_fd = open(entry.path().c_str(), O_RDONLY);
        if (m_keyboard_fd == -1) throw std::runtime_error("Error in open keyboard");

        char name[256] = "";
        ioctl(m_keyboard_fd, EVIOCGNAME(sizeof(name)), name);

        std::string sname(name);
        if (sname.find("keyboard") != std::string::npos) break;

        close(m_keyboard_fd);
      }
    } 

    m_thread = std::thread(&Keyboard::p_event_loop, this);
  }

  Keyboard::~Keyboard() {
    m_shutdown = true;

    if (m_keyboard_fd)
      close(m_keyboard_fd);

    m_thread.join();
  }

  void Keyboard::p_process_key_held(unsigned short keycode) {
    for (auto& [event, callback] : m_event_callback_map) {
      bool condition1 = (event.type == KeyboardEvents::KeyHeld && event.code0 == keycode);
      bool condition0 = (event.type == KeyboardEvents::AltKeyHeld && m_held_keys[event.code0] && m_held_keys[event.code1]);
        
      if (condition0 || condition1) callback();
    }
  }

  void Keyboard::p_process_key_press(unsigned short keycode) {
    m_held_keys[keycode] = true;
    
    for (auto& [event, callback] : m_event_callback_map) {
      bool condition1 = (event.type == KeyboardEvents::KeyDown && event.code0 == keycode);
      bool condition0 = (event.type == KeyboardEvents::AltKeyDown && m_held_keys[event.code0] && m_held_keys[event.code1]);
        
      if (condition0 || condition1) callback();
    }
  }

  void Keyboard::p_process_key_release(unsigned short keycode) {
    m_held_keys[keycode] = false;

    for (auto& [event, callback] : m_event_callback_map) {
      bool condition1 = (event.type == KeyboardEvents::KeyUp && event.code0 == keycode);
      bool condition0 = (event.type == KeyboardEvents::AltKeyUp && m_held_keys[event.code0] && m_held_keys[event.code1]);
        
      if (condition0 || condition1) callback();
    }
  }

  void Keyboard::p_event_loop() {
    fd_set fds;
    timeval timeout;
    
    while (true) {
      timeout.tv_sec = 0;
      timeout.tv_usec = 1000;

      FD_ZERO(&fds);
      FD_SET(m_keyboard_fd, &fds);

      int select_status = select(m_keyboard_fd + 1, &fds, NULL, NULL, &timeout);

      if (select_status == -1 || m_shutdown) break; // Check if we have to shutdown 

      if (select_status == 0) continue;

      input_event event;
      int bytes_read = read(m_keyboard_fd, &event, sizeof(event));

      // Check if we received the correct amount of bytes
      if (bytes_read != sizeof(event) || event.type != EV_KEY) continue;

      // Auto repeat
      if (event.value == 2)
        p_process_key_held(event.code);
      
      // Key press
      else if (event.value == 1)
        p_process_key_press(event.code);
      
      // Key release
      else if (event.value == 0)
        p_process_key_release(event.code);

    }
  }
  
}
