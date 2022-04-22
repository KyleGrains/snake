#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include "types.h"

class Snake {
 public:
  Snake() = default;
  Snake(const Snake&) = delete;

  void InitPosition(int y, int x, int length = 5);
  MoveResult Move(Direction);
  void PopTail();
  void GrowBack(const Position& position);

  char GetBodyCharacter() const;
  const Position& GetHeadPosition() const;
  const Position& GetTailPosition() const;
  const std::deque<Position>& GetPositions() const;

 private:
  bool HitItself();
  std::deque<Position> positions;
  Direction moveDirection;
};

#endif
