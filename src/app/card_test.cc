// Just a place holder

#include "card.h"

Card::Card(int ID) : id(ID) {}

int Card::GetRank() const {
	static int cnt = 0;
	cnt = (cnt + 1) % 13;
	return cnt;
}

int Card::GetSuit() const {
	static int cnt = 0;
	cnt = (cnt + 1) % 5;
	return cnt;
}

CardSet::CardSet(int k) {}

int CardSet::GetNumOfCards() const {
	return 5;
}

Card CardSet::GetCard(int k) const {
	return Card(0);
}