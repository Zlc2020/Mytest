#include "coinbutton.h"
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <QTimer>
coinbutton::coinbutton(QWidget *parent) : QPushButton(parent)
{
    //初始化
    setStat(0);

    //设置按钮不规则样式，去掉边框
    this->setStyleSheet("QPushButton{border:0px;}");

    connect(&this->mTimer,&QTimer::timeout,[=]()
    {
        if(mStat)
        {
            mThatOne--;
        }
        else
        {
            mThatOne++;
        }

        this->setIcon(QIcon(QString(":/res/Coin000%1.png").arg(mThatOne)));

        if(mThatOne==1 || mThatOne==8)
        {
            this->mTimer.stop();
        }
    });
}

void coinbutton::paintEvent(QPaintEvent *ev)
{
    //    static int a=0;
    //    qDebug()<<a++;
    //绘制按钮的图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/BoardNode.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //调用父类的paintEvent
    QPushButton::paintEvent(ev);
}

//获取正反面
int coinbutton::stat()const
{
    return this->mStat;
}

//设置正反面
void coinbutton::setStat(int stat)
{
    this->mStat=stat;

    if(this->mStat)
    {
        //金币
        this->setIcon(QIcon(":/res/Coin0001.png"));
    }
    else
    {
        //银币
        this->setIcon(QIcon(":/res/Coin0008.png"));
    }
    //设置icon大小
    this->setIconSize(this->size());
}

//显示金币变化
void coinbutton::setStatWithAnimation(int stat)
{

    mStat = stat;

    if(mStat)
    {
        mThatOne = 8;
    }
    else
    {
        mThatOne = 1;
    }

    this->mTimer.start(30);
}

//硬币翻转函数
void coinbutton::flip()
{
    setStatWithAnimation(!mStat);
}
