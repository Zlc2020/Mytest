#include "selectscene.h"
#include "playscenecpp.h"
#include <QPainter>
#include <QPixmap>
#include <QMenuBar>
#include <QSound>
#include "mypushbutton.h"
selectscene::selectscene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("选择关卡");

    MyPushButton *btnBack = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png",this);
    //设置大小和移动
    btnBack->resize(72,32);
    btnBack->move(this->width()-btnBack->width(),this->height()-btnBack->height());

    //点击信号连接selectscene::backBtnClicked 信号
    connect(btnBack,&QPushButton::clicked,this,&selectscene::backBtnClicked);

    //关卡按钮20个
    const int colWidth = 70;
    const int rowHeight = 70;
    //x y 偏移
    const int xOffset = 25 ;
    const int yOffset = 130 ;

    for(int i=0;i<20;i++)
    {
        MyPushButton *btn = new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon.png",this);
        btn->setText(QString::number(i+1));
        btn->resize(57,57);

        int col=i%4;
        int row = i/4;

        int x = colWidth * col + xOffset;
        int y = rowHeight * row + yOffset;

        btn->move(x,y);

        connect(btn,&MyPushButton::clicked,[=](){
            //点击按钮创建第3场景隐藏第2场景
            QSound::play(":/res/BackButtonSound.wav");
            playscenecpp *playScene = new playscenecpp(i+1);
            playScene->setAttribute(Qt::WA_DeleteOnClose);
            playScene->move(this->pos());
            this->hide();
            playScene->show();
            connect(playScene,&playscenecpp::backBtinClicked,[=](){

                 QSound::play(":/res/TapButtonSound.wav");

                 this->move(playScene->pos());
                 this->show();
                 playScene->close();
            });

        });

    }
}

void selectscene::paintEvent(QPaintEvent *event)
{
    //绘制背景图片

    QPainter painter(this);
    //搬动画家到菜单栏下面
    painter.translate(0,this->menuBar()->height());
    //画背景
    QPixmap pix(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //画logo
    QPixmap pix1(":/res/Title.png");
    painter.drawPixmap(0,0,268,96,pix1);
}
