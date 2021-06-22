// Server.cpp

#include "Server.h"
#include "game.h"

int Server::StartGame() { // branch error
    state = GAME_ON;
    DouDizhuGame* Gddz;
    SirenDouDizhuGame* G4ddz;
    ShuangkouGame* Gsk;
    switch (game_t) {
    case sanrendoudizhu:
        Gddz = reinterpret_cast<DouDizhuGame*>(game_ptr);
        Gddz->Play();
        break;
    case sirendoudizhu:
        G4ddz = reinterpret_cast<SirenDouDizhuGame*>(game_ptr);
        G4ddz->Play();
        break;
    case shuangkou:
        Gsk = reinterpret_cast<ShuangkouGame*>(game_ptr);
        Gsk->Play();
        break;
    default:
        throw ceBranchEx();
        break;
    }
    state = GAME_OPEN;
    return 0;
}

void Server::setGame() { // branch error
    array<bool,3> human1_robot0_3;
    array<bool, 4> human1_robot0_4;

    int i = 0;
    for (i = 0; i < humans; i++) {
        human1_robot0_3[i] = true;
        human1_robot0_4[i] = true;
    }
    for (; i < humans+robots-1; i++) {
        human1_robot0_3[i] = false;
        human1_robot0_4[i] = false;
    }
    switch (game_t) {
    case sanrendoudizhu:
        human1_robot0_3[i] = false;
        game_ptr = new DouDizhuGame(human1_robot0_3,*this);
        break;
    case sirendoudizhu:
        human1_robot0_4[i] = false;
        game_ptr = new SirenDouDizhuGame(human1_robot0_4, *this);
        break;
    case shuangkou:
        human1_robot0_4[i] = false;
        game_ptr=new ShuangkouGame(human1_robot0_4, *this);
        break;
    default:
        throw ceBranchEx();
        break;
    }
}

void Server::SendGameMsg(const Package& p) const {
    int i = p.GetHeader().GetRecipient();
    GameMessage gm;
    gm.setPackage(p);
    SendInfo(gm, PlayerSortedSock[i]);
}

Package Server::CollectGameMsg(int sender) {
    HANDLE hThread;
    unsigned threadID;
    index_info Info;
    Package pkg(Header(0, rec_server));
    Info.s=this;
    Info.index = sender;

    int microsecond = INFINITE;
    
    hThread=(HANDLE)_beginthreadex(
        NULL,
        0,
        thread_server_BufNotEmpty,
        (void*)&Info,
        0,
        &threadID
    );
    WaitForSingleObject(hThread,(DWORD)microsecond);
    if(!Buf[sender].empty()){
        WaitForSingleObject(Mutex[sender], INFINITE);
        pkg = buffer[sender].front();
        buffer[sender].pop();
        ReleaseMutex(Mutex[sender]);
    }
    return pkg;
}

unsigned WINAPI Server::thread_server_BufNotEmpty(void* arg){
    index_info* pInfo=reinterpret_cast<index_info*>(arg);
    Server* s=pInfo->s;
    int index=pInfo->index;
    if(s){
        while(s->buffer[index].empty());
    }else throw ceNullServer();
}

unsigned WINAPI Server::thread_server_main(void* LPserver){
    Server* s = reinterpret_cast<Server*>(LPserver);
    WSANETWORKEVENTS netEvents;

    int posInfo,startIdx;
    int sigEventIdx;
    int i;

    if(s==nullptr){
        throw ceNullServer();
    }
	else{
        posInfo = 
            WSAWaitForMultipleEvents(
                s->num_Members, 
                s->Member_Event,
                FALSE, WSA_INFINITE, FALSE
            );

        startIdx = posInfo - WSA_WAIT_EVENT_0;

        while(s->state!=GAME_OVER){
            for(i = startIdx; i < s->num_Members; i++){
                sigEventIdx = 
                    WSAWaitForMultipleEvents(
                        1,&s->Member_Event[i], 
                        TRUE,0, FALSE
                    );

                if ((sigEventIdx == WSA_WAIT_FAILED ||
                     sigEventIdx == WSA_WAIT_TIMEOUT)){
                    continue;
                }
                else{
                    sigEventIdx = i;
                    WSAEnumNetworkEvents(
                        s->Member_Sock[sigEventIdx],
                        s->Member_Event[sigEventIdx],
                        &netEvents
                    );
                    /* 请求连接时 */
                    if (netEvents.lNetworkEvents & FD_ACCEPT){
                        if (netEvents.iErrorCode[FD_ACCEPT_BIT] != 0){
                            throw ceIOError("Accept Error");
                            break;
                        }
                        s->handle_accept();
                    }

                    if (netEvents.lNetworkEvents & FD_READ){
                        if (netEvents.iErrorCode[FD_READ_BIT] != 0){
                            throw ceIOError("Read Error");
                            break;
                        }
                        s->handle_read(sigEventIdx);
                    }

                    /* 断开连接 */
                    if (netEvents.lNetworkEvents & FD_CLOSE){ 
                        if (netEvents.iErrorCode[FD_CLOSE_BIT] != 0){
                            throw ceIOError("Close Error");
                            break;
                        }
                        s->handle_close(sigEventIdx);
                    }
                }
            }
        }
    }

	WSACleanup();
	return 0;
}

int Server::handle_close(int index){
    int i;
    if(state==GAME_ON){
        throw ceStateEx();
    }
    WSACloseEvent(Member_Event[index]);
    closesocket(Member_Sock[index]);
    num_Members--;

    for(i=index;i<num_Members;i++){
        Buf[i]=Buf[i+1];
        Member_Sock[i]=Member_Sock[i+1];
        Member_Event[i]=Member_Event[i+1];
    }

    if (num_Members == 0) {
        //if (num_Players) {
        //    //error
        //}
        CloseRoom();
    }
    return 0;
}

