#pragma once
#include "game.h"

const int kMaxCards = 30;

enum CardOrientation {
	kLeft, kRight, kUp, kDown
};

enum CardFace {
	kFaceUp, kFaceDown
};

class Deck {
	int num_of_cards = 0;
	int cards[30];

	CardOrientation orientation;
	CardFace face;

public:
	Deck () = delete;
	Deck (const CardSet& card_set, CardOrientation orient, CardFace face);

	/**
	 * @brief 从左上角坐标 (x, y) 处开始绘制卡牌图片
	 */
	void Draw(int x, int y);
};