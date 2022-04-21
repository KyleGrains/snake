#ifndef TYPES_H
#define TYPES_H
#include <cstdint>
using uint = uint32_t;
using characterType = int;

struct Position {
  uint y;
  uint x;
  Position() : y(0), x(0){};
  Position(int ty, int tx) : y(ty), x(tx){};
  Position(const Position& rhs) : y(rhs.y), x(rhs.x){};
  friend bool operator==(const Position& lhs, const Position& rhs) {
    return (lhs.y == rhs.y) && (lhs.x == rhs.x);
  }
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

enum class GameMode { Normal, Help };

struct GameConfig {
  GameMode gameMode;
  uint height;
  uint width;
  uint playerNumber;
};

#endif
