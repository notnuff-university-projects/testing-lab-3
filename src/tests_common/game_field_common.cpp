#include "game_field_common.h"

std::shared_ptr<GameField> CreateGameField(std::initializer_list<std::initializer_list<CellState>> matrix) {
  auto rows = matrix.size();
  if (rows == 0) return nullptr;
  auto cols = matrix.begin()->size();

  auto field = std::make_shared<tetris_model::GameField>(rows, cols);

  int i = 0;
  for(const auto& cell_rows : matrix) {
    int j = 0;
    for(const auto& cell : cell_rows) {
      field->SetCellState(i, j, cell);
      ++j;
    }
    ++i;
  }

  return field;
}
