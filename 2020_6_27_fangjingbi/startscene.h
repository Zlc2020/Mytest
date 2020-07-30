#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include "mymainwindow.h"
#include "selectscene.h"

class StartScene : public MyMainWindow
{
    Q_OBJECT
public:
    explicit StartScene(QWidget *parent = nullptr);

signals:

protected:
 void paintEvent(QPaintEvent *event);
public slots:
private:
    selectscene mSelectScene;
};

#endif // STARTSCENE_H
