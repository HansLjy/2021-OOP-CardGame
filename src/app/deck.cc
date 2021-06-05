#include "deck.h"
#include "wx/dc.h"
#include "wx/dcclient.h"
#include "global.h"
#include <iostream>

bool Deck::initialized = false;
wxBitmap *Deck::card_pics[60] = {nullptr};

/**
 * @brief Rescale the card image to proper size
 * 
 * @param bitmap bitmap to rescale
 * @param new_size desired size
 * @return wxBitmap* null if bitmap is not valid
 */
wxBitmap *RescaleBitmap (const wxBitmap& bitmap, const wxSize& new_size = k_card_size) {
	if (!bitmap.IsOk()) {
		return nullptr;
	}
	const wxImage image = bitmap.ConvertToImage();
	return new wxBitmap(image.Scale(new_size.GetWidth(), new_size.GetHeight(), wxIMAGE_QUALITY_HIGH));
}

Deck::Deck(const CardSet& card_set)
	: cards(card_set) {
	if (initialized == false) {
		wxString prefix("static/Poke/");
		wxString suffix(".jpg");
		try {
			for (int i = 0; i < 55; i++) {
				wxString infix("");
				infix << i;
				auto new_map = new wxBitmap(prefix + infix + suffix, wxBITMAP_TYPE_JPEG);
				card_pics[i] = RescaleBitmap(*new_map);
				delete new_map;
			}
			initialized = true;
		} catch (...) {
			std::cerr << "Image File Lost!" << std::endl;
		}
	}
}

void Deck::Draw(wxDC &dc, int x, int y, CardFace face, CardOrientation orientation) {
	for (auto &card : cards) {
		std::cout << x << " " << y << std::endl;
		switch (face) {
			case kFaceUp   : dc.DrawBitmap(*card_pics[card], x, y); break;
			case kFaceDown : dc.DrawBitmap(*card_pics[0], x, y); break;
		}
		switch (orientation) {
			case kLeft:
			case kRight:
				y += k_delta_x;
				break;
			case kUp:
			case kDown:
				x += k_delta_y;
				break;
		}
	}
}

BEGIN_EVENT_TABLE(DeckPanel, wxPanel)
	EVT_PAINT(DeckPanel::render)
END_EVENT_TABLE()

DeckPanel::DeckPanel (wxWindow *p_parent, CardFace face, CardOrientation orient)
	: wxPanel(p_parent), p_parent(p_parent), face(face), orientation(orient), dc(this) {
}

void DeckPanel::SetDeck(const CardSet& card_set) {
	deck = Deck(card_set);
}

void DeckPanel::render(wxPaintEvent &event) {
	wxClientDC dc(this);
	int x, y;
	this->GetPosition(&x, &y);	// why use pointer in a c++ lib?
	this->deck.Draw(dc, x, y, face, orientation);
}
