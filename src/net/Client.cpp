#include "Client.h"
//Client.cpp

Client::Client():serv_Sock(NULL),Port(){

}

const vector<string>& Client::JoinRoom(const char* IP, const string& name, int& gameType){
    if (state != GAME_OVER) return names;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw ceNetEx("WSAStartup() error!");
	serv_Sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_Sock == INVALID_SOCKET)
        throw ceNetEx("socket() error!");

	addr.sin_addr.s_addr = inet_addr(IP);

	if (connect(serv_Sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
        throw ceNetEx("connect() error!");

    GameMessage gm;
    Package pkg(Header(0, 0));
    int loop_flag = true;
    while (loop_flag) {
        switch (read_msg(serv_Sock, gm, pkg)) {
        case MSG_CONN_ACCEPT:
            loop_flag = false;
            state = GAME_OPEN;
            break;
        case MSG_CONN_DENY:
            loop_flag = false;
            closesocket(serv_Sock);
            break;
        case MSG_GAME_TYPE:
            gameType = gm.getGameType();
            break;
        default: break;
        }
    }
    return names;
}

int Client::QuitRoom() {
    if (serv_Sock) {
        SendSignal(MSG_WANT_CLOSE, serv_Sock);
        GameMessage gm;
        Package pkg(Header(0, 0));
        while (read_msg(serv_Sock, gm, pkg) != MSG_GRANT_CLOSE);

        state = GAME_OVER;
        closesocket(serv_Sock);
        WSACleanup();
        return 0;
    }
}

void Client::SendGameMsg(const Package & p) const{
    GameMessage gm;
    gm.setPackage(p);
    SendInfo(gm, serv_Sock);
}

Package Client::CollectGameMsg(int sender){
    GameMessage gm;
    Package pkg(Header(0,0));
    while (read_msg(serv_Sock, gm, pkg)!=MSG_PAKAGE);
    return pkg;
}

//inline int Client::SendPlayerInfo(const GameMessage& msg){
//    SendInfo(msg,serv_Sock);
//}

