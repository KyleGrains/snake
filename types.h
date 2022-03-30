#ifndef TYPES_H
#define TYPES_H
#include <cstdint>
using uint = uint32_t;
using characterType = int;

struct Position {
  int y;
  int x;
};

enum class Direction { Up, Down, Left, Right, Stop };

enum class MoveResult { Eat, Nothing, Hit };

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
