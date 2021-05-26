#pragma once
#include <vector>

typedef int Card;
typedef std::vector<Card> CardSet;

enum GameType {kUNO, kPoke};

/**
 * @brief Game 类
 * @note 所有游戏模块都应该继承该类，并覆盖掉全部纯虚函数
 */
class Game {
public:
	// @brief 返回正在进行的游戏类型
	virtual GameType GetGameType() = 0;

	// @brief 返回游戏是否结束
	virtual bool GameOver() = 0;

	/**
	 * @brief 返回游戏的胜利者
	 * @return 玩家编号，编号从 0 开始
	 * @note 如果因为玩家退出导致游戏结束，返回 -1
	 * @note 如果是平局，返回 -2
	 */
	virtual int GameWinner() const = 0;

	// @brief 返回当前玩家数量
	virtual void GetNumOfPlayers() const = 0;

	// @brief 返回当前玩家的编号，编号从 0 开始
	virtual void GetCurrentPlayer() const = 0;

	// @brief 返回当前玩家是否是人类
	virtual bool IsHuman() const = 0;

	/**
	 * @brief 查询玩家手牌数量
	 * @param id 带查询的玩家编号，编号从 0 开始
	 * @note 如果 id 超出合法范围，返回 0
	 */
	virtual void GetNumberOfCards(int id) const = 0;

	/**
	 * @brief 查询玩家手牌
	 * @param id 待查询的玩家编号，编号从 0 开始
	 * @note 如果 id 超出合法范围，未定义（可以抛异常？）
	 */
	virtual const CardSet& GetHandCards(int id) const = 0;

	/**
	 * @brief 处理当前玩家跳过回合的情况
	 * @note 游戏的状态应该被修改至下一回合
	 */
	virtual void OnPass() = 0;

	/**
	 * @brief 处理当前玩家出牌的情况
	 * 
	 * @param card_set 当前玩家想要打出的卡牌
	 * @return true 如果当前玩家的出牌是合法的
	 * @note 如果当前玩家的牌合法，视作出牌，游戏状态应该被修改为下一回合
	 * @note 如果当前玩家的牌不合法，停留在当前回合
	 */
	virtual bool OnPlayCard(const CardSet& card_set) = 0;

	/**
	 * @brief 处理当前玩家是 AI 的情况
	 * @note 调用此函数时，此玩家此回合的行动将会由 AI 来代替，游戏状态应该被修改为下一回合
	 */
	virtual void OnAI() = 0;

	/**
	 * @brief 创建 Game 对象
	 * @param game_type 游戏类型
	 * @param num_player 玩家个数
	 * @param num_human 人类玩家个数
	 * @note 创建游戏，发放初始手牌，排列玩家顺序，决定从谁开始
	 */
	Game(GameType game_type, int num_player, int num_human);
	virtual ~Game() = 0;
};

/**
 * @brief 获取新游戏的指针
 * @param game_type 游戏类型
 * @return Game* 指向游戏的指针
 */
Game* GetGame(GameType game_type);