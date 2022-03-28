#include "screen.h"
#include <iostream>

template <class ScreenType>
AbstractScreen<ScreenType>::~AbstractScreen(){}

void NcursesScreen::Init()
{
  initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
}

void NcursesScreen::Update()
{

}

void NcursesScreen::Refresh()
{

}

void NcursesScreen::Display()
{

}

void NcursesScreen::Clear()
{
  clear();
}

void NcursesScreen::Uninit()
{
  endwin();
}


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

typedef NcursesScreen theScreen;
void InitScreen()
{
  theScreen::GetInstance().Init();
}

void UninitScreen()
{
  theScreen::GetInstance().Uninit();
}

