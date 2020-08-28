#include "OpenGame.h"
#include"MachineGame.h"
#include"NetGame.h"
#include "ui_OpenGame.h"
#include"GameScene.h"
#include <QDebug>
#include"MachineGameSelect.h"
#define GRIDCOUNT1 11   //棋盘竖向均分
#define GRIDCOUNT2 14   //棋盘横向均分
OpenGame::OpenGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpenGame)
{
    ui->setupUi(this);
    this->setWindowTitle("中国象棋");
    //ui->pushButton2->setFocusPolicy((Qt::TabFocus));
    //this->setMinimumSize()
    this->setMinimumSize(655,506);
    backGround1->setLoops(-1);
    backGround1->play();
//    GameScene *gameScene=new GameScene;
  //  connect(ui->pushButton1,&QPushButton::clicked,gameScene,&GameScene::Getthenew1);
    connect(ui->pushButton1,&QPushButton::clicked,this,&OpenGame::button1Slot);
    connect(ui->pushButton1,&QPushButton::clicked,this,&OpenGame::getthenew1);
    connect(ui->pushButton2,&QPushButton::clicked,this,&OpenGame::button2Slot);
//    connect(ui->pushButton2,&QPushButton::clicked,this,&OpenGame::getthenew2);
    connect(ui->pushButton3,&QPushButton::clicked,this,&OpenGame::button3Slot);
    connect(ui->pushButton3,&QPushButton::clicked,this,&OpenGame::getthenew3);
}

OpenGame::~OpenGame()
{
   delete ui;
}

void OpenGame::resizeEvent(QResizeEvent *event)
{
    gridWidth=event->size().width()/GRIDCOUNT2;
    gridHeight=event->size().height()/GRIDCOUNT1;
    qDebug()<<"old:"<<event->oldSize();
    qDebug()<<"new:"<<event->size();
}
void OpenGame::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rect(QPoint(0,0),QPoint(this->width(),this->height()));
    QPixmap pix(":/img/b15.jpg");
    //setFont("华文楷体",r,)
    painter.setFont(QFont("华文行楷",gridWidth,1000));
    painter.drawPixmap(rect,pix);
    QRect rec1(3*gridWidth,gridHeight,2*gridWidth,2*gridHeight);
    QRect rec2(3*gridWidth,3.5*gridHeight,2*gridWidth,2*gridHeight);
    QRect rec3(3*gridWidth,6*gridHeight,2*gridWidth,2*gridHeight);
    QRect rec4(3*gridWidth,8.5*gridHeight,2*gridWidth,2*gridHeight);
    painter.drawText(rec1,"中",QTextOption(Qt::AlignCenter));
    painter.drawText(rec2,"国",QTextOption(Qt::AlignCenter));
    painter.drawText(rec3,"象",QTextOption(Qt::AlignCenter));
    painter.drawText(rec4,"棋",QTextOption(Qt::AlignCenter));
    painter.end();
}

void OpenGame::button1Slot(){
    GameScene *gamescene=new GameScene;
    backGround1->stop();//音乐停
    connect(this,&OpenGame::getthenew1,gamescene,&GameScene::Getthenew1);
//    GameScene *gamescene1=new GameScene;
    this->close();
    gamescene->show();
//    GameScene *board=new GameScene;
//    connect(this,&OpenGame::button1Slot, board,&GameScene::Getthenew1);
//    this->close();
// //  GameScene *board=new GameScene;
//   board->show();
// //-----------normal---------------
//    this->close();
//    gameScene->show();

};
void OpenGame::button2Slot(){
                   //  GameScene *gamescene=new GameScene;
    backGround1->stop();
                   // connect(this,&OpenGame::getthenew2,gamescene,&GameScene::Getthenew2);
    this->close();
                         // gamescene->show();
    MachineGameSelect *w=new MachineGameSelect;
    w->show();

};
void OpenGame::button3Slot(){
    GameScene *gamescene=new GameScene;
    backGround1->stop();
    connect(this,&OpenGame::getthenew3,gamescene,&GameScene::Getthenew3);
    this->close();
    gamescene->show();
};
