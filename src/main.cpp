#include "screen.h"
#include "types.h"

#include <docopt/docopt.h>

#include <getopt.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

static constexpr char USAGE[] = 
R"(Snake.
    Usage:
      snake
      snake [(-x | --width) <width>] [(-y | --height) <height>]
      snake (-h | --help)
      snake --version    

    Options:
      -h --help  Show this screen
      --version  Show version
)";

struct GamePlay {
  int x;
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
  uint width = 0, height = 0;
  uint playerNumber = 1;
  GameMode gameMode = GameMode::Normal;

  std::map<std::string, docopt::value> args = 
    docopt::docopt(USAGE, {argv + 1, argv + argc}, true, "1.0");

  for(const auto& arg : args)
  {
    if(arg.first == "<height>" && arg.second)
      height = static_cast<uint>(arg.second.asLong());
    else if(arg.first == "<width>" && arg.second)
      width = static_cast<uint>(arg.second.asLong());
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
