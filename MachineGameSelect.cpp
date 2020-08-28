#include "MachineGameSelect.h"
#include "ui_machinegameselect.h"
#include"OpenGame.h"
#include<QResizeEvent>
#include<QPainter>
#include"GameScene.h"
#include"MachineGame.h"
#define GRIDCOUNT1 11   //棋盘竖向均分
#define GRIDCOUNT2 14   //棋盘横向均分
MachineGameSelect::MachineGameSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MachineGameSelect)
{
    ui->setupUi(this);
    this->setWindowTitle("中国象棋");
    this->setMinimumSize(655,506);
    backGround1->setLoops(-1);
    backGround1->play();

    connect(ui->Easy,&QPushButton::clicked,this,&MachineGameSelect::easySlot);
    connect(ui->Easy,&QPushButton::clicked,this,&MachineGameSelect::new1);

    connect(ui->Common,&QPushButton::clicked,this,&MachineGameSelect::commonSlot);
    connect(ui->Common,&QPushButton::clicked,this,&MachineGameSelect::new2);
    connect(ui->Difficult,&QPushButton::clicked,this,&MachineGameSelect::difficultSlot);
        connect(ui->Difficult,&QPushButton::clicked,this,&MachineGameSelect::new3);
    //connect(ui->)
}

MachineGameSelect::~MachineGameSelect()
{
    delete ui;
}


void MachineGameSelect::resizeEvent(QResizeEvent *event)
{
    gridWidth=event->size().width()/GRIDCOUNT2;
    gridHeight=event->size().height()/GRIDCOUNT1;
}
void MachineGameSelect::paintEvent(QPaintEvent *event)
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
void MachineGameSelect::easySlot()
{
    GameScene *gameScene=new GameScene;
    backGround1->stop();
    connect(this,&MachineGameSelect::new1,gameScene,&GameScene::Getthenew2);
    this->close();
    gameScene->show();


};
void MachineGameSelect::commonSlot()
{
    GameScene *gameScene=new GameScene;
    backGround1->stop();
    connect(this,&MachineGameSelect::new2,gameScene,&GameScene::Getthenew4);
    this->close();
    gameScene->show();
};
void MachineGameSelect::difficultSlot()
{
    GameScene *gameScene=new GameScene;
    backGround1->stop();
    connect(this,&MachineGameSelect::new3,gameScene,&GameScene::Getthenew5);
    this->close();
    gameScene->show();
};
