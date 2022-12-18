#pragma once

#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include <thread>
#include <stdexcept>
#include <functional>
#include <unordered_map>

class KeyBoardEvents {

  public:
    KeyBoardEvents();
    ~KeyBoardEvents();

  public:
    void remove_event(char keycode);
    void on_key_up (char keycode, std::function<void ()> callback);
    void on_key_down (char keycode, std::function<void ()> callback);

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
