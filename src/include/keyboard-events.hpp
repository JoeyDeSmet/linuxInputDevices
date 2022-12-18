#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <thread>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <unordered_map>

class KeyBoardEvents {

  public:
    KeyBoardEvents();
    ~KeyBoardEvents();

  public:
    template<typename Keycode, typename std::enable_if<std::is_enum<KeyCode>::value>::type* = nullptr>
    void remove_events(KeyCode keycode) {
      m_keyup_callback_map.erase((char) keycode);
      m_keydown_callback_map.erase((char) keycode);
    }

    template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
    void on_key_up (Keycode keycode, std::function<void ()> callback) {
      auto itr = m_keyup_callback_map.find((char) keycode);

      if (itr != m_keyup_callback_map.end()) {
        m_keyup_callback_map.at((char) keycode) = callback;
        return;
      } 

      m_keyup_callback_map[(char) keycode] = callback;
    }

    template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
    void on_key_down (Keycode keycode, std::function<void ()> callback) {
      auto itr = m_keydown_callback_map.find((char) keycode);

      if (itr != m_keydown_callback_map.end()) {
        m_keydown_callback_map.at((char) keycode) = callback;
        return;
      } 

      m_keydown_callback_map[(char) keycode] = callback;
    };

  private:
    void m_event_loop();
    void m_process_key_press(unsigned short keycode);
    void m_process_key_release(unsigned short keycode);

  private:
    std::thread m_thread;
    std::unordered_map<char, std::function<void ()>> m_keyup_callback_map;
    std::unordered_map<char, std::function<void ()>> m_keydown_callback_map;

  private:
    int m_keyboard_fd = 0;
    bool m_shutdown = false;

};
