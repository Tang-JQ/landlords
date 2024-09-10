#ifndef USERPLAYER_H
#define USERPLAYER_H

#include <QObject>
#include "player.h"

class UserPlayer : public Player
{
    Q_OBJECT
public:
    using Player::Player;

    explicit UserPlayer(QObject *parent = nullptr);

    // 虚函数 ---- 叫地主以及待处理的扑克牌
    void prepareCallLord() override;
    void preparePlayHand() override;

signals:
    void startCountDown();
};

#endif // USERPLAYER_H
