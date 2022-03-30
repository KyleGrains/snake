#include "snake.h"
#include "types.h"
MoveResult Snake::Move(Direction direction) {
  switch (direction) {
  case Direction::Left:
    headPosition.x -= 1;
    break;
  case Direction::Right:
    headPosition.x += 1;
    break;
  case Direction::Up:
    headPosition.y -= 1;
    break;
  case Direction::Down:
    headPosition.y += 1;
    break;
  default:
    break;
  }
  return MoveResult::Nothing;
}

Position Snake::GetTailPosition() { return tailPosition; }

Position Snake::GetHeadPosition() { return headPosition; }