int Server::BufClear(int index){
    queue<Package>empty;
    swap(empty, buffer[index]);
    return 0;
}

int Server::handle_accept(){
    SOCKET hClntSock;
    WSAEVENT clntEvent;
    SOCKADDR_IN clntAddr;
    int clntAdrSize;

    clntAdrSize = sizeof(clntAddr);
    hClntSock = accept(Member_Sock[0], (SOCKADDR*)&clntAddr, &clntAdrSize);

    if(num_Members>=humans+1){
        //GameMessage msg(CONN_DENIED);
        //SendGameInfo(msg,hClntSock);

        //发送拒绝受理
        SendSignal(MSG_CONN_DENY, hClntSock);
        closesocket(hClntSock);
        return 0;
    }

    clntEvent = WSACreateEvent();
    WSAEventSelect(hClntSock, clntEvent, FD_READ | FD_CLOSE);

    Member_Event[num_Members] = clntEvent;
    Member_Sock[num_Members] = hClntSock;
    BufClear(num_Members);
    num_Members++;

    return 0;
}

int Server::handle_read(int index){
    GameMessage msg;
    Package pkg(Header(false, rec_server));
    int i;
    switch(read_msg(Member_Sock[index], msg, pkg)) {
    case MSG_PAKAGE:
        if (state != GAME_ON) {
            throw ceStateEx();
        }
        WaitForSingleObject(Mutex[index - 1], INFINITE);
        buffer[Member_Sock[index]].push(pkg);
        ReleaseMutex(Mutex[index - 1]);
        break;
    case MSG_SEND_NAME:
        if (state != GAME_OPEN) {
            throw ceStateEx();
        }
        PlayerSortedSock[num_Players++] = Member_Sock[index];
        if (num_Players >= humans) {
            for (int i = 0; i < humans; i++) {
                if (PlayerSortedSock[i]) {
                    for (int j = 0; j < humans; j++) {
                        SendName(names[j], PlayerSortedSock[i]);
                    }
                    SendGameType(game_t, PlayerSortedSock[i]);
                    SendSignal(
                        MSG_CONN_ACCEPT, 
                        PlayerSortedSock[i]
                    );
                }
            }
        }
        break;
    case MSG_WANT_CLOSE:
        if (state != GAME_OPEN) {
            throw ceStateEx();
        }
        SendSignal(MSG_GRANT_CLOSE, Member_Sock[index]);
        for (i = 0; i < num_Players; i++) {
            if (Member_Sock[i] == PlayerSortedSock[i])break;
        }
        if (i >= num_Players) { throw ceStateEx(); }
        PlayerSortedSock[i] = 0;
        num_Players--;
        break;
    }
}

int Server:: OpenRoom(game_type gt, int humans, int robots){
    unsigned threadID;
    HANDLE hThread;
	WSADATA wsaData;
    WSAEVENT newEvent;

    if(state!=GAME_OVER) return 0;
    state=GAME_OPEN;

    game_t = gt;
    this->humans = humans;
    this->robots = robots;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		throw ceNetEx("WSAStartup() error!");

    Member_Sock[0]=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Member_Sock[0] == INVALID_SOCKET)
        throw ceNetEx("socket() error!");

	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(Member_Sock[0], (SOCKADDR *)&addr, sizeof(addr)) == SOCKET_ERROR)
        throw ceNetEx("bind() error!");

	if (listen(Member_Sock[0], 5) == SOCKET_ERROR)
        throw ceNetEx("listen() error!");

    newEvent=WSACreateEvent();

    if(WSAEventSelect(Member_Sock[0],newEvent,FD_ACCEPT)==SOCKET_ERROR){
        throw ceNetEx("WSAEventSelect() error");
    }

    Member_Event[0] = newEvent;
    num_Members = 1;
    num_Players = 0;

    // construct game
    setGame();

    hThread=(HANDLE)_beginthreadex(
        NULL,
        0,
        thread_server_main,
        (void*)this,
        0,
        &threadID
    );
    return 0;
}

int Server:: CloseRoom(){
    if(state==GAME_OVER) return 0;
    state=GAME_OVER;
    // tell client to quit
    closesocket(Member_Sock[0]);
    WSACloseEvent(Member_Event[0]);
    num_Members=0;
    WSACleanup();

    DouDizhuGame* Gddz;
    SirenDouDizhuGame* G4ddz;
    ShuangkouGame* Gsk;
    switch (game_t) {
    case sanrendoudizhu:
        Gddz = reinterpret_cast<DouDizhuGame*>(game_ptr);
        delete Gddz;
        break;
    case sirendoudizhu:
        G4ddz = reinterpret_cast<SirenDouDizhuGame*>(game_ptr);
        delete G4ddz;
        break;
    case shuangkou:
        Gsk = reinterpret_cast<ShuangkouGame*>(game_ptr);
        delete Gsk;
        break;
    default:
        throw ceBranchEx();
        break;
    }
    game_ptr = nullptr;
    return 0;
}

Server::Server():num_Members(0),Port(){
    int i;
    game_ptr = NULL;
    for(i=0;i<MAX_PLAYERS;i++){
        Mutex[i]=CreateMutex(NULL,FALSE,NULL);
    }
}

Server::~Server(){
    int i;
    //CloseRoom();
    for(i=0;i<MAX_PLAYERS;i++){
        CloseHandle(Mutex[i]);
    }
}

//inline int Server:: NumPlayersInRoom()const{
//    return num_Members-1;
//}
