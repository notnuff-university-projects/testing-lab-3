#ifndef TETRIS_CONTROLLER_H
#define TETRIS_CONTROLLER_H
#include <memory>

#include "../view/file_system_io_write.h"
#include "../model/game.h"
#include "../model/game_field.h"


using namespace tetris_model;
using namespace tetris_view;


namespace tetris_controller {

class TetrisController {
public:
  explicit TetrisController(const std::shared_ptr<Game_IO_I>& io_interface);
  ~TetrisController() = default;

public:
  void GameInit();
  void GameSimulate();
  void GamePrint();

protected:
  std::shared_ptr<GameField> ParceStringToGameField(const std::string& input_str);
  std::string ParceGameFieldToString(const std::shared_ptr<GameField>& input_field);



protected:
  std::shared_ptr<Game> game_model_ = nullptr;
  std::shared_ptr<Game_IO_I> io_ = nullptr;
};

}


#endif //TETRIS_CONTROLLER_H
