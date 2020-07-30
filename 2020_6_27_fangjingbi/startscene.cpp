#include "startscene.h"
#include "selectscene.h"
#include <QPushButton>
#include "mypushbutton.h"
#include <QPainter>
#include <QTimer>
#include <QmenuBar>
#include <QSound>

StartScene::StartScene(QWidget *parent) : MyMainWindow(parent)
{
    this->setWindowTitle("开始");

    //创建按钮
    MyPushButton *btnStart = new MyPushButton(":/res/MenuSceneStartButton.png",":/res/MenuSceneStartButton.png",this);

    //设置按钮大小
    btnStart->resize(114,114);
    //移动按钮到指定位置

    btnStart->move((this->width()-btnStart->width())/2,
                   this->height()*3/4-btnStart->height()/2);

    //给selectscene里的信号加槽
    connect(&this->mSelectScene,&selectscene::backBtnClicked,[=]()
    {
        QSound::play(":/res/TapButtonSound.wav");

        this->move(mSelectScene.pos());
        this->mSelectScene.hide();
        this->show();
    });

    //设置按钮动态
    connect(btnStart,&MyPushButton::clicked,[=](){
        //把按钮设置成不可用
        QSound::play(":/res/BackButtonSound.wav");
        btnStart->setEnabled(false);

        btnStart->moveDonw();

        QTimer::singleShot(110,[=](){
            btnStart->moveUp();
        });

        QTimer::singleShot(220,[=](){
            //恢复按钮
            btnStart->setEnabled(true);
            this->mSelectScene.move(this->pos());
            this->hide();
            this->mSelectScene.show();
        });
    });

}

void StartScene::paintEvent(QPaintEvent *event)
{
    //绘制背景图片
    QPainter painter(this);
    painter.translate(0,this->menuBar()->height());
    QPixmap pix(":/res/MenuSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
