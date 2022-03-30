#include "screen.h"
#include <iostream>

template <class ScreenType>
AbstractScreen<ScreenType>::~AbstractScreen() {}

void NcursesScreen::Init() {
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  curs_set(0);

  border('|', '|', '-', '-', '+', '+', '+', '+');

  getmaxyx(stdscr, screen_height, screen_width);
  move(screen_height / 2, screen_width / 2);

  snake.InitPosition(screen_height / 2, screen_width / 2);
	snake.SetBorderSize(screen_height, screen_width);
	for(auto pos: snake.GetPosition())
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

  Position previoustailPosition = snake.GetTailPosition();
  MoveResult result = snake.Move(direction);
  Position headPosition = snake.GetHeadPosition();
  switch (result) {
    case MoveResult::Eat:
      mvaddch(headPosition.y, headPosition.x, snake.GetBodyCharacter());
      break;
    case MoveResult::Move:
      mvaddch(headPosition.y, headPosition.x, snake.GetBodyCharacter());
      mvaddch(previoustailPosition.y, previoustailPosition.x, ' ');
      break;
    case MoveResult::Hit:
      clear();
      mvaddstr(screen_height / 2, screen_width / 2, "Game Over");
    default:
      break;
  }
}

void NcursesScreen::Refresh() {
  refresh();
}

void NcursesScreen::Clear() {
  clear();
}

void NcursesScreen::Uninit() {
  endwin();
}

typedef NcursesScreen theScreen;
void InitScreen() {
  theScreen::GetInstance().Init();
}

void UninitScreen() {
  theScreen::GetInstance().Uninit();
}

void RefreshScreen() {
  theScreen::GetInstance().Refresh();
}

void UpdateScreen(characterType output_character) {
  theScreen::GetInstance().Update(output_character);
}
