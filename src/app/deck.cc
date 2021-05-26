#include "deck.h"
#include "wx/dc.h"
#include "wx/dcclient.h"

bool Deck::initialized = false;
wxBitmap *Deck::card_pics[60] = {nullptr};

Deck::Deck(CardOrientation orient, CardFace face) 
	: orientation(orient), face(face) {
	if (initialized == false) {
		wxString prefix("static/Poke/");
		wxString suffix(".jpg");
		for (int i = 0; i < 55; i++) {
			wxString infix("");
			infix << i;
			card_pics[i] = new wxBitmap(prefix + infix + suffix, wxBITMAP_TYPE_JPEG);
		}
		initialized = true;
	}
}

Deck::Deck(const CardSet& card_set, CardOrientation orient, CardFace face)
	: Deck(orient, face) {
	cards = card_set;
}

void Deck::Draw(wxDC &dc, int x, int y) {
	for (auto &card : cards) {
		switch (face) {
			case kFaceUp   : dc.DrawBitmap(*card_pics[card], x, y); break;
			case kFaceDown : dc.DrawBitmap(*card_pics[0], x, y); break;
		}
		switch (orientation) {
			case kLeft:
			case kRight:
				y += kDeltaY;
				break;
			case kUp:
			case kDown:
				x += kDeltaX;
				break;
		}
	}
}