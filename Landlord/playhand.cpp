#include "playhand.h"

PlayHand::PlayHand() {}


// 传递给类一组牌，通过类分析出牌型，点数，以及相关的附属信息（比如：顺子，牌的数量）
PlayHand::PlayHand(Cards& cards)
{
    // 1. 对扑克牌进行分类：1张，2张，3张，4张多少种
    classify(cards);

    // 2. 牌型分类
    judgeCardType();

}

PlayHand::PlayHand(HandType type, Card::CardPoint pt, int extra)
{
    m_type = type;
    m_pt = pt;
    m_extra = extra;
}



bool PlayHand::canBeat(const PlayHand& other)            // 比较自己的牌和其它人的牌的牌型大小
{
    // 我的牌是未知的
    if(m_type == Hand_Unknown)
    {
        return false;
    }
    // 对方放弃出牌     Hand_Pass为过
    if(other.m_type == Hand_Pass)
    {
        return true;
    }

    // 1. 炸弹    2. 同类型的大小比较
    if(m_type == Hand_Bomb_Jokers)                      // 我是王炸
    {
        return true;
    }
    // 如果我是炸弹，判断其他人的牌型区间
    if(m_type == Hand_Bomb && other.m_type >= Hand_Single && other.m_type <= Hand_Seq_Single)
    {
        return true;
    }

    // 2. 双方牌型一致
    if(m_type == other.m_type)
    {
        if(m_type == Hand_Seq_Pair || m_type == Hand_Seq_Single)
        {   // 连对or顺子
            return m_pt > other.m_pt && m_extra == other.m_extra;
        }
        else
        {
            return m_pt > other.m_pt;
        }
    }
    return false;
}




void PlayHand::classify(Cards& cards)
{
    CardList list = cards.toCardList();
    int cardRecord[Card::Card_End];
    // 对数组初始化
    memset(cardRecord, 0, sizeof(int) * Card::Card_End);

    // 计数
    for(int i=0; i<list.size(); ++i)
    {
        Card c = list.at(i);
        cardRecord[c.point()]++;
    }
    // 清空容器
    m_oneCard.clear();
    m_twoCard.clear();
    m_threeCard.clear();
    m_fourCard.clear();
    // 存储
    for(int i=0; i<Card::Card_End; ++i)
    {
        if(cardRecord[i] ==1)
        {
            m_oneCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] ==2)
        {
            m_twoCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] ==3)
        {
            m_threeCard.push_back((Card::CardPoint)i);
        }
        else if(cardRecord[i] == 4)
        {
            m_fourCard.push_back((Card::CardPoint)i);
        }
    }

}

void PlayHand::judgeCardType()
{   // 对牌型进行分类
    m_type= Hand_Unknown;
    m_pt = Card::Card_Begin;
    m_extra = 0;

    if(isPass())                    // 玩家放弃出牌
    {
        m_type = Hand_Pass;
    }
    if(isSingle())
    {
        m_type = Hand_Single;
        m_pt = m_oneCard[0];
    }
    else if(isPair())
    {
        m_type = Hand_Pair;
        m_pt = m_twoCard[0];
    }
    else if(isTriple())
    {
        m_type = Hand_Triple;
        m_pt = m_threeCard[0];
    }
    else if(isTripleSingle())
    {
        m_type = Hand_Triple_Single;
        m_pt = m_threeCard[0];
    }
    else if(isTriplePair())
    {
        m_type = Hand_Triple_Pair;
        m_pt = m_threeCard[0];
    }
    else if(isPlane())
    {
        m_type = Hand_Plane;
        m_pt = m_threeCard[0];
    }
    else if(isPlaneTwoSingle())
    {
        m_type = Hand_Plane_Two_Single;
        m_pt = m_threeCard[0];
    }
    else if(isPlaneTwoPair())
    {
        m_type = Hand_Plane_Two_Pair;
        m_pt = m_threeCard[0];
    }
    else if(isSeqPair())
    {
        m_type = Hand_Seq_Pair;
        m_pt = m_twoCard[0];
        m_extra = m_twoCard.size();
    }
    else if(isSeqSingle())
    {
        m_type = Hand_Seq_Single;
        m_pt = m_oneCard[0];
        m_extra = m_oneCard.size();
    }
    else if(isBomb())
    {
        m_type = Hand_Bomb;
        m_pt = m_fourCard[0];
    }
    else if(isBombSingle())
    {
        m_type = Hand_Bomb_Single;
        m_pt = m_fourCard[0];
    }
    else if(isBombPair())
    {
        m_type = Hand_Bomb_Pair;
        m_pt = m_fourCard[0];
    }
    else if(isBombTwoSingle())
    {
        m_type = Hand_Bomb_Two_Single;
        m_pt = m_fourCard[0];
    }
    else if(isBombJokers())
    {
        m_type = Hand_Bomb_Jokers;
    }
    else if(isBombJokersSingle())
    {
        m_type = Hand_Bomb_Jokers_Single;
    }
    else if(isBombJokersPair())
    {
        m_type = Hand_Bomb_Jokers_Pair;
    }
    else if(isBombJokersTwoSingle())
    {
        m_type = Hand_Bomb_Jokers_Two_Single;
    }
}




