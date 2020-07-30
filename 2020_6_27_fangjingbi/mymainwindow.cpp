#include "mymainwindow.h"
#include "ui_mymainwindow.h"
MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    //设置窗口的icon
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置窗口的固定大小
    this->setFixedSize(320,588);
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}
