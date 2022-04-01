#ifndef SCREEN_H
#define SCREEN_H
#include <atomic>
#include <chrono>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>
//#include <unordered_set>
#include <vector>

#include <curses.h>

#include "snake.h"
#include "types.h"

void InitScreen();
void UninitScreen();
void UpdateScreen(characterType);
void RefreshScreen();
bool IsGameOver();

template <class ScreenType>
class AbstractScreen {
 public:
  static ScreenType& GetInstance() {
    static ScreenType screen;
    return screen;
  }
  AbstractScreen() = default;
  virtual ~AbstractScreen() = 0;
  virtual void Init(){};
  virtual void Update(characterType){};
  virtual void Refresh(){};
  virtual void Clear(){};
  virtual void Uninit(){};
  virtual bool IsGameOver() { return false; };

 private:
  AbstractScreen(const AbstractScreen&) = delete;
  AbstractScreen& operator=(const AbstractScreen&) = delete;
};

class NcursesScreen : public AbstractScreen<NcursesScreen> {
 public:
  void Init() override;
  void Update(characterType) override;
  void Refresh() override;
  void Clear() override;
  void Uninit() override;
  bool IsGameOver() override;

  NcursesScreen() = default;
  ~NcursesScreen() = default;

 private:
  NcursesScreen(const NcursesScreen&) = delete;
  NcursesScreen& operator=(const NcursesScreen&) = delete;
  void GenerateFood();
  int screen_width;
  int screen_height;
  Snake snake;
  std::vector<Position> generating_foods;
  std::vector<Position> foods;
  std::mutex foods_mutex;
  std::atomic<bool> stopThread;
};

#endif
