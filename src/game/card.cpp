#include <stdlib.h>
#include <string>

#include "card.h"

using namespace std;

Card::Card(int i): id(i) {
    if (i < 0 || i > 53) {
        throw "Card::Card(int i) - invalid card ID";
    }
}
Card::Card(int s, int r) {
    if (s < 0 || s > 4) {
        throw "Card::Card(int s, int r) - invalid suit";
    }
    if (s == 4) {
        if (r && r != 14) {
            throw "Card::Card(int s, int r) - invalid rank";
        }
        id = r? 53: 0;
    } else {
        if (r < 1 || r > 13) {
            throw "Card::Card(int s, int r) - invalid rank";
        }
        id = 13 * s + r;
    }
}
int Card::GetID() const {
    return id;
}
int Card::GetSuit() const {
    if (id == 0 || id == 53) {
        return joker;
    }
    return (id - 1) / 13;
}
int Card::GetRank() const {
    int r = id;
    for (int i = 0; i < 3; i++) {
        if (r > 13) {
            r -= 13;
        }
    }
    return r;
}

CardSet::CardSet(int n): noc(54 * n) {
    if (n < 0 || n > 127) {
        throw "CardSet::CardSet(int n) - invalid number of decks";
    }
    for (int i = 0; i < 54; i++) {
        num[i] = (char)n;
    }
}
CardSet::CardSet(const string &s) {
    if (s.size() != 54) {
        throw "CardSet::CardSet(const string &s) - invalid length";
    }
    noc = 0;
    for (int i = 0; i < 54; i++) {
        if ((num[i] = s[i]) < 0) {
            throw "CardSet::CardSet(const string &s) - invalid value";
        }
        noc += s[i];
    }
}
int CardSet::GetNum(const Card &c) const {
    return (int)num[c.GetID()];
}
int CardSet::GetNum(int s, int r) const {
    return GetNum(Card(s, r));
}
int CardSet::GetNumOfCards() const {
    return noc;
}
Card CardSet::GetCard(int k) const {
    if (k < 0 || k >= noc) {
        throw "Card CardSet::GetCard(int k) const - invalid index";
    }
    for (int i = 0; i < 54; i++) {
        k -= num[i];
        if (k < 0) {
            return Card(i);
        }
    }
}
void CardSet::Insert(const Card &c) {
    if(num[c.GetID()]++ < 0) {
        throw "void CardSet::Insert(const Card &c) - overflow";
    }
    noc++;
}
void CardSet::Insert(int s, int r) {
    Insert(Card(s, r));
}
void CardSet::Insert(const CardSet &s) {
    for (int i = 0; i < 54; i++) {
        if ((num[i] += s.GetNum(i)) < 0) {
            throw "void CardSet::Insert(const CardSet &s) - overflow";
        }
    }
    noc += s.GetNumOfCards();
}
void CardSet::Delete(const Card &c) {
    if (num[c.GetID()]-- < 0) {
        throw "void CardSet::Delete(const Card &c) - underflow";
    }
    noc--;
}
void CardSet::Delete(int s, int r) {
    Delete(Card(s, r));
}
void CardSet::Delete(const CardSet &s) {
    for (int i = 0; i < 54; i++) {
        if ((num[i] -= s.GetNum(i)) < 0) {
            throw "void CardSet::Delete(const CardSet &s) - underflow";
        }
    }
    noc -= s.GetNumOfCards();
}
CardSet CardSet::Take(int k) {
    if (k < 0 || k > noc) {
        throw "CardSet CardSet::Take(int k) - invalid number of cards";
    }
    bool a[noc];
    if (2 * k < noc) {
        for (int i = 0; i < noc; i++) {
            a[i] = false;
        }
        while (k) {
            int r = rand() % noc;
            if (!a[r]) {
                a[r] = true;
                k--;
            }
        }
    } else {
        for (int i = 0; i < noc; i++) {
            a[i] = true;
        }
        while (k < noc) {
            int r = rand() % noc;
            if (a[r]) {
                a[r] = false;
                k++;
            }
        }
    }
    CardSet s;
    for (int i = 0; i < noc; i++) {
        if (a[i]) {
            s.Insert(GetCard(i));
        }
    }
    Delete(s);
    return s;
}
string CardSet::String() const {
    return string(num, 54);
}
CardSet::operator bool() const {
    return (bool)noc;
}
CardSet CardSet::operator+(const Card &c) const {
    CardSet t = *this;
    t.Insert(c);
    return t;
}
CardSet CardSet::operator+(const CardSet &s) const {
    CardSet t = *this;
    t.Insert(s);
    return t;
}
CardSet CardSet::operator-(const Card &c) const {
    CardSet t = *this;
    t.Delete(c);
    return t;
}
CardSet CardSet::operator-(const CardSet &s) const {
    CardSet t = *this;
    t.Delete(s);
    return t;
}
bool CardSet::operator==(const CardSet &s) const {
    if (noc != s.noc) {
        return false;
    }
    for (int i = 0; i < 54; i++) {
        if (num[i] != s.num[i]) {
            return false;
        }
    }
    return true;
}
bool CardSet::operator!=(const CardSet &s) const {
    return !operator==(s);
}

