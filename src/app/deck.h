#pragma once
#include "game.h"
#include "wx/bitmap.h"

const int kMaxCards = 30;
const int kCardHeight = 50;
const int kCardWidth = 50;
const int kDeltaX = 10;
const int kDeltaY = 10;

enum CardOrientation {
	kLeft, kRight, kUp, kDown
};

enum CardFace {
	kFaceUp, kFaceDown
};

class Deck {
	static bool initialized;
	static wxBitmap *card_pics[60];


	CardOrientation orientation;
	CardFace face;

public:
	CardSet cards;
	Deck (CardOrientation orient = kDown, CardFace face = kFaceDown);
	Deck (const CardSet& card_set, CardOrientation orient, CardFace face);

	/**
	 * @brief 从左上角坐标 (x, y) 处开始绘制卡牌图片
	 */
	void Draw(wxDC &dc, int x, int y);
};