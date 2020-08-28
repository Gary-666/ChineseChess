#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QWidget>
#include"Board.h"
#include"ui_GameScene.h"
#include"MachineGame.h"
#include"NetGame.h"
#include<QResizeEvent>
#include<QSound>
//#include<QMeiaPlayer>
namespace Ui {
class GameScene;
}

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);
    ~GameScene();
     void resizeEvent(QResizeEvent *);
     void paintEvent(QPaintEvent *event);
     void Init();
     bool a[5]={false,false,false,false,false};
     //---------双人对战--------------
     void Getthenew1();
     //----------人机对战选择-----------
     void Getthenew2();
     void Getthenew4();
     void Getthenew5();
     //----------联网对战----------------
     void Getthenew3();

     Board *board;
     MachineGame *machineGame;
     double gridWidth,gridHeight;
     //NetGame *netGame;
     //-------音效-----------
    // QSound *backGround1=new QSound(":/Music/FirstBG.wav",this);
 QSound *backGround2=new QSound(":/Music/BG2.wav");//BG音乐
private:
    Ui::GameScene *ui;

    Ui_GameScene *xi;
    GameScene *yi;

public slots:
    void slotAbout();
    void slotBack1();
    void slotBack2();
    void slotBack3();
    void slotReturn();
};

#endif // GAMESCENE_H
