#include "userplayer.h"

UserPlayer::UserPlayer(QObject *parent)
    : Player{parent}
{
    m_type = Player::User;
}


// 虚函数 ---- 叫地主以及待处理的扑克牌
void UserPlayer::prepareCallLord()
{

}
void UserPlayer::preparePlayHand()
{
    emit startCountDown();
}































