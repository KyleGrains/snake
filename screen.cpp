#include "screen.h"
#include <algorithm>
#include <future>
#include <iostream>
#include <random>

using namespace std::chrono_literals;

void Help() {
  std::cout << "Usage: snake [-?]        [--help]\n"
            << "             [-w <size>] [--width=<size>]\n"
            << "             [-h <size>] [--height=<size>]\n"
            << "Start snake game with default screen size (full screen).\n";
}

void NcursesScreen::Init(GameMode gameMode, int height, int width) {
  if (gameMode == GameMode::Help) {
    Help();
    exit(0);
  }
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  noecho();
  curs_set(0);

  getmaxyx(stdscr, screen_height, screen_width);
  if (height && height < screen_height)
    screen_height = height;
  if (width && width < screen_width)
    screen_width = width;

  if (width == 0 && height == 0) {
    border('|', '|', '-', '-', '+', '+', '+', '+');
  } else {
    mvvline(0, 0, '|', screen_height);
    mvvline(0, screen_width, '|', screen_height);
    mvhline(0, 0, '-', screen_width + 1);
    mvhline(screen_height, 0, '-', screen_width + 1);
  }
  mvaddstr(0, 0, "Score: 0");

  snake.InitPosition(screen_height / 2, screen_width / 2);
  move(screen_height / 2, screen_width / 2);
  for (const auto& pos : snake.GetPositions())
    addch(snake.GetBodyCharacter());

  foodPosition = Position(0, 0);
  score = 0;
  stopThread.store(false);

  std::thread([this] { this->GenerateFood(); }).detach();
}

void NcursesScreen::GenerateFood() {
  std::random_device r;
  std::default_random_engine e(r());
  typedef std::uniform_int_distribution<int> random_distribution;
  random_distribution random_x_distribution(1, screen_width - 1);
  random_distribution random_y_distribution(1, screen_height - 1);

  while (true) {
    if (stopThread.load())
      return;
    int x = random_x_distribution(e);
    int y = random_y_distribution(e);

    std::unique_lock<std::mutex> foodLock(foodMutex);
    foodCond.wait(foodLock,
                  [this] { return (foodPosition == Position(0, 0)); });
    foodPosition = Position(y, x);
    mvaddch(foodPosition.y, foodPosition.x, 'o');
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

  const Position& snakePreviousTail = snake.GetTailPosition();
  MoveResult result = snake.Move(direction);
  const Position& snakeHead = snake.GetHeadPosition();

  if (snakeHead == foodPosition) {
    result = MoveResult::Eat;
  }

  if (snakeHead.x == 0 || snakeHead.x == screen_width || snakeHead.y == 0 ||
      snakeHead.y == screen_height)
    result = MoveResult::Hit;

  switch (result) {
    case MoveResult::Eat:
      mvaddch(snakeHead.y, snakeHead.x, snake.GetBodyCharacter());
      snake.GrowBack(snakePreviousTail);
      {
        std::lock_guard<std::mutex> lock(foodMutex);
        foodPosition = Position(0, 0);
        foodCond.notify_one();
      }
      score += 10;
      mvaddstr(0, 0, "Score: ");
      addstr(std::to_string(score).c_str());
      break;
    case MoveResult::Move:
      mvaddch(snakeHead.y, snakeHead.x, snake.GetBodyCharacter());
      mvaddch(snakePreviousTail.y, snakePreviousTail.x, ' ');
      break;
    case MoveResult::Hit:
      stopThread.store(true);
      clear();
      mvaddstr(screen_height / 2, screen_width / 2 - 4, "Game Over");
      return;
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

bool NcursesScreen::IsGameOver() {
  return stopThread.load();
}

typedef NcursesScreen theScreen;
void InitScreen(GameMode gameMode, int height, int width) {
  theScreen::GetInstance().Init(gameMode, height, width);
}

void UninitScreen() {
  theScreen::GetInstance().Uninit();
}

void RefreshScreen() {
  theScreen::GetInstance().Refresh();
}

bool IsGameOver() {
  return theScreen::GetInstance().IsGameOver();
}

void UpdateScreen(characterType output_character) {
  theScreen::GetInstance().Update(output_character);
}
