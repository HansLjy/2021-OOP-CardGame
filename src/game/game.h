#pragma once

class Card {
public:
	/**
	 * @brief 获得该张卡片的 ID
	 * @return 卡片的 ID
	 * @todo 卡牌和 int 的映射方式待定
	 */
	virtual int GetID() const = 0;
};

// 以下类应继承自 Card 类
class UNOCard;
class PokeCard;

/**
 * @brief 卡牌集，手牌和准备打出的牌均以此方式传输
 * @note 卡牌集应当保持一定顺序
 */
class CardSet {
public:
	/**
	 * @brief 获得卡牌集的卡牌数
	 * @return int 卡牌数
	 */
	virtual int GetNumOfCards() = 0;

	/**
	 * @brief 获得第 k 张卡牌
	 * @param k 卡牌编号，从 0 开始
	 * @return const Card& 第 k 张卡牌的常引用
	 */
	virtual const Card& GetCard(int k) const = 0;

	/**
	 * @brief 从卡牌集中删除卡牌
	 * @param card 待删除的卡牌
	 * @note 如果有多张相同的卡牌，应当只删除一张；如果找不到此卡牌，此操作无效
	 */
	virtual void DeleteCard(const Card& card);

	/**
	 * @brief 像卡牌组中添加一张卡牌
	 * @note 添加的卡牌可以添加至末尾，但建议顺序保持卡牌的顺序，即按大小插入到正确位置
	 */
	virtual void AddCard() = 0;
};

// 一下类应继承自 CardSet，并提供不带参数的构造函数，要求此构造函数构造空的卡牌集
class UNOCardSet;
class PokeCardSet;

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
 * 下列函数应当继承自 Game 类
 */
class UNOGame;
class PokeGame;