// You can modify the prototypes and update them in game.h.

#include <array>
#include <string>

#include "clockint.h"
#include "card.h"
#include "rule.h"
#include "game.h"

using namespace std;

template <int np> CardSet WinnerBasedGame<np>::playout_robot(ci<np> k) const {}
// or make it pure virtual and implement the robots individually

int DouDizhuGame::bid_robot(ci<3> k) const {}

int SirenDouDizhuGame::bid_robot(ci<4> k) const {}
