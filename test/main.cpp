#include <keyboard.hpp>
#include <keyboard-layouts.hpp>

#include <mutex>
#include <csignal>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <iostream>
#include <condition_variable>

namespace { // Used for signal handeling
  std::mutex mtx;
  std::condition_variable shutdown_request;
}

void shutdown(int sig) {
  std::lock_guard lock(mtx);
  shutdown_request.notify_all();
}

struct termios orig_termios;
struct termios new_termios;

void reset_terminal_mode() {
  tcsetattr(0, TCSANOW, &orig_termios);
}

using namespace KeyboardLayouts::AZERTY;

int main() {
  tcgetattr(0, &orig_termios);
  memcpy(&new_termios, &orig_termios, sizeof(new_termios));

  atexit(reset_terminal_mode);
  
  new_termios.c_lflag &= ~ECHO;
  cfmakeraw(&new_termios);
  
  tcsetattr(0, TCSANOW, &new_termios);

  signal(SIGINT, shutdown);

  Keyboard keyboard;

  keyboard.on_key_down(KeyCode::ESC, []() {
    std::lock_guard lock(mtx);
    shutdown_request.notify_all();
  });

  keyboard.on_key_down(KeyCode::Z, []() {
    std::cout << "UP\r" << std::endl;
  });
  
  keyboard.on_key_down(KeyCode::Q, []() {
    std::cout << "LEFT\r" << std::endl;
  });

  keyboard.on_key_up(KeyCode::S, []() {
    std::cout << "DOWN\r" << std::endl;
  });

  keyboard.on_key_down(KeyCode::D, []() {
    std::cout << "RIGHT\r" << std::endl;
  });

  keyboard.on_alt_key_down(KeyCode::LEFTCTRL, KeyCode::C, []() {
    std::cout << "Try pressing ESC\r" << std::endl;
  });

  keyboard.on_key_held(KeyCode::A, []() {
    static int i = 0;
    std::cout << i << "\r" << std::flush;
    i++;
  });

  std::unique_lock lock(mtx);
  shutdown_request.wait(lock);

  return 0;
}
