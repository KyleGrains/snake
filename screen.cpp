#include "screen.h"
#include <iostream>

template <class ScreenType> AbstractScreen<ScreenType>::~AbstractScreen() {}

void NcursesScreen::Init() {
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  curs_set(0);

  box(stdscr, '|', '-');

  getmaxyx(stdscr, window_height, window_width);
  move(window_height / 2, window_width / 2);

  snake.SetPosition(window_height / 2, window_width / 2);
  addch(snake.GetBodyCharacter());
}

void NcursesScreen::Update(characterType output_character) {
  Direction direction = Direction::Stop;
  switch (output_character) {
  case 'h':
  case 'a':
  case KEY_LEFT:
    direction = Direction::Left;
    break;
  case 'l':
  case 'd':
  case KEY_RIGHT:
    direction = Direction::Right;
    break;
  case 'j':
  case 's':
  case KEY_DOWN:
    direction = Direction::Down;
    break;
  case 'k':
  case 'w':
  case KEY_UP:
    direction = Direction::Up;
    break;
  default:
    break;
  }

  Position headPosition;
  Position previoustailPosition = snake.GetTailPosition();
  MoveResult result = snake.Move(direction);
  headPosition = snake.GetHeadPosition();
  switch (result) {
  case MoveResult::Eat:
    mvaddch(headPosition.y, headPosition.x, snake.GetBodyCharacter());
    break;
  case MoveResult::Nothing:
    mvaddch(headPosition.y, headPosition.x, snake.GetBodyCharacter());
    mvaddch(previoustailPosition.y, previoustailPosition.x, ' ');
    break;
  case MoveResult::Hit:
    clear();
    mvaddstr(window_height / 2, window_width / 2, "Game Over");
  default:
    break;
  }
}

void NcursesScreen::Refresh() { refresh(); }

void NcursesScreen::Clear() { clear(); }

void NcursesScreen::Uninit() { endwin(); }

typedef NcursesScreen theScreen;
void InitScreen() { theScreen::GetInstance().Init(); }

void UninitScreen() { theScreen::GetInstance().Uninit(); }

void RefreshScreen() { theScreen::GetInstance().Refresh(); }

void UpdateScreen(characterType output_character) {
  theScreen::GetInstance().Update(output_character);
}
