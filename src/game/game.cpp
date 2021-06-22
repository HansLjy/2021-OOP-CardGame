// This file has not been logically tested and may contain tons of bugs.

#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <array>
#include <string>

#include "clockint.h"
#include "card.h"
#include "rule.h"
#include "message.h"
#include "package.h"
#include "port.h"
#include "disconnection.h"
#include "game.h"

using namespace std;

template <int np> void CardGame<np>::notify(ci<np> k, const Message &m) const {
    if (ishuman[k]) {
        server.SendGameMsg(Package(Header(true, (int)k), m.String()));
    }
}
template <int np> Message CardGame<np>::request(ci<np> k) const {
    Package p = server.CollectGameMsg((int)k);
    if (!p.GetHeader().IsSuccess()) {
        throw Disconn<np>(k);
    }
    Message m(p.GetData());
    m.SetIsRequest(false);
    return m;
}
template <int np> void CardGame<np>::broadc(const MsgSeries<np> &ms) const {
    for (int i = 0; i < np; i++) {
        notify(i, ms[i]);
    }
}
template <int np> void CardGame<np>::broadc(const MsgSeries<np> &ms, array<bool, np> a) const {
    for (int i = 0; i < np; i++) {
        if (a[i]) {
            notify(i, ms[i]);
        }
    }
}
template <int np> void CardGame<np>::disptext(const string &s) const {
    Message m(m_disptext);
    m.SetExtension(s);
    broadc(m);
}
template <int np> void CardGame<np>::dispeffect(const string &s) const {
    Message m(m_dispeffect);
    m.SetPlayer(np);
    m.SetExtension(s);
    broadc(m);
}
template <int np> void CardGame<np>::dispeffect(ci<np> k, const string &s) const {
    Message m(m_dispeffect);
    m.SetExtension(s);
    MsgSeries<np> ms(m);
    ms.SetPlayer(k);
    broadc(ms);
}
template <int np> void CardGame<np>::dispscore() const {
    MsgSeries<np> ms(Message(m_dispscore));
    ms.SetPars(0, score);
    broadc(ms);
}
template <int np> CardGame<np>::CardGame(array<bool, np> ish, const Server &s, const CardSet &c):
    ishuman(ish), server(s), ccards(c)
{
    srand(time(0));
}
template <int np> void CardGame<np>::Play() {
    broadc(Message(m_start));
    try {
        play();
        dispscore();
    } catch (Disconn<np> &d) {
        MsgSeries<np> ms(Message(m_box));
        ms.SetPlayer(d.GetIndex());
        for (int i = 0; i < np; i++) {
            ms[i].SetExtension("玩家“$" + to_string(ms[i].GetPlayer()) + "”掉线，游戏结束。");
        }
        broadc(ms);
    }
    Sleep(1000);
    broadc(Message(m_end));
}

template <int np> void WinnerBasedGame<np>::deal(array<int, np> noc) {
    tcards = this->ccards;
    for (int i = 0; i < np; i++) {
        cards[i] = tcards.Take(noc[i]);
    }
    Message m(m_deal);
    m.SetPar(np, tcards.GetNumOfCards());
    MsgSeries<np> ms(m);
    ms.SetPars(0, noc);
    ms.SetCards(cards);
    this->broadc(ms);
}
template <int np> void WinnerBasedGame<np>::changestake(int s) {
    Message m(m_changestake);
    m.SetPar(0, stake = s);
    this->broadc(m);
}
template <int np> void WinnerBasedGame<np>::playout(ci<np> k) {
    Message m(m_playout);
    CardSet c;
    if (this->ishuman[k]) {
        m.SetPar(0, (int)(npasses < np - 1));
        m.SetTime(t_playout);
        m.SetPlayer((int)k);
        this->notify(k, m);
        while (true) {
            m = this->request(k);
            c = m.GetCards();
            if (Analysis(c) > last) {
                break;
            }
            this->notify(k, Message(m_deny));
        }
    } else {
        c = playout_robot(k);
    }
    if (c) {
        tcards.Insert(c);
        cards[k].Delete(c);
        npasses = 0;
        last = Analysis(c);
        if (last.GetFlag() > 4) {
            this->dispeffect(k, "bomb");
        } else if (int l = last.GetLen() > 1) {
            if (l >= 3) {
                this->dispeffect(k, "airplane");
            } else {
                this->dispeffect(k, "sequence");
            }
        }
    } else if(++npasses == np - 1) {
        last = Analysis();
    }
    m.SetIsRequest(false);
    m.SetPar(0, cards[k].GetNumOfCards());
    this->broadc(m);
}
template <int np> WinnerBasedGame<np>::WinnerBasedGame(
    array<bool, np> ish, const Server &s, const CardSet &c, const Rule r
):
    CardGame<np>(ish, s, c), rule(r)
{}

