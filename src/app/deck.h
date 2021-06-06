#pragma once
#include "game.h"
#include "wx/bitmap.h"
#include "wx/dcclient.h"
#include "global.h"

const int k_card_width = 70;
const int k_card_height = 100;
const int kMaxCards = 30;
const int k_delta_x = 20;
const int k_delta_y = 20;

const wxSize k_card_size(k_card_width, k_card_height);

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
	void Draw(wxDC &dc, int x, int y, CardFace face, CardOrientation orientation, bool is_drawn[]);
};

class DeckPanel : public wxPanel {
	CardFace face;
	CardOrientation orientation;

	wxWindow *p_parent;
	Deck deck;
	bool is_draw[30];

	void OnPaint();
	void OnClick();

public:
	DeckPanel () = delete;
	DeckPanel(wxWindow *p_parent, CardFace face, CardOrientation orient);

	void SetDeck(const CardSet& card_set);
	void Render();
	void OnRender(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);

	DECLARE_EVENT_TABLE();
};