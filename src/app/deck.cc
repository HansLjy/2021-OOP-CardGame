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

// Ininitialize the cardset pictures
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

int getCardID(const Card& card) {
	switch (card.GetSuit()) {
		case club:
			return card.GetRank();
		case diamond:
			return 13 + card.GetRank();
		case spade:
			return 26 + card.GetRank();
		case heart:
			return 39 + card.GetRank();
		case joker:
			return card.GetRank() == 0 ? 54 : 53;
	}
}

void Deck::Draw(wxDC &dc, int x, int y, CardFace face, CardOrientation orientation, bool is_drawn[]) {
	int n = cards.GetNumOfCards();
	for (int i = 0; i < n; i++) {
		auto card = cards.GetCard(i);
		int draw_y = y;
		if (is_drawn[i] && orientation == kDown) {
			draw_y -= k_delta_y;
		}
		switch (face) {
			case kFaceUp   :
				dc.DrawBitmap(*card_pics[getCardID(card)], x, draw_y);
				break;
			case kFaceDown :
				dc.DrawBitmap(*card_pics[0], x, draw_y);
				break;
		}
		switch (orientation) {
			case kLeft:
			case kRight:
				y += k_delta_x;
				break;
			case kUp:
			case kDown:
			case kCenter:
				x += k_delta_y;
				break;
		}
	}
}

BEGIN_EVENT_TABLE(DeckPanel, wxPanel)
	EVT_PAINT(DeckPanel::OnRender)
	EVT_LEFT_UP(DeckPanel::OnClick)
END_EVENT_TABLE()

DeckPanel::DeckPanel (wxWindow *p_parent, CardFace face, CardOrientation orient)
	: wxPanel(p_parent), p_parent(p_parent), face(face), orientation(orient) {
}

const CardSet& DeckPanel::GetDrawnDeck() {
	CardSet cards = deck.cards, result(0);
	int n = cards.GetNumOfCards();
	for (int i = 0; i < n; i++) {
		if (is_draw[i]) {
			result.Insert(cards.GetCard(i));
		}
	}
}

void DeckPanel::SetDeck(const CardSet& card_set) {
	deck = Deck(card_set);
}

void DeckPanel::Render() {
	wxClientDC dc(this);
	int width, height;
	this->GetClientSize(&width, &height);

	int x, y;	// position of the deck
	switch (orientation) {
		case kUp:
			x = 2 * k_card_width;
			y = 0;
			break;
		case kDown:
			x = 2 * k_card_width;
			y = height - k_card_height;
			break;
		case kLeft:
			x = 0;
			y = 30;
			break;
		case kRight:
			x = width - k_card_width;
			y = 30;
			break;
		case kCenter:
			x = width / 2 - (deck.cards.GetNumOfCards() * k_delta_x + k_card_width) / 2;
			y = height / 2 - k_card_height / 2;
			break;		
	}
	// Draw an invisible rectangle to cover the region
	dc.SetPen(invisible_pen);
	dc.SetBrush(invisible_brush);
	dc.DrawRectangle(wxPoint(0, 0), GetSize());
	deck.Draw(dc, x, y, face, orientation, is_draw);
}

void DeckPanel::OnRender(wxPaintEvent &event) {
	Render();
	event.Skip();
}

void DeckPanel::OnClick(wxMouseEvent &event) {
	int mouse_x = event.GetPosition().x;
	int mouse_y = event.GetPosition().y;
	std::cerr << mouse_x << " " << mouse_y << std::endl;

	if (orientation == kDown) {
		int number_of_cards = deck.cards.GetNumOfCards();
		int x, y;
		GetClientSize(nullptr, &y);
		
		x = 2 * k_card_width;
		y -= k_card_height;
		for (int i = 0; i < number_of_cards; i++) {
			if (x < mouse_x && (x + k_delta_x > mouse_x || (i == number_of_cards - 1 && x + k_card_width > mouse_x))) {
				if (is_draw[i]) {
					if (y - k_delta_y < mouse_y && mouse_y < y - k_delta_y + k_card_height) {
						is_draw[i] = false;
						std::cerr << "Chosen " << i << std::endl;
						break;
					}
				} else {
					if (y < mouse_y && mouse_y < y + k_card_height) {
						is_draw[i] = true;
						std::cerr << "Chosen " << i << std::endl;
						break;
					}
				}
			}
			x += k_delta_x;
		}
		Render();
	}
	event.Skip();
}