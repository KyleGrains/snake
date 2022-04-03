#include "screen.h"
#include "types.h"

#include <curses.h>

#include "getopt.h"
#include "unistd.h"

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

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

static struct option long_options[] = {{"help", no_argument, 0, '?'},
                                       {"width", required_argument, 0, 'w'},
                                       {"height", required_argument, 0, 'h'},
                                       {0, 0, 0, 0}};

int main(int argc, char** argv) {
  int c;
  int width = 0, height = 0;
  GameMode gameMode = GameMode::Normal;
  while (1) {
    c = getopt_long(argc, argv, "?w:h:", long_options, NULL);

    if (c == -1)
      break;

    switch (c) {
      case '?':
        gameMode = GameMode::Help;
        break;
      case 'h':
        if (optarg)
          height = std::atoi(optarg);
        break;
      case 'w':
        if (optarg)
          width = std::atoi(optarg);
        break;
      default:
        gameMode = GameMode::Normal;
    }
  }

  InitScreen(gameMode, height, width);

  std::thread tReadInput((ReadInput()));
  std::thread tProcessInput((Display()));

  tReadInput.join();
  tProcessInput.join();

  UninitScreen();
  return 0;
}
