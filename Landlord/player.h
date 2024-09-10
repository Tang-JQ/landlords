#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "cards.h"

class Player : public QObject
{
    Q_OBJECT
public:

    explicit Player(QObject *parent = nullptr);
    explicit Player(QString name, QObject *parent = nullptr);

    // 玩家信息
    enum Role{Lord, Farmer};                                    // 角色
    enum Sex{Man, Woman};                                       // 性别
    enum Direction{Left, Right};                                // 头像显示方位
    enum Type{Robot, User, UnKnow};                             // 玩家类星

    // 设置 & 获取玩家信息   --- 姓名/角色/。。。/分数/输赢
    void setName(QString name);
    QString getName();
    void setRole(Role role);
    Role getRole();
    void setSex(Sex sex);
    Sex getSex();
    void setDirection(Direction direction);
    Direction getDirection();
    void setType(Type type);
    Type getType();
    void setScore(int score);
    int getScore();
    void setWin(bool flag);
    bool isWin();

    // 提供当前对象的上家/下家对象
    void setPrevPlayer(Player* player);
    void setNextPlayer(Player* player);
    Player* getPrevPlayer();
    Player* getNextPlayer();

    // 叫地主/抢地主
    void grabLordBet(int point);

    // 存储扑克牌（发牌时得到的）
    void storeDispatchCard(Card& card);                         // 玩家每次发一张牌
    void storeDispatchCard(Cards& cards);                       // 最后剩余三张牌 -- 给地主留的

    // 得到/清空所有的牌
    Cards getCards();
    void clearCards();

    // 出牌
    void playHand(Cards& cards);

    // 设置出牌的玩家以及待处理的扑克牌
    void setPendingInfo(Player* player, Cards& cards);
    Player* getPendPlayer();
    Cards getPendCards();

    // 存储出牌玩家对象和打出的牌
    void storePendingInfo(Player* player, Cards& cards);

    // 虚函数  ----- 准备叫地主/出牌
    virtual void prepareCallLord();
    virtual void preparePlayHand();
    virtual void thinkCallLord();               // 考虑叫地主
    virtual void thinkPlayHand();               // 考虑出牌





signals:
    // 通知已下注
    void notifyGrabLordBet(Player* player,int bet);
    // 通知已经出牌
    void notifyPlayHand(Player* player, Cards& cards);
    // 通知已经发牌了
    void notifyPickCards(Player* player, Cards& cards);


protected:                                          // protected在派生类（子类）中是可以访问的，private不行（保护性更强）
    QString m_name;
    Role m_role;
    Sex m_sex;
    Direction m_direction;
    Type m_type;
    int m_score;
    bool m_isWin;
    Player* m_prev;
    Player* m_next;
    Cards m_cards;                                  // 存储多张扑克牌（玩家手中的牌）

    Cards m_pendCards;                              // 玩家打出的牌
    Player* m_pendPlayer;                           // 出牌的玩家
};

#endif // PLAYER_H
