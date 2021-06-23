#pragma once
#include "card.h"
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
	kLeft, kRight, kUp, kDown, kCenter
};

enum CardFace {
	kFaceUp, kFaceDown
};

class Deck {
	static bool initialized;		// Whether the card images has been loaded
	static wxBitmap *card_pics[60];	// Pictures of the cards

public:
	CardSet cards;					// The card in this deck
	Deck () = default;
	Deck (const CardSet& card_set);	// Use a cardset to initialize the deck

	// Draw card from position (x, y) (upper left corner)
	void Draw(wxDC &dc, int x, int y, CardFace face, CardOrientation orientation, bool is_drawn[]);
};

class DeckPanel : public wxPanel {
	CardFace face;					// face up or face down
	CardOrientation orientation;	// the position of the cardset

	wxWindow *p_parent;
	Deck deck;						// The deck in the panel
	bool is_draw[60];				// whether the card has been drawn

	void OnPaint();
	void OnClick();

public:
	DeckPanel () = delete;
	DeckPanel(wxWindow *p_parent, CardFace face, CardOrientation orient);

	const CardSet& GetDrawnDeck();
	void SetDeck(const CardSet& card_set);
	void Render();

	void OnRender(wxPaintEvent &event);
	void OnClick(wxMouseEvent &event);

	DECLARE_EVENT_TABLE();
};