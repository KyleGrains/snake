#include <cstdint>
#ifndef TYPES_H
#define TYPES_H
using uint = uint32_t;

enum class Direction
{
  up,
  down,
  left,
  right
};

enum class Dot
{
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
