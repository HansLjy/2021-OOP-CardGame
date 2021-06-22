// ConnectBase.h
#ifndef _CONNECT_BASE_H
#define _CONNECT_BASE_H
// #include "game.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ConnException.h"
#include <WinSock2.h>
#include <process.h>
#include <iostream>
#include <array>

#include "package.h"

using std::string;
using std::array;
#define rec_server (-1)

enum game_type {
    sirendoudizhu,
    shuangkou,
    sanrendoudizhu
};

class ConnectBase{
     private:
     protected:
         static const int BUF_SIZE=1024;
     public:
         //static void ErrorHandling(const char* message);
         //static int read_msg(SOCKET s,GameMessage& msg);
         //static char* read_buf(SOCKET s,void* dst,char* buf,char* cur_read,int buf_size,int max_size);
};

#endif