#include "playscenecpp.h"
#include "MyMainWindow.h"
#include "MyPushButton.h"
#include "dataconfig.h"
#include "coinbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QmenuBar>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QPropertyAnimation>
#include <QDebug>
#include <QSound>

playscenecpp::playscenecpp(int level,QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("加油");

    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    //设置大小和移动
    btnBack->resize(72,32);
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //关联按钮功能
    connect(btnBack,&QPushButton::clicked,this,&playscenecpp::backBtinClicked);

    //添加左下角的label
    QLabel *label = new QLabel(this);
    label->setText(QString("Level: %1").arg(level));
    label->resize(150,50);
    //设置字体
    label->setFont(QFont("华文新魏",20));
    //移动到左下角
    label->move(30,this->height()-label->height());

    const int colWidth = 50;
    const int rowHeight = 50;
    const int xOffset = 57;
    const int yOffset = 200;

    dataConfig data;
    QVector <QVector <int > > dataArray = data.mData[level];
    mHasWin =false;
    for(int row=0;row<4;++row)
    {
        for(int col=0;col<4;++col)
        {
            int x = xOffset+colWidth*row;
            int y = yOffset+rowHeight*col;
            //创建按钮
            coinbutton *btn = new coinbutton(this);
            btn->setGeometry(x,y,50,50);
            //根据数据设置
            btn->setStat(dataArray[row][col]);
            //保持按钮的指针
            mCoins[row][col] = btn;

            connect(btn,&QPushButton::clicked,[=](){
                this->flip(row,col);
            });
        }
    }

}

void playscenecpp::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    //搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    //画背景
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画logo
    QPixmap pix1(":/res/Title.png");
    painter.drawPixmap(0,0,268/2,96/2,pix1);
}

//改变金币动态
void playscenecpp::flip(int row,int col)
{
    if(mHasWin)
    {
        return;
    }


    //翻金币的音效
    QSound::play(":/res/ConFlipSound.wav");

    mCoins[row][col]->flip();

    QTimer::singleShot(250,[=](){
        if(col-1 != -1)
        {
            mCoins[row][col-1]->flip();
        }

        if(col+1 != 4 )
        {
            mCoins[row][col+1]->flip();
        }

        if(row-1 != -1)
        {
            mCoins[row-1][col]->flip();
        }

        if(row+1 != 4 )
        {
            mCoins[row+1][col]->flip();
        }

        //判断游戏是否胜利
        this->judgeWin();
    });
}

//判断是否通关
void playscenecpp::judgeWin()
{

    for(int row=0;row<4;++row)
    {
        for(int col=0;col<4;++col)
        {
            if(!mCoins[row][col]->mStat)
            {
                return;
            }
        }
    }

    //播放胜利音效

    QSound::play(":/res/LevelWinSound.wav");


    mHasWin = true;
    //播放胜利动画
    QLabel *labelWin = new QLabel(this);
    QPixmap pix = QPixmap(":/res/LevelCompletedDialogBg.png");
    labelWin->setPixmap(pix);
    labelWin->resize(pix.size());
    labelWin->show();
    labelWin->move((this->width()-labelWin->width())/2,0);

    QPropertyAnimation *animation = new QPropertyAnimation(labelWin,"geometry",this);
    animation->setStartValue(labelWin->geometry());
    animation->setEndValue(QRect(labelWin->x(),labelWin->y()+100,labelWin->width(),labelWin->height()));
    animation->setDuration(2000);
    //设置动画的运动曲线
    animation->setEasingCurve(QEasingCurve::OutInElastic);
    //动画播放完自动删除动画对象
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
