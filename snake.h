#include "types.h"

class Snake{
public:
  Snake() = default;
  Snake(const Snake&) = delete;
  MoveResult Move(Direction);
	char GetBodyCharacter();
	Position GetTailPosition();
	Position GetHeadPosition();
	void SetPosition(int y, int x);

private:
	Position headPosition;
	Position tailPosition;
};

inline char Snake::GetBodyCharacter()
{
	return '*';
}

inline void Snake::SetPosition(int y, int x) {
	headPosition.y = y;
	headPosition.x = x;
	tailPosition.y = y;
	tailPosition.x = x;
}

