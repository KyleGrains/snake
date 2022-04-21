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

static struct option long_options[] = {
    {"help", no_argument, 0, '?'},
    {"width", required_argument, 0, 'w'},
    {"height", required_argument, 0, 'h'},
    {"playernumber", required_argument, 0, 'p'},
    {0, 0, 0, 0}};

struct GamePlay {
  void operator()() {
    constexpr std::chrono::milliseconds refresh_interval(100);

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
  uint opt = '?';
  uint width = 0, height = 0;
  uint playerNumber = 1;
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
          height = static_cast<uint>(std::atoi(optarg));
        break;
      case 'w':
        if (optarg)
          width = static_cast<uint>(std::atoi(optarg));
        break;
      case 'p':
        if (optarg)
          playerNumber = static_cast<uint>(std::atoi(optarg));
      default:
        gameMode = GameMode::Normal;
    }
  }

  GameConfig gameConfig;
  gameConfig.gameMode = gameMode;
  gameConfig.height = height;
  gameConfig.width = width;
  gameConfig.playerNumber = playerNumber;

  InitScreen(gameConfig);

  GamePlay()();

  UninitScreen();
  return 0;
}
