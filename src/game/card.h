#pragma once

#include <string>
using std::string;

const int heart = 0;
const int diamond = 1;
const int club = 2;
const int spade = 3;
const int joker = 4;
const int R = 0; // red joker
const int A = 1;
const int J = 11;
const int Q = 12;
const int K = 13;
const int B = 14; // black joker

class Card {
    int id;
    // Each card is mapped to an integer in [0, 54), called its ID.
    // Do not care about the mapping rule when using the class.
    // Please use ID only for traverals. Otherwise use suit & rank.
public:
	Card() = default;
    Card(int ID); // returns a card of the specified ID, or throws "invalid_card_ID"
    Card(int suit, int rank); // returns a card of the specified suit & rank, or throws "invalid_suit" or "invalid_rank"
    int GetID() const; // returns the card's ID
    int GetSuit() const; // returns the card's suit
    int GetRank() const; // returns the card's rank
};

class CardSet {
    char num[54];
    int noc;
public:
    CardSet(int n = 0); // returns a set of n full decks, containing 54n cards, or throws "invalid_number_of_decks"
    CardSet(const string &s); // decodes a string encoded by CardSet::String(), or throws "decoding failure"
    int GetNum(const Card &c) const; // returns the number of c's in the set
    int GetNum(int suit, int rank) const; // returns the number of Card(suit, rank)'s in the set
    int GetNumOfCards() const; // returns the total number of cards in the set
    Card GetCard(int k) const; // returns the kth card in the set sorted with ID (used for traversals), or throws "invalid_index_in_cardset"
    void Insert(const Card &c); // inserts a c into the set, or throws "number_of_cards_overflow"
    void Insert(int suit, int rank); // inserts a Card(suit, rank) into the set, or throws "number_of_cards_overflow"
    void Insert(const CardSet &s); // inserts s into the set, or throws "number_of_cards_overflow"
    void Delete(const Card &c); // deletes a c from the set, or throws "number_of_cards_underflow"
    void Delete(int suit, int rank); // deletes a Card(suit, rank) from the set, or throws "number_of_cards_underflow"
    void Delete(const CardSet &s); // subtracts s from the set, or throws "number_of_cards_underflow"
    CardSet Take(int k); // randomly takes and subtracts k cards from the set, or throws "invalid_number_of_cards"
    string String() const; // encodes the set to a string
};