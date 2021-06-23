#ifndef GAME_H
#define GAME_H

#include <array>
#include <string>

#include "Server.h"

#include "clockint.h"
#include "card.h"
#include "rule.h"
#include "message.h"
#include "package.h"
#include "disconnection.h"

const int t_bid = 10, t_playout = 20;

using namespace std;

template <int np> class CardGame {
protected:
    const array<bool, np> ishuman; // The index starts from the room creator and goes counterclockwise.
    Server &server; // through which messages are transmitted
    const CardSet ccards; // complete card set used
    array<int, np> score;
    void notify(ci<np> k, const Message &m) const; // notify the kth player of m
    Message request(ci<np> k) const;
    void broadc(const MsgSeries<np> &ms) const;
    void broadc(const MsgSeries<np> &ms, array<bool, np> a) const; // sends m[i] when a[i]
    void disptext(const string &s) const;
    void dispeffect(const string &s) const; // global effect
    void dispeffect(ci<np> k, const string &s) const; // player effect
    void dispscore() const; // broadcasts everyone's score
    virtual void play() = 0;
public:
    CardGame(array<bool, np> ish, Server &s, const CardSet &c); // returns a card game with "is human" list ish and server s
    void Play();
};
template class CardGame<3>;
template class CardGame<4>;

template <int np> class WinnerBasedGame: public CardGame<np> {
protected:
    const Rule rule;
    int stake;
    CardSet tcards; // cards on the table
    array<CardSet, np> cards; // cards on each player's hand
    int npasses; // number of successive passes
    Analysis last; // analysis of the last non-pass hand
    void deal(array<int, np> noc); // the ith player gets noc[i] cards
    void changestake(int s);
    virtual CardSet playout_robot(ci<np> k);
    void playout(ci<np> k);
    virtual void play() = 0;
public:
    WinnerBasedGame(array<bool, np> ish, Server &s, const CardSet &c, const Rule r);
};
template class WinnerBasedGame<3>;
template class WinnerBasedGame<4>;

class DouDizhuGame: public WinnerBasedGame<3> {
    ci<3> ll; // index of the landlord
    int bid_robot(ci<3> k);
    void play();
public:
    DouDizhuGame(array<bool, 3> ish, Server &s);
};

class SirenDouDizhuGame: public WinnerBasedGame<4> {
    ci<4> ll;
    int bid_robot(ci<4> k);
    void play();
public:
    SirenDouDizhuGame(array<bool, 4> ish, Server &s);
};

class ShuangkouGame: public WinnerBasedGame<4> {
    int nleft; // number of players who still have cards
    void play();
public:
    ShuangkouGame(array<bool, 4> ish, Server &s);
};

#endif
