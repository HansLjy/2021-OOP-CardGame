#pragma once

#include "card.h"
using std::string;

enum MsgType {
    start,
    finish,
    drop,
    error,
    print,
    think,
    deal,
    auction,
    setlandlord,
    changebet,
    play,
    deny,
    bomb,
    spring
};

class Message {
    string str;
public:
    Message(const string &s);
    bool IsRequest() const;
    MsgType GetType() const;
    int GetPlayer() const;
    int GetTime() const;
    int GetPar(int i = 0) const;
    CardSet GetCards() const;
    string GetExtension() const;
    void SetPar(int i, int val);
    void SetCards(const CardSet &s);
    string String() const;
};

/*
需要写的伪代码：
Client::Play() {
    while (true) {
        Package p = CollectGameMsg(rec_server);
        if (!p.GetHeader().IsSuccess) {
            显示：服务器挂了，游戏结束
            break;
        }
        Message m = Message(p.GetData());
        MsgType t = m.GetType();
        if (t == start) {
            初始化之类的，可能什么也不用干
        } else if (t == finish) {
            if (m.GetPar() > 0) {
                显示：你赢了！
            } else {
                显示：你输了！
            }
            显示分数列表
            break;
        } else if (t == drop) {
            显示：Name[m.GetPlayer()]掉线，游戏结束
            break;
        } else if (t == error) {
            显示：程序错误，游戏结束（错误信息：m.GetExtension()）
            break;
        } else if (t == print) {
            显示m.GetExtension()
        } else if (t == think) {
            在第m.GetPlayer()个玩家上画个省略号之类的（可以显示倒计时）
        } else if (t == deal) {
            播放发牌动画，显示m.GetCards()，显示每人张数
        } else if (t == auction) {
            if (m.IsRequest) {
                出现不叫、m.GetPar(1)至m.GetPar(2)叫分按钮
                OnPress {
                    m.SetPar(按钮值);
                    SendGameMsg(Package(Header(true, rec_server)), m.String());
                }
                倒计时m.GetTime()秒，超时则发送0（不叫）
            } else {
                第m.GetPlayer()个玩家发出气泡“x分”
            }
        } else if (t == changbet) {
            更新底分
        } else if (t == setlandlord) {
            m.GetPlayer()获得地主标识
            显示底牌，更新地主牌数
        } else if (t == play) {
            if (m.IsRequest) {
                CardSet s = CardSet();
                OnPress card: s.Insert(点的牌) 或 s.Delete(选的牌)
                OnPress botton: m.SetCards(s); SendGameMsg(...);
                倒计时m.GetTime()秒，超时则发送空集（pass）
            } else {
                显示某人出了某牌
            }
        } else if (t == deny) {
            显示：非法出牌
            （倒计时不停）
        } else if (t == bomb) {
            播放炸弹动画
        } else if (t == spring) {
            播放春天动画
        }
    }
}
*/
