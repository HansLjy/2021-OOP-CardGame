// Server.h
#ifndef _SERVER_H
#define _SERVER_H
#include "ConnectBase.h"
#include "GameMessage.h"

using namespace game_connect;

class Server{
    private:

    public:

    int OpenRoom();
    int CloseRoom();
    int NumPlayersInRoom(); // 目前加入房间的玩家数量

    /**
	 * @brief 踢出玩家
	 * @param player_index 玩家编号从1到房间内现人数
     * @return 暂定默认返回0 
	 * @note 玩家若在游戏开始前被删除，其后编号顺次左移；游戏开始后，其余玩家编号不变
	 */ 
    int KickPlayers(int player_index); // index开始为[1,n],n为玩家数量;只能在游戏开始前调用

    int SendGameInfo(const GameMessage& msg, int sendto_player_index);
    
    /**
	 * @brief 等待客户端输入
	 * @param msg 消息接口
     * @param recvfrom_player_index 发送信息的玩家编号
     * @param microsecond 超时等待时间，若为INFINITY,则将一直等待;为0，立刻返回
     * @return 若超时，返回time_out;成功，返回success;出现错误，返回error; 
	 * @note 
	 */
    int FetchPlayerInfo(GameMessage& msg,int recvfrom_player_index,int microsecond);

    // int CallPlayers();     //广播房间信息,异步IO,调用后立即返回，只需执行一次
    // int StopCallPlayers(); //停止广播房间信息
};
#endif