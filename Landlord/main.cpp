#include "gamepanel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<Cards>("Cards&");
    qRegisterMetaType<Cards>("Cards");
    QApplication a(argc, argv);
    GamePanel w;
    w.show();
    return a.exec();
}
