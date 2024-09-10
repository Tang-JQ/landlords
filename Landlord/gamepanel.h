#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QMainWindow>
#include "gamecontrol.h"
#include "cardpanel.h"
#include <QLabel>
#include <QMap>
#include <QTimer>
#include "animationwindow.h"
#include "countdown.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class GamePanel;
}
QT_END_NAMESPACE

class GamePanel : public QMainWindow
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = nullptr);
    ~GamePanel();


    // 初始化游戏控制类
    void gameControlInit();


    // 处理游戏的状态
    void gameStatusProcess(GameControl::GameStatus status);

    // 更新分数面板的分数
    void updatePlayerScore();
    // 切割并存储图片
    void initCardMap();
    // 裁剪图片
    void cropImage(QPixmap& pix, int x, int y, Card& c);

    // 初始化游戏按钮组
    void initButtonsGroup();

    // 7. 初始化玩家在窗口中的上下文环境
    void initPlayerContext();

    // 初始化游戏场景
    void initGameScene();


    // 发牌
    void startDispatchCard();

    // 移动扑克牌
    void cardMoveStep(Player* player, int curPos);

    // 处理分发得到的扑克牌
    void disposCard(Player* player, Cards& cards);

    // 更新扑克牌在窗口中的显示
    void updatePlayerCards(Player* player);

    // 加载玩家头像
    QPixmap loadRoleImage(Player::Sex sex, Player::Direction direct, Player::Role role);



    // 定时器的处理动作
    void onDispatchCard();

    // 处理玩家状态的变化
    void onPlayerStatusChanged(Player* player, GameControl::PlayerStatus status);

    //处理玩家抢地主
    void onGarbLordBet(Player* player, int bet, bool flag);

    // 隐藏玩家打出的牌
    void hidePlayerDropCards(Player* player);

    // 处理玩家的出牌
    void onDisposePlayHand(Player* player, Cards& cards);

    // 处理玩家选牌
    void onCardSelected(Qt::MouseButton button);

    // 处理玩家出牌
    void onUserPlayHand();

    // 用户玩家放弃出牌
    void onUserPass();

    // 显示特效动画
    enum AnimationType{ShunZi, LianDui, Plane, JokerBomb, Bomb, Bet};
    void showAnimation(AnimationType type, int bet = 0);


    // 显示玩家的最终得分
    void showEndingScorePanel();

    // 初始化闹钟倒计时
    void initCountDown();


protected:
    void paintEvent(QPaintEvent* ev);
    void mouseMoveEvent(QMouseEvent* ev);

private:
    enum CardAlign{Horizontal, Vertical};
    struct PlayerContext
    {
        // 1. 玩家扑克牌显示的区域
        QRect cardRect;
        // 2. 出牌的区域
        QRect playHandRect;
        // 3. 扑克牌的对齐方式（水平 or 垂直）
        CardAlign align;
        // 4. 扑克牌显示正面还是背面
        bool isFrontSide;
        // 5. 游戏过程中的提示信息， 比如： 不出
        QLabel* info;
        // 6. 玩家的头像
        QLabel* roleImg;
        // 7. 玩家刚打出的牌
        Cards lastCards;
    };
    QMap<Player*, PlayerContext> m_contextMap;

    Ui::GamePanel *ui;
    QPixmap m_bkImage;
    GameControl* m_gameCtl;
    QVector<Player*> m_playerList;                  // 储存用户玩家指针的数组
    QMap<Card, CardPanel*> m_cardMap;               // 分割保存扑克牌
    QSize m_cardSize;                               // 保存单张图片大小
    QPixmap m_cardBackImg;                          // 卡牌背景图片

    CardPanel* m_baseCard;                          // 发牌区扑克牌
    CardPanel* m_moveCard;                          // 移动的扑克牌
    QVector<CardPanel*> m_last3Card;                // 最后三张
    QPoint m_baseCardPos;                           // 发牌区扑克牌的位置

    GameControl::GameStatus m_gameStatus;           // 游戏状态
    QTimer* m_timer;

    AnimationWindow* m_animation;                   // 动画

    CardPanel* m_curSelCard;                        // 当前选中的窗口对象
    QSet<CardPanel*> m_selectCards;                 // 当前选中的卡牌对象

    // 实现扑克牌的框选功能
    QRect m_cardsRect;
    QHash<CardPanel*, QRect> m_userCards;

    // 闹钟
    CountDown* m_countDown;
};
#endif // GAMEPANEL_H


















