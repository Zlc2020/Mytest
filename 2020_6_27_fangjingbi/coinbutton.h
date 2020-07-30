#ifndef COINBUTTON_H
#define COINBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QTimer>
class coinbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit coinbutton(QWidget *parent = nullptr);
    int stat() const;
    void setStat(int stat);
    //硬币翻转函数
    void flip();
    //显示硬币动画
    void setStatWithAnimation(int stat);
public:
    int mStat;
private:
    int mThatOne;
    QTimer mTimer;
protected:
    void paintEvent(QPaintEvent *ev);
signals:

public slots:
};

#endif // COINBUTTON_H
