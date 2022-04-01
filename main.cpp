#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <curses.h>

#include "screen.h"
#include "types.h"

characterType input_character = 'l';
characterType processed_character = 'l';
characterType output_character = 'l';
std::mutex character_mutex;

using namespace std::chrono_literals;
constexpr std::chrono::milliseconds input_interval(50ms);
constexpr std::chrono::milliseconds refresh_interval(100ms);

int GetCharacter() {
  return getch();
}

struct ReadInput {
  void operator()() {
    while (input_character = GetCharacter()) {
      if (IsGameOver())
        return;
      std::lock_guard<std::mutex> character_mutex_guard(character_mutex);
      processed_character = input_character;
      std::this_thread::sleep_for(input_interval);
      if (input_character == 'q')
        break;
    }
  }
};

struct Display {
  void operator()() {
    std::unique_lock<std::mutex> character_mutex_lock(character_mutex);
    while (processed_character != 'q') {
      if (IsGameOver())
        return;
      output_character = processed_character;
      character_mutex.unlock();
      std::this_thread::sleep_for(refresh_interval);
      character_mutex.lock();
      UpdateScreen(output_character);
      RefreshScreen();
    }
  }
};

int main() {
  InitScreen();

  std::thread tReadInput((ReadInput()));
  std::thread tProcessInput((Display()));

  tReadInput.join();
  tProcessInput.join();

  UninitScreen();
  return 0;
}
