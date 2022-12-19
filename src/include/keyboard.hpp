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

namespace InputDevices {

  class Keyboard {

    public:
      Keyboard();
      ~Keyboard();

    public:
      /**
       * @brief 
       * Directly add an event to handel by creating your own event.
       * 
       * @param event 
       * Event struct, for more information refer to keyboard-events.hpp.
       * @param callback 
       * Callback to make when event occurs.
       */
      inline void on(KeyboardEvent event, std::function<void()> callback) { 
        m_event_callback_map.insert_or_assign(event, callback); 
      }

      /**
       * @brief
       * Remove all events associated with the Keycode.
       * 
       * @tparam Keycode 
       * @param keycode 
       * Keycode to remove events
       */
      template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
      void remove_events(Keycode keycode) {
        // Not implemented yet
      }

      /**
       * @brief 
       * Remove an event directly.
       * 
       * @param event
       * Event to remove. 
       */
      inline void remove_event(KeyboardEvent event) {
        m_event_callback_map.erase(event);
      }

    public:
      //--* The following are methods to make this claass easy to use, they just create the Event struct for you *--//

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
      void on_key_held (Keycode keycode, std::function<void ()> callback) {
        KeyboardEvent event = {
          KeyboardEvents::KeyHeld,
          (char) keycode,
          0
        };

        m_event_callback_map.insert_or_assign(event, callback);
      }

      template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
      void on_alt_key_down(Keycode keycode, Keycode and_keycode, std::function<void()> callback) {
        KeyboardEvent event = {
          KeyboardEvents::AltKeyDown,
          (char) keycode,
          (char) and_keycode
        };

        m_event_callback_map.insert_or_assign(event, callback);
      }

      template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
      void on_alt_key_up(Keycode keycode, Keycode and_keycode, std::function<void()> callback) {
        KeyboardEvent event = {
          KeyboardEvents::AltKeyUp,
          (char) keycode,
          (char) and_keycode
        };

        m_event_callback_map.insert_or_assign(event, callback);
      }

      template<typename Keycode, typename std::enable_if<std::is_enum<Keycode>::value>::type* = nullptr>
      void on_alt_key_held(Keycode keycode, Keycode and_keycode, std::function<void()> callback) {
        KeyboardEvent event = {
          KeyboardEvents::AltKeyHeld,
          (char) keycode,
          (char) and_keycode
        };

        m_event_callback_map.insert_or_assign(event, callback);
      }

    private:
      // Internal private methods used to handel events.
      void p_event_loop();
      void p_process_key_held(unsigned short keycode);
      void p_process_key_press(unsigned short keycode);
      void p_process_key_release(unsigned short keycode);

    private:
      std::thread m_thread;
      std::unordered_map<KeyboardEvent, std::function<void ()>> m_event_callback_map;

    private:
      int m_keyboard_fd = 0;
      bool m_shutdown = false;

    private:
      std::vector<bool> m_held_keys;

  };

}
