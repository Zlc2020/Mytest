#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QString normlImg,QString pressedimg,QWidget *parent = nullptr);
    //往下和往上的动画函数
    void moveDonw();
    void moveUp();
protected:
    enum MyPushButtonStat
    {
        Normal,
        Pressed,
    };
    void paintEvent(QPaintEvent *ev);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
private:
    QString normlImg;
    QString pressedimg;
    MyPushButtonStat mStat;
signals:

public slots:
};

#endif // MYPUSHBUTTON_H
