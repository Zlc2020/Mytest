#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <MyMainWindow.h>

class selectscene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit selectscene(QWidget *parent = nullptr);

signals:
    void backBtnClicked();
protected:
 void paintEvent(QPaintEvent *event);
public slots:
};

#endif // SELECTSCENE_H
