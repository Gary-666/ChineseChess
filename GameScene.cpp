#include "GameScene.h"
#include "ui_GameScene.h"
#include "OpenGame.h"
#include "Board.h"
#include"MachineGame.h"
#include"NetGame.h"
#include<QDebug>
#include<QSound>
#define GRIDCOUNT1 11   //棋盘竖向均分
#define GRIDCOUNT2 14   //棋盘横向均分
GameScene::GameScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameScene)
{
    ui->setupUi(this);
    backGround2->setLoops(-1);
    backGround2->play();
// Init();
    //Init();
    //connect(ui->back,&QPushButton::clicked,this,&GameScene::slotBack);  由于各个所创建对象不同，因此切换位置
    connect(ui->return_2,&QPushButton::clicked,this,&GameScene::slotReturn);
    connect(ui->about,&QPushButton::clicked,this,&GameScene::slotAbout);
}

GameScene::~GameScene()
{    /*Init();*/
    delete ui;
}

//------------------function------------------------
void GameScene::Init()
{
     this->setWindowTitle("中国象棋");
    if(a[0])
        //申请棋盘类空间
    {board=new Board();
        //把棋盘显示在容器中
       // backGround->setLoops(-1);
        //backGround->play();
        ui->gridLayout_3->addWidget(board);}
    else if(a[1])
    {
       // machineGame->GetNew1();
        machineGame=new MachineGame(2);
        ui->gridLayout_3->addWidget(machineGame);}
    else if(a[3])
    {
        machineGame=new MachineGame(3);
        ui->gridLayout_3->addWidget(machineGame);
    }
    else if(a[4])
    {
        machineGame=new MachineGame(4);
        ui->gridLayout_3->addWidget(machineGame);
    }
    else if(a[2])
    {
        QMessageBox::StandardButton ret;
        ret=QMessageBox::question(NULL,"server or client","作为服务器启动");

        bool bServer=false;
        if(ret==QMessageBox::Yes)
        {
            bServer=true;
        }
        QMessageBox::information(this,"说明", "为保证用户之间PK的公平性，由此撤销悔棋功能~");
        NetGame *netGame=new NetGame(bServer);
        ui->back->hide();
        ui->gridLayout_3->addWidget(netGame);
    }
}
//------------------------------双人对战----------------------------
void GameScene::Getthenew1()
{
   // qDebug()<<"大哥，给力点啊！"<<endl;
    a[0]=true;
   Init();
    connect(ui->back,&QPushButton::clicked,this,&GameScene::slotBack1);
}

//---------------------人机对战---------------------------
void GameScene::Getthenew2()
{
    a[1]=true;
    Init();
    connect(ui->back,&QPushButton::clicked,this,&GameScene::slotBack2);
}
void GameScene::Getthenew4()
{
  a[3]=true;
  Init();
  connect(ui->back,&QPushButton::clicked,this,&GameScene::slotBack2);
}
void GameScene::Getthenew5()
{
  a[4]=true;
  Init();
  connect(ui->back,&QPushButton::clicked,this,&GameScene::slotBack2);
}



//-----------------------------联网对战----------------------------------------
void GameScene::Getthenew3()
{
    a[2]=true;
    Init();
    connect(ui->back,&QPushButton::clicked,this,&GameScene::slotBack3);
}
//--------------------end-----------------------------


//------------------events------------------------
void GameScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(),QPixmap(":/img/b22.png"));
    QFont font1("华文行楷",0.4*gridWidth,0.4*gridHeight);
    QFont font("华文行楷",gridWidth,gridHeight);
    painter.setFont(font);
    QRect rec1(6*gridWidth,1.5*gridHeight,1.5*gridWidth,2.5*gridHeight);
    QRect rec2(6*gridWidth,3.5*gridHeight,1.5*gridWidth,2.5*gridHeight);
    QRect rec3(6*gridWidth,5.5*gridHeight,1.5*gridWidth,2.5*gridHeight);
    QRect rec4(6*gridWidth,7.5*gridHeight,1.5*gridWidth,2.5*gridHeight);
    painter.drawText(rec1,"再",QTextOption(Qt::AlignCenter));
    painter.drawText(rec2,"来",QTextOption(Qt::AlignCenter));
    painter.drawText(rec3,"一",QTextOption(Qt::AlignCenter));
    painter.drawText(rec4,"局",QTextOption(Qt::AlignCenter));
    painter.end();

}
void GameScene::resizeEvent(QResizeEvent *event)
{
    gridWidth=event->size().width()/GRIDCOUNT2;
    gridHeight=event->size().height()/GRIDCOUNT1;
}
void GameScene::slotAbout()
{
    QMessageBox x;
    x.setWindowTitle("关于");
    x.setIconPixmap(QPixmap(":/img/b03.jpg"));
    x.exec();
}
void GameScene::slotReturn()
{
    int ret=QMessageBox::warning(this,"返回","确定要放弃当前棋局返回主界面？",
                                 QMessageBox::No|QMessageBox::Yes);
    if(ret==QMessageBox::Yes)
    {
      backGround2->stop();
    OpenGame *ai=new OpenGame(nullptr);
    ai->show();
    this->close();}
}
//--------------------end-----------------------------




//------------------slots------------------------
void GameScene::slotBack1()
{
   board->slotBack();
}
void GameScene::slotBack2()
{
    machineGame->Backone();
}
void GameScene::slotBack3()
{
    //netGame->back();
}


//--------------------end-----------------------------
