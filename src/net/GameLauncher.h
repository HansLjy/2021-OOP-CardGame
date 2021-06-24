#ifndef _GAME_LAUNCHER_H
#define _GAME_LAUNCHER_H
#include "package.h"
#include "Server.h"
#include "ConnectBase.h"
#include "game.h"

class GameLauncher
{
public:
    // return: success if 0 else failure occured
    int OpenRoom(GameType gt, int humans, int robots);

    // return: success if 0 else failure occured
    int StartGame();

    GameLauncher():s(),game_ptr(nullptr){}
    ~GameLauncher();
private:
    void* game_ptr;
    Server s;
    void setGame();
    void clearGame();
};

#endif