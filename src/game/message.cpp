#include <string>
#include <array>

#include "clockint.h"
#include "card.h"
#include "message.h"

using namespace std;

Message::Message(MsgType t):
    type(t),
    isr(false),
    spar(string(8, 0)),
    scard(string(54, 0)),
    ext(string())
{}
Message::Message(const string &s):
    type((MsgType)s[0]),
    isr((bool)s[1]),
    spar(string(s, 2, 8)),
    scard(string(s, 10, 54)),
    ext(string(s, 64))
{}
MsgType Message::GetType() const {
    return type;
}
bool Message::IsRequest() const {
    return isr;
}
int Message::GetPar(int k) const {
    if (k < 0 || k >= 8) {
        throw "int Message::GetPar(int k) const - invalid index";
    }
    return (int)spar[k];
}
int Message::GetPlayer() const {
    return GetPar(7);
}
int Message::GetTime() const {
    return GetPar(6);
}
CardSet Message::GetCards() const {
    return CardSet(scard);
}
string Message::GetExtension() const {
    return ext;
}
const string &Message::GetExtensionR() const {
    return ext;
}
void Message::SetType(MsgType t) {
    type = t;
}
void Message::SetIsRequest(bool b) {
    isr = b;
}
void Message::SetPar(int k, int v) {
    if (k < 0 || k >= 8) {
        throw "void Message::SetPar(int k, int v) - invalid index";
    }
    if ((spar[k] = (char)v) != v) {
        throw "void Message::SetPar(int k, int v) - invalid value";
    }
}
void Message::SetPlayer(int p) {
    SetPar(7, p);
}
void Message::SetTime(int t) {
    SetPar(6, t);
}
void Message::SetCards(const CardSet &s) {
    scard = s.String();
}
void Message::SetExtension(const string &s) {
    ext = s;
}
string Message::String() const {
    return string(1, (char)type) + string(1, (char)isr) + spar + scard + ext;
}

template <int np> MsgSeries<np>::MsgSeries(const Message &m) {
    this->fill(m);
}
template <int np> void MsgSeries<np>::SetPar(int k, array<int, np> a) {
    for (int i = 0; i < np; i++) {
        this->at(i).SetPar(k, a[i]);
    }
}
template <int np> void MsgSeries<np>::SetPar(int k, ci<np> v) {
    for (int i = 0; i < np; i++, v--) {
        this->at(i).SetPar(k, v);
    }
}
template <int np> void MsgSeries<np>::SetPars(int k, array<int, np> a) {
    for (int i = 0; i < np; i++) {
        ci<np> i0 = i;
        for (int j = k; j < k + np; j++, i0--) {
            this->at(i).SetPar(j, a[i0]);
        }
    }
}
template <int np> void MsgSeries<np>::SetPlayer(ci<np> v) {
    SetPar(7, v);
}
template <int np> void MsgSeries<np>::SetCards(const array<CardSet, np> &a) {
    for (int i = 0; i < np; i++) {
        this->at(i).SetCards(a[i]);
    }
}

// test code, expected all 1's

// #include <iostream>
// #include "clockint.cpp"
// #include "card.cpp"
// int main() {
//     Message m;
//     m.SetType(m_playout);
//     m.SetIsRequest(false);
//     m.SetPar(0, 13);
//     m.SetPar(1, 5);
//     m.SetPlayer(2);
//     m.SetTime(20);
//     CardSet s;
//     for (int i = 3; i <= 8; i++) s.Insert(Card(i));
//     m.SetCards(s);
//     m.SetExtension(string("abc"));
//     m = Message(m.String());
//     cout
//         << (m.GetType() == m_playout)
//         << (m.IsRequest() == false)
//         << (m.GetPar() == 13)
//         << (m.GetPar(1) == 5)
//         << (m.GetPlayer() == 2)
//         << (m.GetTime() == 20)
//         << (m.GetCards() == s)
//         << (m.GetExtension() == string("abc"))
//     ;
//     MsgSeries<4> ms(m);
//     cout << (ms[2].String() == m.String());
//     ms.SetPar(0, array<int, 4>{5, 6, 7, 8});
//     cout << (
//         ms[0].GetPar() == 5 &&
//         ms[1].GetPar() == 6 &&
//         ms[2].GetPar() == 7 &&
//         ms[3].GetPar() == 8
//     );
//     ms.SetPar(0, ci<4>(2));
//     cout << (
//         ms[0].GetPar() == 2 &&
//         ms[1].GetPar() == 1 &&
//         ms[2].GetPar() == 0 &&
//         ms[3].GetPar() == 3
//     );
//     ms.SetPlayer(ci<4>(0));
//     cout << (
//         ms[0].GetPlayer() == 0 &&
//         ms[1].GetPlayer() == 3 &&
//         ms[2].GetPlayer() == 2 &&
//         ms[3].GetPlayer() == 1
//     );
//     CardSet t, u, v;
//     for (int i = 5; i <= 9; i++) t.Insert(Card(i));
//     for (int i = 4; i <= 13; i++) u.Insert(Card(i));
//     for (int i = 2; i <= 3; i++) v.Insert(Card(i));
//     ms.SetCards(array<CardSet, 4>{s, t, u, v});
//     cout << (
//         ms[0].GetCards() == s &&
//         ms[1].GetCards() == t &&
//         ms[2].GetCards() == u &&
//         ms[3].GetCards() == v
//     );
//     return 0;
// }
