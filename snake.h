#include <vector>
#include "types.h"

class Snake{
public:
  Snake() = default;
  Snake(const Snake&) = delete;
  void Update();

private:
  void DoRun();
  std::vector<Dot> snakeDots;
};