/*
    test code
    expected:
    1st line all 1's
    2nd line 15 1's
    3rd line 35 1's
*/

// #include <iostream>
// #include <time.h>
// int main() {
//     Card c(0);
//     cout << (c.GetID() == 0 && c.GetSuit() == joker && c.GetRank() == R);
//     c = Card(5);
//     cout << (c.GetID() == 5 && c.GetSuit() == heart && c.GetRank() == 5);
//     c = Card(38);
//     cout << (c.GetID() == 38 && c.GetSuit() == club && c.GetRank() == Q);
//     c = Card(53);
//     cout << (c.GetID() == 53 && c.GetSuit() == joker && c.GetRank() == B);
//     c = Card(joker, R);
//     cout << (c.GetID() == 0 && c.GetSuit() == joker && c.GetRank() == R);
//     c = Card(heart, K);
//     cout << (c.GetID() == 13 && c.GetSuit() == heart && c.GetRank() == K);
//     c = Card(diamond, A);
//     cout << (c.GetID() == 14 && c.GetSuit() == diamond && c.GetRank() == A);
//     c = Card(club, 10);
//     cout << (c.GetID() == 36 && c.GetSuit() == club && c.GetRank() == 10);
//     c = Card(joker, B);
//     cout << (c.GetID() == 53 && c.GetSuit() == joker && c.GetRank() == B);
//     CardSet s0, s1(1), s2(2);
//     s0.Insert(Card(15));
//     s1.Insert(s0);
//     s1.Delete(Card(39));
//     s2.Delete(s1);
//     cout << (s2.GetNum(53) == 1 && s2.GetNum(diamond, 2) == 0 && s2.GetNum(39) == 2);
//     cout << ((s0 + s1).GetNum(15) == 3 && (s2 - Card(39)).GetNum(39) == 1);
//     s2 = CardSet(s2.String());
//     cout << (s2.GetNum(53) == 1 && s2.GetNum(diamond, 2) == 0 && s2.GetNum(39) == 2 && s2.GetNumOfCards() == 54);
//     cout << (s0 == s0 && !(s0 != s0) && s0 != s1 && !(s0 == s1)) << endl;
//     srand(time(0));
//     CardSet s = CardSet(1).Take(15);
//     for (int i = 0; i < 54; i++) {
//         cout << s.GetNum(i);
//     }
//     cout << endl;
//     s = CardSet(1).Take(35);
//     for (int i = 0; i < 54; i++) {
//         cout << s.GetNum(i);
//     }
//     cout << endl;
//     return 0;
// }
