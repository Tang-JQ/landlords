#ifndef GAMECONTROL_H
#define GAMECONTROL_H

#include <QObject>
#include "robot.h"
#include "userplayer.h"
#include "cards.h"
#include <QTimer>


struct BetRecord
{
    BetRecord()
    {
        reset();
    }
    void reset()
    {
        player = nullptr;
        bet = 0;
        times = 0;
    }
    Player* player;
    int bet;
    int times;              // 第几次叫地主
};

class GameControl : public QObject
{
    Q_OBJECT
public:
    // 游戏状态   -- 发牌/叫地主/出牌状态
    enum GameStatus
    {
        DispatchCard,
        CallingLord,
        PlayingHand
    };
    // 玩家状态  --- 考虑叫地主/考虑出牌/获胜
    enum PlayerStatus
    {
        ThinkingForCallLord,
        ThinkingForPlayHand,
        Winning
    };

    explicit GameControl(QObject *parent = nullptr);

    // 初始化玩家
    void playerInit();

    // 得到玩家的实例对象
    Robot* getLeftRobot();
    Robot* getRightRobot();
    UserPlayer* getUserPlayer();

    // 设置/获取当前玩家
    void setCurrentPlayer(Player* player);
    Player* getCurrentPlayer();

    // 得到出牌玩家和打出的牌（不一定时当前玩家）
    Player* getHandPlayer();
    Cards getPendCards();

    // 初始化扑克牌
    void initAllCards();
    // 每次发一张牌
    Card takeOneCard();
    // 得到最后的三张底牌
    Cards getSurplusCards();
    //重置卡牌数据
    void resetCardData();

    // 准备叫地主
    void startLordCard();
    // 成为地主
    void becomeLord(Player* player, int bet);

    // 清空所有玩家的得分
    void clearPlayerScore();

    // 得到玩家下注的最高分数
    int getPlayerMaxBet();

    // 处理叫地主
    void onGrabBet(Player* player, int bet);

    //处理出牌
    void onPlayHand(Player* player, Cards& cards);

signals:
    // 通知玩家改变状态
    void playerStatusChanged(Player* player, PlayerStatus status);
    // 通知玩家抢地主了
    void notifyGrabLordBet(Player* player, int bet, bool flag);
    // 游戏状态变化
    void gameStatusChanged(GameStatus status);
    // 通知玩家出牌了
    void notifyPlayHand(Player* player, Cards& cards);
    // 给玩家传递出牌数据
    void pendingInfo(Player* player, Cards& cards);


private:
    // 两个机器人一个玩家+所有扑克牌  --- 当前玩家 --- 当前出牌的玩家/牌
    Robot* m_robotLeft;
    Robot* m_robotRight;
    UserPlayer* m_user;
    Cards m_allCards;
    Player* m_currPlayer;
    Player* m_pendPlayer;
    Cards m_pendCards;

    // 下注最大的
    BetRecord m_betRecord;

    // 下注分数
    int m_curBet;
};

#endif // GAMECONTROL_H















