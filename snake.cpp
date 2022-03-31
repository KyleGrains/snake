#include "snake.h"
#include <ncurses.h>
#include "types.h"
MoveResult Snake::Move(Direction direction) {
  if ((movedirection == Direction::Up && direction == Direction::Down) ||
      (direction == Direction::Up && movedirection == Direction::Down) ||
      (movedirection == Direction::Left && direction == Direction::Right) ||
      (direction == Direction::Left && movedirection == Direction::Right))
    return MoveResult::Nothing;

  movedirection = direction;
  Position head = positions.front();
  switch (direction) {
    case Direction::Left:
      positions.emplace_front(head.y, head.x - 1);
      // headPosition.x -= 1;
      break;
    case Direction::Right:
      positions.emplace_front(head.y, head.x + 1);
      // headPosition.x += 1;
      break;
    case Direction::Up:
      positions.emplace_front(head.y - 1, head.x);
      // headPosition.y -= 1;
      break;
    case Direction::Down:
      positions.emplace_front(head.y + 1, head.x);
      // headPosition.y += 1;
      break;
    default:
      break;
  }
  PopTail();
  if (IsHit())
    return MoveResult::Hit;
  return MoveResult::Move;
}

bool Snake::IsHit() {
  Position head = positions.front();
  if (head.x == 0 || head.x == screen_width || head.y == 0 ||
      head.y == screen_height)
    return true;
  return false;
}

Position Snake::GetTailPosition() {
  return positions.back();
}

void Snake::PopTail() {
  return positions.pop_back();
}

Position Snake::GetHeadPosition() {
  return positions.front();
}

char Snake::GetBodyCharacter() {
  return '*';
}

void Snake::InitPosition(int y, int x) {
  positions.emplace_front(y, x - 4);
  positions.emplace_front(y, x - 3);
  positions.emplace_front(y, x - 2);
  positions.emplace_front(y, x - 1);
  positions.emplace_front(y, x);
}

void Snake::SetBorderSize(int y, int x) {
  screen_height = y;
  screen_width = x;
}

std::deque<Position>& Snake::GetPosition() {
  return positions;
}

void Snake::GrowBack(const Position& position) {
  positions.push_back(position);
}
