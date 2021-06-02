// Client.h
#ifndef _CLIENT_H
#define _CLIENT_H
#include "ConnectBase.h"
#include "GameMessage.h"

using namespace game_connect;


class Client{
    public:

    int JoinRoom(const char* IP,int microtime); // 接收或超时后才返回
    int QuitRoom();

    int FetchGameInfo(GameMessage& msg); //立即返回，若服务器有信息传回返回message_fetched，否则返回no_message
    int SendPlayerInfo(GameMessage& msg);
};

#endif