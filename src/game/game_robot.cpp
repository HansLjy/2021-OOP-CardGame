// You can modify the prototypes and update them in game.h.

#include <array>
#include <string>

#include "clockint.h"
#include "card.h"
#include "rule.h"
#include "game.h"

using namespace std;

int score(const CardSet& cards) {
	int sum[15] = { 0 };
	int weight[15] = { 40,15,16,1,2,3,4,5,6,7,8,9,10,11,30};
	int w_order[15] = { 3,4,5,6,7,8,9,10,11,12,13,1,2,0,14 };
	int score=0;
	int board_value = 0;
	int sequence_value = 0;

	for (int i = 1; i < 14; i++) {
		for (int j = 0; j < 4; j++) {
			sum[i] += cards.GetNum(j, i);
		}
	}
	sum[0] = cards.GetNum(4, 0);
	sum[14] = cards.GetNum(4, 14);

	for (int i = 0; i < 15; i++) {
		board_value += sum[i] * weight[i];
	}

	for (int i = 1; i < 15; i++) {
		sequence_value += min(sum[w_order[i - 1]], sum[w_order[i]])*weight[w_order[i]];
	}

	return board_value * 3 / 10 + sequence_value * 7 / 10;
}

#define show_card(card_set) for (int i = 0; i < card_set.GetNumOfCards(); i++) {cerr << card_set.GetCard(i).GetID() << " ";} cerr << endl;

// n 当前已经选择了多少张牌
// last_n 上一轮出了多少张牌
// first 现在从第几张牌开始选
void SearchBest(const Rule& rule, const CardSet& my_card, const Analysis& last, CardSet& to_dealt, int last_n, int n, int first, int &max_score) {
	static CardSet cur_card;
	if (n == 0) {
		cur_card = CardSet(0);
	}
	if (n == last_n) {
		// 可以响应
		if (Analysis(cur_card, rule) > last) {
			show_card(cur_card);
			// 可以出牌
			CardSet whats_left = my_card;
			whats_left.Delete(cur_card);
			int new_score = score(whats_left);
			if (new_score > max_score) {
				to_dealt = cur_card;
			}
		}
		return;
	}
	int num_my_cards = my_card.GetNumOfCards();
	for (int i = first; i < num_my_cards; i++) {
		cur_card.Insert(my_card.GetCard(i));
		SearchBest(rule, my_card, last, to_dealt, last_n, n + 1, i + 1, max_score);
		cur_card.Delete(my_card.GetCard(i));
	}
}

#include <assert.h>

CardSet DouDizhuGame::playout_robot(ci<3> k) const {
	int max_score = 0;
	CardSet result(0);
	show_card(cards[k]);
	SearchBest(r_1v2_wiki, cards[k], last, result, tcards.GetNumOfCards(), 0, 0, max_score);
	show_card(result);
	return result;
}

CardSet SirenDouDizhuGame::playout_robot(ci<4> k) const {
	int max_score = 0;
	CardSet result(0);
	SearchBest(r_1v3, cards[k], last, result, tcards.GetNumOfCards(), 0, 0, max_score);
	return result;
}

CardSet ShuangkouGame::playout_robot(ci<4> k) const {
	int max_score = 0;
	CardSet result(0);
	SearchBest(r_2v2, cards[k], last, result, tcards.GetNumOfCards(), 0, 0, max_score);
	return result;
}

int DouDizhuGame::bid_robot(ci<3> k) const {
	return 0;
}

int SirenDouDizhuGame::bid_robot(ci<4> k) const {
	return 0;
}
