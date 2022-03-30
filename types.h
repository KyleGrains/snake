#ifndef TYPES_H
#define TYPES_H
#include <cstdint>
using uint = uint32_t;
using characterType = int;

struct Position {
  int y;
  int x;
	Position(int ty, int tx): y(ty), x(tx) {};
};

enum class Direction { Up, Right, Left, Down, Stop };

enum class MoveResult { Move, Eat, Nothing, Hit };

enum class Dot {
  Empty,
  Snake,
  Border,
  BorderUp,
  BorderDown,
  BorderLeft,
  BorderRight,
  CRLF
};
#endif
