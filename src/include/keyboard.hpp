#pragma once

#include <keyboard-events.hpp>
#include <keyboard-layouts.hpp>

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <thread>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <unordered_map>

class Keyboard {

  public:
    Keyboard();
    ~Keyboard();

  public:
    template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
    void remove_events(Keycode keycode) {
      // Not implemented yet
    }

    template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
    void on_key_up (Keycode keycode, std::function<void ()> callback) {
      KeyboardEvent event = {
        KeyboardEvents::KeyUp,
        (char) keycode,
        0
      };

      m_event_callback_map.insert_or_assign(event, callback);
    }

    template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
    void on_key_down (Keycode keycode, std::function<void ()> callback) {
      KeyboardEvent event = {
        KeyboardEvents::KeyDown,
        (char) keycode,
        0
      };

      m_event_callback_map.insert_or_assign(event, callback);
    };

    template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
    void on_alt_key_down(Keycode keycode, Keycode and_keycode, std::function<void()> callback) {
      KeyboardEvent event = {
        KeyboardEvents::AltKeyDown,
        (char) keycode,
        (char) and_keycode
      };

      m_event_callback_map.insert_or_assign(event, callback);
    }

  private:
    void m_event_loop();
    void m_process_key_press(unsigned short keycode);
    void m_process_key_release(unsigned short keycode);

  private:
    std::thread m_thread;
    std::unordered_map<KeyboardEvent, std::function<void ()>> m_event_callback_map;

  private:
    int m_keyboard_fd = 0;
    bool m_shutdown = false;

  private:
    std::vector<bool> m_held_keys;

};
