// GameMessage.h

#include "ConnectBase.h"

class GameMessage{
    private:
        int state;
        int card_owner_index;
        CardSet* LPcards;
    public:
        /**
         * @brief 设定信息
         * @param state 信息状态
         * @param card_owner_index 卡组的主人编号，0为无主；只在state=game_send_you_card时有效
         * @param LPcards 卡组指针；只在state=game_send_you_card时有效
         * @note 玩家若在游戏开始前被删除，其后编号顺次左移；游戏开始后，其余玩家编号不变
         */ 
        void SetGameMessage(int state,CardSet* LPcards=nullptr,int card_owner_index=0);
        int get_state();
        int get_card_owner_index();
        const CardSet& get_cards();
};

