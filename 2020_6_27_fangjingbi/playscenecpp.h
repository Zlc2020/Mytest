#ifndef PLAYSCENECPP_H
#define PLAYSCENECPP_H

#include <QWidget>
#include <MyMainWindow.h>
#include <coinbutton.h>

class playscenecpp : public MyMainWindow
{
    Q_OBJECT
public:
    explicit playscenecpp(int level,QWidget *parent = nullptr);

signals:
    void backBtinClicked();
protected:
 void paintEvent(QPaintEvent *event);
  void flip(int row,int col);
  void judgeWin();
private:
    coinbutton *mCoins[4][4];
    bool mHasWin;
public slots:

};

#endif // PLAYSCENECPP_H
