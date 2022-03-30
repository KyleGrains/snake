#ifndef SNAKE_H
#define SNAKE_H
#include <deque>
#include "types.h"

class Snake {
 public:
  Snake() = default;
  Snake(const Snake&) = delete;
  MoveResult Move(Direction);
  char GetBodyCharacter();
  Position GetTailPosition();
	void PopTail();
  Position GetHeadPosition();
  void InitPosition(int y, int x);
	std::deque<Position>& GetPosition();
  void SetBorderSize(int y, int x);

 private:
	bool IsHit();
	std::deque<Position> positions;
	Direction movedirection;
  int screen_width;
  int screen_height;
};

#endif
