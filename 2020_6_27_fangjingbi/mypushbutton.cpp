#include "mypushbutton.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QDebug>

MyPushButton::MyPushButton(QString normlImg,QString pressedimg,QWidget *parent)
    : QPushButton(parent)
    , normlImg(normlImg)
    , pressedimg(pressedimg)
{
    mStat=Normal;
}
//绘画
void MyPushButton::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);
    QPixmap pix;
    if(mStat  == Normal)
        pix.load(normlImg);
    if(mStat  == Pressed)
        pix.load(pressedimg);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //绘制按钮的文字
    painter.drawText(0,0,this->width(),this->height(),
                     Qt::AlignHCenter|Qt::AlignVCenter,this->text());
}
//鼠标进入
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    this->mStat=Pressed;
    this->update();
    QPushButton::mousePressEvent(e);
}
//鼠标移出
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    this->mStat=Normal;
    this->update();
    QPushButton::mouseReleaseEvent(e);
}
//鼠标按下
void MyPushButton::moveDonw()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
//鼠标弹起
void MyPushButton::moveUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry",this);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setDuration(100);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
