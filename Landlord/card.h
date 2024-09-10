#ifndef CARD_H
#define CARD_H
#include <QVector>

class Card
{
public:
    //花色
    enum CardSuit
    {
        Suit_Begin,
        Diamond,            //方块
        Club,               //梅花
        Heart,              //红桃
        Spade,              //黑桃
        Suit_End
    };
    //点数
    enum CardPoint
    {
        Card_Begin,
        Card_3,
        Card_4,
        Card_5,
        Card_6,
        Card_7,
        Card_8,
        Card_9,
        Card_10,
        Card_J,
        Card_Q,
        Card_K,
        Card_A,
        Card_2,
        Card_SJ,            //small joker
        Card_BJ,            //big joker
        Card_End
    };

    Card();
    Card(CardPoint point, CardSuit suit);

    // 成员函数
    void setPoint(CardPoint point);         //设置点数
    void setSuit(CardSuit suit);            //设置花色
    CardPoint point() const;                           //获得点数
    CardSuit suit() const;                            //获得花色

    // 私有 成员变量
private:
    CardPoint m_point;
    CardSuit m_suit;

};


// 对象比较
bool lessSort(const Card& c1, const Card& c2);
bool greaterSort(const Card& c1, const Card& c2);

// 下列两个步骤 --- 解决QSet值必须是可赋值数据类型，提供一个==和qHash（返回哈希值，函数可自定义）
// 操作符重载 ==
bool operator <(const Card& c1, const Card& c2);
bool operator ==(const Card& left, const Card& right);

// 重写全局函数qHash
uint qHash(const Card& card);



//定义类型的别名
using CardList = QVector<Card>;


#endif // CARD_H











