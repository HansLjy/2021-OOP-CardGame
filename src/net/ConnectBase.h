// ConnectBase.h
#ifndef _CONNECT_BASE_H
#define _CONNECT_BASE_H
#include "game.h"

namespace game_connect{
    const int message_fetched=0;
    const int no_message=1;
    const int time_out=2;

    const int success=0;
    const int error=-1;

    const int game_on=16;
    const int game_over=17;
    const int game_give_me_card=18;
    const int game_send_you_card=19;
    const int game_quit=20;
}

#endif