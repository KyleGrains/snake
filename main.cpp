#include "screen.h"
#include "types.h"

#include <curses.h>
#include <getopt.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

static struct option long_options[] = {{"help", no_argument, 0, '?'},
                                       {"width", required_argument, 0, 'w'},
                                       {"height", required_argument, 0, 'h'},
                                       {0, 0, 0, 0}};

struct GamePlay {
  void operator()() {
    using namespace std::chrono_literals;
    constexpr std::chrono::milliseconds refresh_interval(100ms);

    while (true) {
      GetInputCharacter();

      if (IsGameOver())
        return;

      UpdateScreen();
      RefreshScreen();

      std::this_thread::sleep_for(refresh_interval);
    }
  }
};

int main(int argc, char** argv) {
  int opt;
  int width = 0, height = 0;
  GameMode gameMode = GameMode::Normal;

  while (1) {
    if ((opt = getopt_long(argc, argv, "?w:h:", long_options, NULL)) == -1)
      break;

    switch (opt) {
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

  GamePlay()();

  UninitScreen();
  return 0;
}
