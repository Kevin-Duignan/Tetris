constexpr int GAP = 4;
constexpr int ROWS = 20;
constexpr int COLUMNS = 12;
constexpr int CELL_SIZE = 25;

enum class cellType : short {
  empty,
  active,
  sealed
}; // empty means there is no block, acive means there is a block that can move,
   // sealed means there is a block that can't move.
