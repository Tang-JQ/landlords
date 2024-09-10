#include "mybutton.h"

#include <QMouseEvent>
#include <QPainter>

MyButton::MyButton(QWidget *parent)
    : QPushButton{parent}
{}


void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    m_normal = normal;
    m_hover = hover;
    m_pressed = pressed;
    m_pixmap.load(m_normal);
    update();
}

// 鼠标按下
void MyButton::mousePressEvent(QMouseEvent* ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_pressed);
        update();
    }
    QPushButton::mousePressEvent(ev);
}
// 鼠标释放
void MyButton::mouseReleaseEvent(QMouseEvent* ev)
{
    if(ev->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_normal);
        update();
    }
    QPushButton::mouseReleaseEvent(ev);
}
// 鼠标进入
void MyButton::enterEvent(QEvent* ev)
{
    m_pixmap.load(m_hover);
    update();
}
// 鼠标离开
void MyButton::leaveEvent(QEvent* ev)
{
    m_pixmap.load(m_normal);
    update();
}

// 绘图
void MyButton::paintEvent(QPaintEvent* ev)
{
    QPainter p(this);
    p.drawPixmap(rect(), m_pixmap);
}





























