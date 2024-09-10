#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{
    m_score = 0;
    m_isWin = false;
}

Player::Player(QString name, QObject *parent) : Player(parent)
{
    m_name = name;
}


// 叫地主/抢地主
void Player::grabLordBet(int point)
{
    emit notifyGrabLordBet(this, point);
}

// 设置出牌的玩家以及待处理的扑克牌
void Player::setPendingInfo(Player* player, Cards& cards)
{
    m_pendCards = cards;
    m_pendPlayer = player;
}
Player* Player::getPendPlayer()
{
    return m_pendPlayer;
}
Cards Player::getPendCards()
{
    return m_pendCards;
}

// 存储扑克牌（发牌时得到的）
void Player::storeDispatchCard(Card& card)                         // 玩家每次发一张牌
{
    m_cards.add(card);
    Cards cs;
    cs.add(card);
    emit notifyPickCards(this, cs);
}
void Player::storeDispatchCard(Cards& cards)                       // 最后剩余三张牌 -- 给地主留的
{
    m_cards.add(cards);
    emit notifyPickCards(this, cards);
}

// 得到/清空所有的牌
Cards Player::getCards()
{
    return m_cards;
}
void Player::clearCards()
{
    m_cards.clear();
}

// 出牌
void Player::playHand(Cards& cards)
{
    m_cards.remove(cards);
    emit notifyPlayHand(this, cards);
}


void Player::setName(QString name)
{
    m_name = name;
}
QString Player::getName()
{
    return m_name;
}

void Player::setRole(Role role)
{
    m_role = role;
}
Player::Role Player::getRole()
{
    return m_role;
}

void Player::setSex(Sex sex)
{
    m_sex = sex;
}
Player::Sex Player::getSex()
{
    return m_sex;
}

void Player::setDirection(Direction direction)
{
    m_direction = direction;
}
Player::Direction Player::getDirection()
{
    return m_direction;
}

void Player::setType(Type type)
{
    m_type = type;
}
Player::Type Player::getType()
{
    return m_type;
}

void Player::setScore(int score)
{
    m_score = score;
}
int Player::getScore()
{
    return m_score;
}


void Player::setWin(bool flag)
{
    m_isWin = flag;
}
bool Player::isWin()
{
    return m_isWin;
}

void Player::setPrevPlayer(Player* player)
{
    m_prev = player;
}
void Player::setNextPlayer(Player* player)
{
    m_next = player;
}
Player* Player::getPrevPlayer()
{
    return m_prev;
}
Player* Player::getNextPlayer()
{
    return m_next;
}



// 存储出牌玩家对象和打出的牌
void Player::storePendingInfo(Player* player, Cards& cards)
{
    m_pendPlayer = player;
    m_pendCards = cards;
}


// 虚函数  ----- 准备叫地主/出牌
void Player::prepareCallLord()
{

}
void Player::preparePlayHand()
{

}

void Player::thinkCallLord()               // 考虑叫地主
{

}


void Player::thinkPlayHand()               // 考虑出牌
{

}





