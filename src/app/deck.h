#pragma once
#include "game.h"
#include "wx/bitmap.h"
#include "wx/dcclient.h"
#include "global.h"

const int k_card_length = 50;
const int k_card_height = 73;
const int kMaxCards = 30;
const int k_delta_x = 10;
const int k_delta_y = 10;

const wxSize k_card_size(k_card_length, k_card_height);
const wxPoint k_down_deck_pos(k_card_length * 2, k_window_height - k_card_height);
const wxPoint k_left_deck_pos(0, k_card_height * 2);
const wxPoint k_right_deck_pos(k_window_length - k_card_length, k_card_height * 2);
const wxPoint k_up_deck_pos(k_card_length * 2, 0);

enum CardOrientation {
	kLeft, kRight, kUp, kDown
};

enum CardFace {
	kFaceUp, kFaceDown
};

class Deck {
	static bool initialized;
	static wxBitmap *card_pics[60];

public:
	CardSet cards;
	Deck () = default;
	Deck (const CardSet& card_set);

	/**
	 * @brief Draw card from position (x, y) (upper left corner)
	 */
	void Draw(wxDC &dc, int x, int y, CardFace face, CardOrientation orientation);
};

class DeckPanel : public wxPanel {
	wxClientDC dc;
	CardFace face;
	CardOrientation orientation;

	wxWindow *p_parent;
	Deck deck;

	void OnPaint();
	void OnClick();

public:
	DeckPanel () = delete;
	DeckPanel(wxWindow *p_parent, CardFace face, CardOrientation orient);

	void SetDeck(const CardSet& card_set);
	void render(wxPaintEvent & evt);

	DECLARE_EVENT_TABLE();
};