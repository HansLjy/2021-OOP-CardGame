// Port.h
#ifndef _PORT_H
#define _PORT_H

#include "ConnectBase.h"
#include "GameMessage.h"
#include <queue>
// using namespace game_connect;

enum port_state {
    GAME_ON,
    GAME_OVER,
    GAME_OPEN,
};

class Port:public ConnectBase{
    protected:
        port_state state;
        SOCKADDR_IN addr;
        vector<string>names;
        game_type game_t;

        msg_t read_msg(SOCKET s, GameMessage& gm, Package& pkg);

        static void SendSignal(msg_t sig, SOCKET to);
        static void SendName(const string& name, SOCKET to);
        static void SendGameType(game_type gt, SOCKET to);
        //static char* read_buf(SOCKET s,void* dst,char* buf,char* cur_read,int buf_size,int max_size);
        static void read_buf(SOCKET s, char* dst, int size);
        static int MsgBufClear(queue<GameMessage>& buf);
        static void SendInfo(const GameMessage& gm, SOCKET clntsocket);

    public:
        Port(port_state state = GAME_OVER, USHORT port = 9190);
        virtual void SendGameMsg(const Package& p) const = 0;
        virtual Package CollectGameMsg(int sender=rec_server)=0;
};
#endif