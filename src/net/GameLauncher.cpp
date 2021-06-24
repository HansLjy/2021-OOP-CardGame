#include "GameLauncher.h"

//void test_game(Server& s);

int GameLauncher::OpenRoom(
	GameType gt, 
	int humans,
	int robots
){
    if (game_ptr) clearGame();
    try {
        setGame();
        return s.OpenRoom(gt, humans, robots);
    }
    catch (...) { return 1; }
}

void GameLauncher::setGame() {
    array<bool, 3> human1_robot0_3;
    array<bool, 4> human1_robot0_4;
    
    int i = 0;
    for (i = 0; i < s.getHumans(); i++) {
        human1_robot0_3[i] = true;
        human1_robot0_4[i] = true;
    }
    for (; i < s.getHumans()+s.getRobots() - 1; i++) {
        human1_robot0_3[i] = false;
        human1_robot0_4[i] = false;
    }
    switch (s.getGameType()) {
    case GameType::Landlords_3:
        human1_robot0_3[i] = false;
        game_ptr = new DouDizhuGame(human1_robot0_3,s);
        break;
    case GameType::Landlords_4:
        human1_robot0_4[i] = false;
        game_ptr = new SirenDouDizhuGame(human1_robot0_4,s);
        break;
    case GameType::Doubleclasp:
        human1_robot0_4[i] = false;
        game_ptr = new ShuangkouGame(human1_robot0_4,s);
        break;
    default:
        throw ceBranchEx();
        break;
    }
}

int GameLauncher::StartGame() {
    if (s.getState() != GamePort::GAME_OPEN||s.isError()) {
        return 1;
    }
    s.setState(GamePort::GAME_ON);
    DouDizhuGame* Gddz;
    SirenDouDizhuGame* G4ddz;
    ShuangkouGame* Gsk;
    switch (s.getGameType()) {
    case GameType::Landlords_3:
        Gddz = reinterpret_cast<DouDizhuGame*>(game_ptr);
        Gddz->Play();
        break;
    case GameType::Landlords_4:
        G4ddz = reinterpret_cast<SirenDouDizhuGame*>(game_ptr);
        G4ddz->Play();
        break;
    case GameType::Doubleclasp:
        Gsk = reinterpret_cast<ShuangkouGame*>(game_ptr);
        Gsk->Play();
        break;
    default:
        return 1;
        break;
    }
    s.setState(GamePort::GAME_OPEN);
    return 0;
}

void GameLauncher::clearGame() {
    DouDizhuGame* Gddz;
    SirenDouDizhuGame* G4ddz;
    ShuangkouGame* Gsk;
    switch (s.getGameType()) {
    case GameType::Landlords_3:
        Gddz = reinterpret_cast<DouDizhuGame*>(game_ptr);
        delete Gddz;
        break;
    case GameType::Landlords_4:
        G4ddz = reinterpret_cast<SirenDouDizhuGame*>(game_ptr);
        delete G4ddz;
        break;
    case GameType::Doubleclasp:
        Gsk = reinterpret_cast<ShuangkouGame*>(game_ptr);
        delete Gsk;
        break;
    default:
        throw ceBranchEx();
        break;
    }
    game_ptr = nullptr;
}

GameLauncher::~GameLauncher() {
    if (game_ptr)clearGame();
}

//int Server::StartGame() { // branch error
//    state = GAME_ON;
//    DouDizhuGame* Gddz;
//    SirenDouDizhuGame* G4ddz;
//    ShuangkouGame* Gsk;
//    switch (game_t) {
//    case sanrendoudizhu:
//        Gddz = reinterpret_cast<DouDizhuGame*>(game_ptr);
//        Gddz->Play();
//        break;
//    case sirendoudizhu:
//        G4ddz = reinterpret_cast<SirenDouDizhuGame*>(game_ptr);
//        G4ddz->Play();
//        break;
//    case shuangkou:
//        Gsk = reinterpret_cast<ShuangkouGame*>(game_ptr);
//        Gsk->Play();
//        break;
//    default:
//        throw ceBranchEx();
//        break;
//    }
//    state = GAME_OPEN;
//    return 0;
//}

//void Server::setGame() { // branch error
//    array<bool, 3> human1_robot0_3;
//    array<bool, 4> human1_robot0_4;
//
//    int i = 0;
//    for (i = 0; i < humans; i++) {
//        human1_robot0_3[i] = true;
//        human1_robot0_4[i] = true;
//    }
//    for (; i < humans + robots - 1; i++) {
//        human1_robot0_3[i] = false;
//        human1_robot0_4[i] = false;
//    }
//    switch (game_t) {
//    case sanrendoudizhu:
//        human1_robot0_3[i] = false;
//        game_ptr = new DouDizhuGame(human1_robot0_3, *this);
//        break;
//    case sirendoudizhu:
//        human1_robot0_4[i] = false;
//        game_ptr = new SirenDouDizhuGame(human1_robot0_4, *this);
//        break;
//    case shuangkou:
//        human1_robot0_4[i] = false;
//        game_ptr = new ShuangkouGame(human1_robot0_4, *this);
//        break;
//    default:
//        throw ceBranchEx();
//        break;
//    }
//}

//int Server::CloseRoom() {
//    if (state == GAME_OVER) return 0;
//    state = GAME_OVER;
//    // tell client to quit
//    closesocket(Member_Sock[0]);
//    WSACloseEvent(Member_Event[0]);
//    num_Members = 0;
//    WSACleanup();
//

//    return 0;
//}

//int GameLauncher::StartGame() {
//	s.setState(GamePort::GAME_ON);
//    test_game(s);
//	s.setState(GamePort::GAME_OPEN);
//    return 0;
//}

//void test_game(Server& s) {
//    Package pkg(Header(0, 0));
//    string input;
//    cout << "game start" << endl;
//    cout << "put your message:\n>>" << endl;
//    cin >> input;
//
//    for (int i = 0; i < 2; i++) {
//        pkg = Package(Header(true, i), input);
//        s.SendGameMsg(pkg);
//        pkg = s.CollectGameMsg(i);
//        if (pkg.GetHeader().IsSuccess()) {
//            cout << pkg.GetData() << endl;
//        }
//        else {
//            cout << "receive error" << endl;
//        }
//    }
//
//    cout << "game over" << endl;
//}