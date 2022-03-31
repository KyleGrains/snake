#include "screen.h"
#include <algorithm>
#include <future>
#include <iostream>
#include <random>

using namespace std::chrono_literals;
constexpr std::chrono::milliseconds generate_interval(3s);

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
  for (auto pos : snake.GetPosition())
    addch(snake.GetBodyCharacter());

  std::thread([this] { this->GenerateFood(); }).detach();
}

void NcursesScreen::GenerateFood() {
  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> random_x_distribution(1, screen_width - 1);
  std::uniform_int_distribution<int> random_y_distribution(1,
                                                           screen_height - 1);
  while (true) {
    std::this_thread::sleep_for(generate_interval);
    int x = random_x_distribution(e);
    int y = random_y_distribution(e);

    std::lock_guard<std::mutex> lock(foods_mutex);
    generating_foods.push_back(Position(y, x));
  }
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

  auto find_food = std::find(begin(foods), end(foods), headPosition);
  if (find_food != foods.end()) {
    foods.erase(find_food);
    result = MoveResult::Eat;
  }

  switch (result) {
    case MoveResult::Eat:
      mvaddch(headPosition.y, headPosition.x, snake.GetBodyCharacter());
      snake.GrowBack(previoustailPosition);
      break;
    case MoveResult::Move:
      mvaddch(headPosition.y, headPosition.x, snake.GetBodyCharacter());
      mvaddch(previoustailPosition.y, previoustailPosition.x, ' ');
      break;
    case MoveResult::Hit:
      clear();
      mvaddstr(screen_height / 2, screen_width / 2 - 4, "Game Over");
    default:
      break;
  }
  std::lock_guard<std::mutex> lock(foods_mutex);
  if (!generating_foods.empty()) {
    Position food = generating_foods.back();
    generating_foods.pop_back();
    mvaddch(food.y, food.x, 'o');
    foods.push_back(food);
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
