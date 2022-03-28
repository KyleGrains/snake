#include <chrono>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include <curses.h>

#include "types.h"

void InitScreen();
void UninitScreen();

template <class ScreenType>
class AbstractScreen {
public:
  static ScreenType& GetInstance()
  {
    static ScreenType screen;
    return screen;
  }
  AbstractScreen() = default;
  virtual ~AbstractScreen() = 0;
  virtual void Init() {};
  virtual void Update() {};
  virtual void Refresh() {};
  virtual void Display() {};
  virtual void Clear() {};
  virtual void Uninit() {};

private:
  AbstractScreen(const AbstractScreen&) = delete;
  AbstractScreen& operator=(const AbstractScreen&) = delete;
};

class NcursesScreen: public AbstractScreen<NcursesScreen> {
public:
  void Init() override;
  void Update() override;
  void Refresh() override;
  void Display() override;
  void Clear() override;
  void Uninit() override;

  NcursesScreen() = default;
  ~NcursesScreen() = default;
private:
  NcursesScreen(const NcursesScreen&) = delete;
  NcursesScreen& operator=(const NcursesScreen&) = delete;
};

class Screen: public AbstractScreen<Screen> {
public:
  void Init() override;
  void Update() override;
  void Display() override;

	Screen() = default;
  ~Screen() = default;
private:
  void SetSize(uint w = 50, uint h = 20)
  {
    width = w;
    height = h;
    size = height * (width + 1); //for the '\n' characters
  }
  const std::string& ToString();

  void ClearScreen() { printf("\033[H\033[J"); }
  void SaveCursorPosition() { printf("\033[s"); }
  void RestoreCursorPosition() { printf("\033[u"); }

private:
  uint width = 0;
  uint height = 0;
  uint size = 400;
  std::vector<Dot> coordinates;
  std::string coordinates_string;
};
