#include <gtest/gtest.h>

#include "game.h"
#include "exceptions.h"

namespace tetris_model {

std::shared_ptr<GameField> CreateGameField(std::initializer_list<std::initializer_list<CellState>> matrix) {
  auto rows = matrix.size();
  if (rows == 0) return nullptr;
  auto cols = matrix.begin()->size();

  auto field = std::make_shared<GameField>(rows, cols);

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

bool AreFieldsEqual(const std::shared_ptr<GameField>& gf1, const std::shared_ptr<GameField>& gf2) {
  if (gf1->Cols() != gf2->Cols()) return false;
  if (gf1->Rows() != gf2->Rows()) return false;

  for (int i = 0; i < gf1->Rows(); ++i) {
    for (int j = 0; j < gf1->Cols(); ++j) {
      if (gf1->GetCellState(i, j) != gf2->GetCellState(i, j)) return false;
    }
  }

  return true;
}



TEST(TetrisModel, GameInit) {
  EXPECT_THROW(auto game = Game(nullptr), tetris_model::init_error);

  {
    auto gameField = std::make_shared<GameField>(0, 0);
    EXPECT_THROW(auto game = Game(gameField), tetris_model::init_error);
  }

  {
    auto gameField = std::make_shared<GameField>(1, 0);
    EXPECT_THROW(auto game = Game(gameField), tetris_model::init_error);
  }

  {
    auto gameField = std::make_shared<GameField>(0, 1);
    EXPECT_THROW(auto game = Game(gameField), tetris_model::init_error);
  }

  {
    auto gameField = std::make_shared<GameField>(1, 1);
    EXPECT_NO_THROW(auto game = Game(gameField));
  }
}


const auto E = CellState::EMPTY;
const auto G = CellState::FIGURE;
const auto L = CellState::LANDSCAPE;

using init_matrix_t = std::initializer_list<std::initializer_list<CellState>>;
TEST(TetrisModel, GameEmptyRun) {
  {
    init_matrix_t fieldInit = {
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
    };

    auto gameFieldBefore = CreateGameField(fieldInit);

    Game game(CreateGameField(fieldInit));
    game.Run();
    EXPECT_TRUE( AreFieldsEqual( gameFieldBefore, game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, E, E, E, E, E, E, E, E},
      {E, E, L, L, L, E, E, E, E, E},
      {E, E, E, L, L, E, E, E, E, E},
      {L, L, L, L, L, L, L, L, L, L},
    };

    auto gameFieldBefore = CreateGameField(fieldInit);

    Game game(CreateGameField(fieldInit));
    game.Run();
    EXPECT_TRUE( AreFieldsEqual( gameFieldBefore, game.GetField() ) );
  }
}

TEST(TetrisModel, GameRunNoLandscape) {
  // will try different shapes
  {
    init_matrix_t fieldInit = {
      {E, E, G, G, G},
      {E, E, E, E, G},
      {E, E, E, E, E},
      {E, E, E, E, E},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, G, G, G},
      {E, E, E, E, G},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, G, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, G, E, E, E},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {G, G, G, G, G},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, G, G, G, G},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {G, G, G, G, G},
      {E, E, G, E, E},
      {E, E, G, E, E},
      {E, E, G, E, E},
    };

    init_matrix_t fieldFinal = {
      {G, G, G, G, G},
      {E, E, G, E, E},
      {E, E, G, E, E},
      {E, E, G, E, E},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, G, G, G, G},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, G, G, G, G},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
}

TEST(TetrisModel, GameRunLandscapeNoInterrupt) {
  // will try different shapes
  {
    init_matrix_t fieldInit = {
      {E, E, G, G, G},
      {E, E, E, E, G},
      {E, E, E, E, E},
      {L, L, L, L, E},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, G, G, G},
      {L, L, L, L, G},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, G, E, E, E},
      {E, E, E, L, E},
      {E, E, E, L, E},
      {L, E, L, L, L},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, L, E},
      {E, E, E, L, E},
      {L, G, L, L, L},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {G, G, G, G, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, L},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, G, G, G, L},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {G, G, G, G, G},
      {E, E, G, E, E},
      {E, E, G, E, E},
      {L, E, G, E, L},
    };

    init_matrix_t fieldFinal = {
      {G, G, G, G, G},
      {E, E, G, E, E},
      {E, E, G, E, E},
      {L, E, G, E, L},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, L, G, G, G},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, L, G, G, G},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
}

TEST(TetrisModel, GameRunLandscapeInterrupt) {
  // will try different shapes
  {
    init_matrix_t fieldInit = {
      {E, E, G, G, G},
      {E, E, E, E, G},
      {E, E, E, L, E},
      {L, L, L, L, L},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, G, G, G},
      {E, E, E, L, G},
      {L, L, L, L, L},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, G, E, E, E},
      {E, E, E, E, E},
      {E, L, E, E, E},
      {E, L, E, E, E},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, G, E, E, E},
      {E, L, E, E, E},
      {E, L, E, E, E},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {G, G, G, G, G},
      {E, E, L, E, E},
      {E, E, L, E, E},
      {E, E, L, E, E},
    };

    init_matrix_t fieldFinal = {
      {G, G, G, G, G},
      {E, E, L, E, E},
      {E, E, L, E, E},
      {E, E, L, E, E},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {G, G, G, G, G},
      {E, E, G, E, E},
      {E, E, G, E, E},
      {E, E, L, E, E},
    };

    init_matrix_t fieldFinal = {
      {G, G, G, G, G},
      {E, E, G, E, E},
      {E, E, G, E, E},
      {E, E, L, E, E},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
  {
    init_matrix_t fieldInit = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, G, G, G, G},
      {E, E, E, E, L},
    };

    init_matrix_t fieldFinal = {
      {E, E, E, E, E},
      {E, E, E, E, E},
      {G, G, G, G, G},
      {E, E, E, E, L},
    };

    Game game(CreateGameField(fieldInit));
    game.Run();

    EXPECT_TRUE( AreFieldsEqual( CreateGameField(fieldFinal), game.GetField() ) );
  }
}

}