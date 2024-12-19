//
// Created by notnuff on 18.12.24.
//

#include "tetris_controller.h"

namespace tetris_controller {

TetrisController::TetrisController(
    const std::shared_ptr<Game_IO_I>& io_interface) : io_(io_interface) {

}

void TetrisController::GameInit() {
  auto input_str = io_->Read();
  auto game_field = ParceStringToGameField(input_str);
  game_model_ = std::make_shared<Game>(game_field);
}

void TetrisController::GameSimulate() {
  game_model_->Run();
}

void TetrisController::GamePrint() {
  auto output_str = ParceGameFieldToString( game_model_->GetField() );
  io_->Write(output_str);
}

std::shared_ptr<GameField> TetrisController::ParceStringToGameField(
    const std::string& input_str) {

}

std::string TetrisController::ParceGameFieldToString(
    const std::shared_ptr<GameField>& input_field) {

}


}