void DouDizhuGame::play() {
    changestake(0);
    last = Analysis();
    npasses = 0;
    Message m(m_bid);
    m.SetPar(2, 3);
    m.SetTime(t_bid);
    while (!stake) {
        deal(array<int, 3>{17, 17, 17});
        for (ci<3> i = rand(); npasses < 3; i++) {
            m.SetPar(1, stake + 1);
            m.SetPlayer((int)i);
            int s;
            if (ishuman[i]) {
                m.SetIsRequest(true);
                notify(i, m);
                m = request(i);
                s = m.GetPar();
            } else {
                s = bid_robot(i);
                m.SetPar(0, s);
            }
            broadc(m);
            if (s) {
                changestake(s);
                if (s == 3) {
                    ll = i;
                    break;
                }
                npasses = 0;
            } else if (++npasses == 2 && stake) {
                ll = i + 1;
                break;
            }
        }
    }
    m.SetType(m_setlandlord);
    m.SetPar(0, 20);
    m.SetPlayer((int)ll);
    m.SetCards(tcards);
    broadc(m);
    cards[ll].Insert(tcards);
    tcards = CardSet();
    npasses = 2;
    int sprref = 20;
    for (ci<3> i = ll; ; i++) {
        playout(i);
        if (sprref == 20) {
            sprref = cards[ll].GetNumOfCards();
        }
        if (last.GetFlag() >= 4) {
            changestake(2 * stake);
        }
        if (!cards[i]) {
            if (
                i == ll &&
                cards[i + 1].GetNumOfCards() == 17 &&
                cards[i + 2].GetNumOfCards() == 17
            ||
                i != ll &&
                cards[ll].GetNumOfCards() == sprref
            ) {
                dispeffect("spring");
                changestake(2 * stake);
            }
            int sgn = i == ll? 1: -1;
            score[ll] = 2 * sgn  * stake;
            for (int j = 1; j < 3; j++) {
                score[ll + j] = -sgn  * stake;
            }
            break;
        }
    }
}
DouDizhuGame::DouDizhuGame(array<bool, 3> ish, const Server &s):
    WinnerBasedGame<3>(ish, s, CardSet(1), r_1v2_wiki)
{}

void SirenDouDizhuGame::play() {
    changestake(0);
    last = Analysis();
    Message m(m_bid);
    m.SetPar(2, 3);
    m.SetTime(t_bid);
    while (!stake) {
        deal(array<int, 4>{25, 25, 25, 25});
        ci<4> i = rand();
        for (int j = 0; j < 4; j++, i++) {
            m.SetPar(1, stake + 1);
            m.SetPlayer((int)i);
            int s;
            if (ishuman[i]) {
                m.SetIsRequest(true);
                notify(i, m);
                m = request(i);
                s = m.GetPar();
            } else {
                s = bid_robot(i);
                m.SetPar(0, s);
            }
            broadc(m);
            if (s) {
                changestake(s);
                ll = i;
                if (s == 3) {
                    break;
                }
            }
        }
    }
    m.SetType(m_setlandlord);
    m.SetPar(0, 33);
    m.SetPlayer((int)ll);
    m.SetCards(tcards);
    broadc(m);
    cards[ll].Insert(tcards);
    tcards = CardSet();
    npasses = 3;
    for (ci<4> i = ll; ; i++) {
        playout(i);
        if (last.GetFlag() >= 6) {
            changestake(2 * stake);
        }
        if (!cards[i]) {
            int sgn = i == ll? 1: -1;
            score[ll] = 3 * sgn * stake;
            for (int j = 1; j < 4; j++) {
                score[ll + j] = -sgn * stake;
            }
            break;
        }
    }
}
SirenDouDizhuGame::SirenDouDizhuGame(array<bool, 4> ish, const Server &s):
    WinnerBasedGame<4>(ish, s, CardSet(2), r_1v3)
{}

void ShuangkouGame::play() {
    changestake(1);
    last = Analysis();
    deal(array<int, 4>{27, 27, 27, 27});
    nleft = 4;
    score.fill(-3);
    npasses = 3;
    for (ci<4> i = rand(); ; i++) {
        if (cards[i]) {
            playout(i);
            int s = last.GetFlag();
            if (s == nuke) {
                s = 5;
            } else {
                s -= 3;
            }
            if (s > stake) {
                changestake(s);
            }
            if (!cards[i]) {
                score[i] += nleft;
                score[i + 2] += nleft;
                if (!cards[i + 2]) {
                    score[i + 1] = -score[i];
                    score[i + 3] = -score[i];
                    for (int i = 0; i < 4; i++) {
                        score[i] *= stake;
                    }
                    break;
                }
            }
        } else if (++npasses == 3) {
            last = Analysis();
        } else if (npasses == 4) {
            i++;
        }
    }
}
ShuangkouGame::ShuangkouGame(array<bool, 4> ish, const Server &s):
    WinnerBasedGame<4>(ish, s, CardSet(2), r_2v2)
{}

// test code

// #include <iostream>
// #include "clockint.cpp"
// #include "card.cpp"
// #include "rule.cpp"
// #include "message.cpp"
// #include "package.cpp"
// #include "disconnection.cpp"
// #include "game_robot.cpp"
// using namespace std;
// void Port::SendGameMsg(Package const&) const {}
// Package Port::CollectGameMsg(int) const {}
// int main() {
//     cout << "No compile-time error";
//     return 0;
// }
