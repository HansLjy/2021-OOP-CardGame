// game.h
#ifndef _GAME_H
#define _GAME_H
#include <string>
#include <vector>
#include <iostream>

class Client;
class Server;

#define rec_server (-1)

using std::string;
using std::vector;

class Header {
public:
    Header(bool suc, int rec, int spe = 0);
    bool IsSuccess() const;
    int GetRecipient() const;
    int GetSpecial() const; // 留作备用，提高可继承性[滑稽]
};

class Package {
public:
    Package(const Header &h, const string &d);
    Header GetHeader() const;
    string GetData() const;
};

enum GameType {doudizhu, sirendoudizhu};

class Game {
public:
    Game(GameType t, vector<bool> ishuman, const Server &s);
    // ishuman以逆时针方向按序描述，如1010表示两个人类对坐，1100表示两个人类相邻
    // 建议将AI选手也纳入编号，如1010时两个玩家分别用0、2表示
    GameType GetGameType() const;
    int GetNumOfPlayers() const;
    int GetNumOfHumans() const;
    int Play(); // 只会返回0
    // 开始游戏时，请写Game g = Game(...); g.Play();
};
    
class Player {
    int index;
public:
    Player(int index, const Client &c);
    int GetIndex();
    // 在client代码中，先从server获取分配编号，然后创建Player p = Player(...);
};
#endif
// 帮忙实现以下两个
// void Poet::SendGameMsg(const Package &p) const;
// Package Port::CollectGameMsg(int sender) const;
// 如果和sender连接超时/失败，则认为他已退出，此时请return Package(Header(false, Port的编号), "");
// 如果和sender连接成功（说明他在线，但此时他可能未发），则一直等，直至他发第一个包，返回它（UI上倒计时结束就自动发一个“无操作”消息，所以不会等到死）
// 房主的电脑会同时收到GetRecipient()为-1和0的包，注意过滤

