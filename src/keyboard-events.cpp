#include <keyboard-events.hpp>

KeyBoardEvents::KeyBoardEvents() {
  // Open input device
  m_keyboard_fd = open("/dev/input/event4", O_RDONLY);
  
  if (m_keyboard_fd == -1) {
    // Somthing went wrong
    throw std::runtime_error("Error in open keyboard");
  } 

  m_thread = std::thread(&KeyBoardEvents::m_event_loop, this);
}

KeyBoardEvents::~KeyBoardEvents() {
  m_shutdown = true;

  if (m_keyboard_fd)
    close(m_keyboard_fd);

  m_thread.join();
}

void KeyBoardEvents::m_process_key_press(unsigned short keycode) {
  auto itr = m_keydown_callback_map.find(static_cast<char>(keycode));

  if (itr == m_keydown_callback_map.end()) return;

  itr->second();
}

void KeyBoardEvents::m_process_key_release(unsigned short keycode) {
  auto itr = m_keyup_callback_map.find(static_cast<char>(keycode));

  if (itr == m_keyup_callback_map.end()) return;

  itr->second();
}

void KeyBoardEvents::m_event_loop() {
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

    (event.value == 1) ? m_process_key_press(event.code) : m_process_key_release(event.code);
  }
}
