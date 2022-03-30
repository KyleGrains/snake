#ifndef SCREEN_H
#define SCREEN_H
#include <chrono>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <curses.h>

#include "snake.h"
#include "types.h"

void InitScreen();
void UninitScreen();
void UpdateScreen(characterType);
void RefreshScreen();

template <class ScreenType> class AbstractScreen {
public:
  static ScreenType &GetInstance() {
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

private:
  AbstractScreen(const AbstractScreen &) = delete;
  AbstractScreen &operator=(const AbstractScreen &) = delete;
};

class NcursesScreen : public AbstractScreen<NcursesScreen> {
public:
  void Init() override;
  void Update(characterType) override;
  void Refresh() override;
  void Clear() override;
  void Uninit() override;

  NcursesScreen() = default;
  ~NcursesScreen() = default;

private:
  NcursesScreen(const NcursesScreen &) = delete;
  NcursesScreen &operator=(const NcursesScreen &) = delete;
  int window_width;
  int window_height;
  Snake snake;
};

#endif
