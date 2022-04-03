#include "snake.h"
#include <ncurses.h>
#include <algorithm>
#include <cassert>
#include "types.h"

void Snake::InitPosition(int y, int x, int length) {
  for (int i = 0; i < 5; ++i)
    positions.emplace_front(y, x + i);
}

MoveResult Snake::Move(Direction direction) {
  if ((moveDirection == Direction::Up && direction == Direction::Down) ||
      (direction == Direction::Up && moveDirection == Direction::Down) ||
      (moveDirection == Direction::Left && direction == Direction::Right) ||
      (direction == Direction::Left && moveDirection == Direction::Right)) {
    moveDirection = moveDirection;
  } else
    moveDirection = direction;

  Position head = positions.front();
  switch (moveDirection) {
    case Direction::Left:
      positions.emplace_front(head.y, head.x - 1);
      break;
    case Direction::Right:
      positions.emplace_front(head.y, head.x + 1);
      break;
    case Direction::Up:
      positions.emplace_front(head.y - 1, head.x);
      break;
    case Direction::Down:
      positions.emplace_front(head.y + 1, head.x);
      break;
    default:
      abort();
      break;
  }
  PopTail();
  if (HitItself())
    return MoveResult::Hit;
  return MoveResult::Move;
}

void Snake::PopTail() {
  assert(!positions.empty());
  positions.pop_back();
}

void Snake::GrowBack(const Position& position) {
  positions.push_back(position);
}

const char Snake::GetBodyCharacter() const {
  return '*';
}

const Position& Snake::GetHeadPosition() const {
  return positions.front();
}

const Position& Snake::GetTailPosition() const {
  return positions.back();
}

const std::deque<Position>& Snake::GetPositions() const {
  return positions;
}

bool Snake::HitItself() {
  if (count(positions.begin(), positions.end(), positions.front()) > 1)
    return true;
  return false;
}
