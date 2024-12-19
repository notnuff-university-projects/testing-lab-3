#ifndef GAME_FIELD_COMMON_H
#define GAME_FIELD_COMMON_H
#include <memory>

#include "../model/game_field.h"

using namespace tetris_model;


const auto E = CellState::EMPTY;
const auto G = CellState::FIGURE;
const auto L = CellState::LANDSCAPE;

std::shared_ptr<GameField> CreateGameField(std::initializer_list<std::initializer_list<CellState>> matrix);

#endif //GAME_FIELD_COMMON_H
