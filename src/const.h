int constexpr GAP = 4, ROWS = 20, COLUMNS = 12, CELL_SIZE = 25;
enum class cellType : short {
  empty,
  active,
  sealed
}; // empty means there is no block, acive means there is a block that can move,
   // sealed means there is a block that can't move.
