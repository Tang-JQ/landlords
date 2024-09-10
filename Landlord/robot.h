#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include "player.h"

class Robot : public Player
{
    Q_OBJECT
public:
    using Player::Player;
    explicit Robot(QObject *parent = nullptr);

    // 虚函数 ---- 叫地主以及待处理的扑克牌
    void prepareCallLord() override;
    void preparePlayHand() override;

    // 考虑叫地主  --- override用于检测重写的函数名是否正确
    void thinkCallLord() override;

    void thinkPlayHand() override;               // 考虑出牌
};

#endif // ROBOT_H
