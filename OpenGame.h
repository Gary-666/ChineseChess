#ifndef OPENGAME_H
#define OPENGAME_H

#include <QWidget>
#include<QMessageBox>
#include<QSound>
#include "ui_OpenGame.h"
namespace Ui {
class OpenGame;
}

class OpenGame : public QWidget
{
    Q_OBJECT

public:
    explicit OpenGame(QWidget *parent = nullptr);
    ~OpenGame();
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    double gridWidth;
    double gridHeight;
    QSound *backGround1=new QSound(":/Music/BG1.wav",this);
signals:
    void getthenew1();
    void getthenew2();
    void getthenew3();
private:
    Ui::OpenGame *ui;
    Ui_OpenGame *b1;
    OpenGame *a1;
public slots:
    void button1Slot();
    void button2Slot();
    void button3Slot();
};

#endif // OPENGAME_H
