#ifndef STRATEGY_H
#define STRATEGY_H

#include "player.h"
#include "cards.h"
#include "playhand.h"
#include <QMap>

class Strategy
{
public:
    Strategy(Player* player, const Cards& cards);


    // 1.制定出牌策略
    Cards makeStrategy();
    // 2.第一个出牌时，怎么出firstPlay
    Cards firstPlay();
    // 3.得到比指定牌型大的牌
    Cards getGreaterCards(PlayHand type);
    // 4.能打过指定的牌时，判断是出牌还是放行，返回true->出牌，返回false->放行
    bool whetherToBeat(Cards& cs);

    // 5.找出指定数量（count）的相同点数的牌（point)，找出count张点数为point的牌
    Cards findSamePointCards(Card::CardPoint point, int count);
    // 6.找出所有点数为count的牌 ====>  得到一个多张扑克牌数组
    QVector<Cards> findCardsByCount(int count);
    // 7.根据点数范围找牌
    Cards getRangeCards(Card::CardPoint begin, Card::CardPoint end);
    // 8.按牌型找牌，并且指定要找的牌是否要打过指定的牌型
    QVector<Cards> findCardType(PlayHand hand, bool beat);

    // 9. 从指定的Cards对象中挑选出满足条件的顺子
    void pickSeqSingles(QVector<QVector<Cards>> &allSeqRecord, const QVector<Cards> &seqSingle, const Cards& cards);

    // 10.最优的顺子的集合的筛选函数
    QVector<Cards> pickOptimalSeqSingles();


private:
    using function = Cards (Strategy::*)(Card::CardPoint point);
    struct CardInfo
    {
        Card::CardPoint begin;
        Card::CardPoint end;
        int extra;                      // 顺子或者连对的数量
        bool beat;
        int number;                     // 指定点数的牌的数量，顺子=1，连对=2
        int base;                       // 最基础的顺子或连对的数量
        function getSeq;
    };

    // 从point开始找number张牌（找n张牌）
    QVector<Cards> getCards(Card::CardPoint point, int number);
    // 找三带一或三代二的牌
    QVector<Cards> getTripleSingleOrPair(Card::CardPoint begin, PlayHand::HandType type);
    // 飞机
    QVector<Cards> getPlane(Card::CardPoint begin);
    // 飞机带一单或一对
    QVector<Cards> getPlane2SingleOr2Pair(Card::CardPoint begin, PlayHand::HandType type);
    // 连对or顺子，把beat传进来才能知道是找更大的还是随便找
    QVector<Cards> getSeqPairOrSeqSingle(CardInfo &info);
    // 返回到结构体CardInfo中的两个函数
    Cards getBaseSeqPair(Card::CardPoint point);
    Cards getBaseSeqSingle(Card::CardPoint point);
    // 找炸弹
    QVector<Cards> getBomb(Card::CardPoint begin);



private:

    Player* m_player;
    Cards m_cards;




};

#endif // STRATEGY_H


