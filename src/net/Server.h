//Server.h
#ifndef _SERVER_H
#define _SERVER_H
// #include "GameMessage.h"
#include "Port.h"
//#include "game.h"
#include <queue>

// class Package;
// using namespace game_connect;

class Server:public Port{

public:
    void SendGameMsg(const Package &p) const;
    Package CollectGameMsg(int sender=rec_server);

    int OpenRoom(game_type gt,int humans,int robots);  
    int StartGame();

    Server();
    ~Server();
private:
    //...
    void* game_ptr;
    int humans;
    int robots;

    struct index_info {
        Server* s;
        int index;
    };


    static const int MAX_PLAYERS = 4;
    static const int MSG_BUF_SIZE = 10;

    int num_Members;
    HANDLE Mutex[MAX_PLAYERS];
    queue<Package> buffer[MAX_PLAYERS];

    SOCKET Member_Sock[MAX_PLAYERS + 1];

    int num_Players;
    SOCKET PlayerSortedSock[MAX_PLAYERS];

    WSAEVENT Member_Event[MAX_PLAYERS + 1];
    queue<GameMessage> Buf[MAX_PLAYERS + 1];

    int handle_accept();
    int handle_read(int index);
    int handle_close(int index);
    int BufClear(int index);
    int CloseRoom();
    void setGame();
    // CONNECT_STATE SendGameInfo(const GameMessage& msg, SOCKET clntsocket)const;

    static unsigned WINAPI thread_server_main(void* LPserver);
    static unsigned WINAPI thread_server_BufNotEmpty(void* arg);
};
#endif