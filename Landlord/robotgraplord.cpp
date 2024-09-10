#include "robotgraplord.h"

RobotGrapLord::RobotGrapLord(Player* player, QObject *parent)
    : QThread{parent}
{
    m_player = player;
}


void RobotGrapLord::run()
{
    msleep(2000);                   // 叫地主前的缓冲
    m_player->thinkCallLord();
}
