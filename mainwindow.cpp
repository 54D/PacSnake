#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Snake.h"
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QGraphicsScene * scene = new QGraphicsScene(0,0,1000,600,this);
    Snake * snake = new Snake();
    snake->setRect(0,0,20,100);
    scene->addItem(snake);
    snake->setFlag(QGraphicsItem::ItemIsFocusable);
    snake->setFocus();
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();
}
