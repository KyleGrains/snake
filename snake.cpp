#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <vector>
#include <iostream>

using uint = uint32_t;
using namespace std::chrono_literals;

void InitScreen();
void ReadInput();
void UpdateScreen();
void RefreshScreen();
int main()
{
  InitScreen();

  while(true)
  {
    ReadInput();

    UpdateScreen();

    RefreshScreen();

    std::this_thread::sleep_for(1000ms);
  }
  int i;
  return 0;
}

enum class Direction
{
  up,
  down,
  left,
  right
};

enum class Dot
{
  Empty,
  Snake,
  Border,
  BorderUp,
  BorderDown,
  BorderLeft,
  BorderRight,
  CRLF
};

class Snake{
public:
  Snake() = default;
  Snake(const Snake&) = delete;
  void Update();

private:
  void DoRun();
  std::vector<Dot> snakeDots;
};

class Screen {
public:
  static Screen& GetInstance()
  {
    static Screen screen;
    return screen;
  }
  void Init();
  void Update();
  void Refresh();
  void Display();

  ~Screen() = default;
private:
  Screen() = default;
  Screen(const Screen&) = delete;
  Screen& operator=(const Screen&) = delete;

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

void Screen::Init()
{
  SetSize();
  coordinates.resize(size, Dot::Empty);
  coordinates_string.resize(size);

  uint index = 0;
  for(index = 0; index < width; ++index)
    coordinates[index] = Dot::BorderUp;

  for(index = size - width - 1; index < size - 1; ++index)
    coordinates[index] = Dot::BorderDown;

  for(index = 0; index < size; index += width + 1)
    coordinates[index] = Dot::BorderLeft;

  for(index = width - 1; index < size; index += width + 1)
    coordinates[index] = Dot::BorderRight;

  for(index = width; index < size; index += width + 1)
    coordinates[index] = Dot::CRLF;

  index = 0;
  for(auto &dot: coordinates)
  {
    switch(dot)
    {
    case Dot::Border:
    case Dot::BorderUp:
    case Dot::BorderDown:
    case Dot::BorderLeft:
    case Dot::BorderRight:
      coordinates_string[index] = '=';
      break;
    case Dot::CRLF:
      coordinates_string[index] = '\n';
      break;
    default:
      coordinates_string[index] = ' ';
      break;
    }
    ++index;
  }
};

const std::string& Screen::ToString()
{
  return coordinates_string;
}

void Screen::Update()
{
  uint i = 0;

};

void Screen::Display()
{
  ClearScreen();
  SaveCursorPosition();
  std::cout << "Snake Game \n";
  std::cout << ToString().c_str();
  RestoreCursorPosition();
  std::cout << std::flush;
};

void InitScreen()
{
  Screen::GetInstance().Init();
}

void UpdateScreen()
{
  Screen::GetInstance().Update();
}

void RefreshScreen()
{
  Screen::GetInstance().Display();
}

void ReadInput()
{

}

