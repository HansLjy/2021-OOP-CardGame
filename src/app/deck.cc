#include "deck.h"
#include "wx/dc.h"

Deck::Deck(const CardSet& card_set, CardOrientation orient, CardFace face)
	: num_of_cards (0), orientation(orient), face(face) {
	for (auto &card : card_set) {
		cards[num_of_cards++] = card;
	}
}

void Deck::Draw(int x, int y) {
	
}