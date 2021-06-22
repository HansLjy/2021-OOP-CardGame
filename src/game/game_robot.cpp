// You can modify the prototypes and update them in game.h.

#include <array>
#include <string>

#include "clockint.h"
#include "card.h"
#include "rule.h"
#include "game.h"

using namespace std;

template <int np> CardSet WinnerBasedGame<np>::playout_robot(ci<np> k) {}
// or make it pure virtual and implement the robots individually

int DouDizhuGame::bid_robot(ci<3> k) {}

int SirenDouDizhuGame::bid_robot(ci<4> k) {}

template class WinnerBasedGame<3>;
template class WinnerBasedGame<4>;