PlayHand::HandType PlayHand::getHandType()
{
    return m_type;
}

Card::CardPoint PlayHand::getCardPoint()
{
    return m_pt;
}

int PlayHand::getExtra()
{
    return m_extra;
}


// 判断牌的类型
bool PlayHand::isPass()                        // 放弃出牌
{
    if(m_oneCard.size() == 0 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isSingle()                    // 单
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        return true;
    }
    return false;
}


bool PlayHand::isPair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1 && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isTriple()                    // 三个（相同
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.size() == 1 && m_fourCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isTripleSingle()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty() && m_threeCard.size() == 1 && m_fourCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isTriplePair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1 && m_threeCard.size() == 1 && m_fourCard.isEmpty())
    {
        return true;
    }
    return false;
}

bool PlayHand::isPlane()                // 飞机，不能出现2
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.size() == 2 && m_fourCard.isEmpty())
    {
        std::sort(m_threeCard.begin(), m_threeCard.end());              // 排序
        // 判断是否是连着，并且较大的不为2
        if(m_threeCard[1] - m_threeCard[0] == 1 && m_threeCard[1] < Card::Card_2)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isPlaneTwoSingle()           // 飞机带两单，不能是大小王
{
    if(m_oneCard.size() == 2 && m_twoCard.isEmpty() && m_threeCard.size() == 2 && m_fourCard.isEmpty())
    {
        std::sort(m_threeCard.begin(), m_threeCard.end());
        // 判断两单不能是大小王
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_threeCard[1] - m_threeCard[0] == 1 && m_threeCard[1] < Card::Card_2 &&
            m_oneCard[0] != Card::Card_SJ && m_oneCard[1] != Card::Card_BJ)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isPlaneTwoPair()           // 飞机带一对（不能是俩2）
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 2 && m_threeCard.size() == 2 && m_fourCard.isEmpty())
    {
        std::sort(m_threeCard.begin(), m_threeCard.end());
        if(m_threeCard[1] - m_threeCard[0] == 1 && m_threeCard[1] < Card::Card_2)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isSeqPair()                   // 连对
{
    if(m_oneCard.isEmpty() && m_twoCard.size() >= 3 && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_twoCard.begin(), m_twoCard.end());
        if(m_twoCard.last() - m_twoCard.first() == (m_twoCard.size() -1) &&
            m_twoCard.first() >= Card::Card_3 && m_twoCard.last() < Card::Card_2)
        {
            m_extra = m_twoCard.size();
            return true;
        }
    }
    return false;
}

bool PlayHand::isSeqSingle()
{
    if(m_oneCard.size() >= 5 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_oneCard.last() - m_oneCard.first() == (m_oneCard.size() -1) &&
            m_oneCard.first() >= Card::Card_3 && m_oneCard.last() < Card::Card_2)
        {
            m_extra = m_oneCard.size();
            return true;
        }
    }
    return false;
}

bool PlayHand::isBomb()
{
    if(m_oneCard.isEmpty() && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.size() == 1)
    {
        return true;
    }
    return false;
}

bool PlayHand::isBombSingle()
{
    if(m_oneCard.size() == 1 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.size() == 1)
    {
        return true;
    }
    return false;
}

bool PlayHand::isBombPair()
{
    if(m_oneCard.isEmpty() && m_twoCard.size() == 1 && m_threeCard.isEmpty() && m_fourCard.size() == 1)
    {
        return true;
    }
    return false;
}

bool PlayHand::isBombTwoSingle()
{
    if(m_oneCard.size() == 2 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.size() == 1)
    {
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_oneCard.first() != Card::Card_SJ && m_oneCard.last() != Card::Card_BJ)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isBombJokers()
{
    if(m_oneCard.size() == 2 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_oneCard.first() == Card::Card_SJ && m_oneCard.last() == Card::Card_BJ)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isBombJokersSingle()
{
    if(m_oneCard.size() == 3 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_oneCard[1] == Card::Card_SJ && m_oneCard[2] == Card::Card_BJ)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isBombJokersPair()
{
    if(m_oneCard.size() == 2 && m_twoCard.size() == 1 && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_oneCard[0] == Card::Card_SJ && m_oneCard[1] == Card::Card_BJ)
        {
            return true;
        }
    }
    return false;
}

bool PlayHand::isBombJokersTwoSingle()
{
    if(m_oneCard.size() == 4 && m_twoCard.isEmpty() && m_threeCard.isEmpty() && m_fourCard.isEmpty())
    {
        std::sort(m_oneCard.begin(), m_oneCard.end());
        if(m_oneCard[2] == Card::Card_SJ && m_oneCard[3] == Card::Card_BJ)
        {
            return true;
        }
    }
    return false;
}





































