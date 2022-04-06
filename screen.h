#ifndef SCREEN_H
#define SCREEN_H
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <curses.h>

#include "snake.h"
#include "types.h"

void InitScreen(GameMode gameMode, int height = 0, int width = 0);
void UninitScreen();
void GetInputCharacter();
void UpdateScreen();
void RefreshScreen();
bool IsGameOver();

class NcursesScreen {
 public:
  static NcursesScreen& GetInstance() {
    static NcursesScreen screen;
    return screen;
  }
  void Init(GameMode gameMode, int height = 0, int width = 0);
  void GetInputCharacter();
  void Update();
  void Refresh();
  void Clear();
  void Uninit();
  bool IsGameOver();

  NcursesScreen() = default;
  ~NcursesScreen() = default;

 private:
  NcursesScreen(const NcursesScreen&) = delete;
  NcursesScreen& operator=(const NcursesScreen&) = delete;
  void GenerateFood();
  int screen_width;
  int screen_height;
  characterType inputCharacter;
  Snake snake;
  std::mutex foodMutex;
  std::condition_variable foodCond;
  Position foodPosition;
  std::atomic<bool> stopThread;
  uint score;
};

#endif
