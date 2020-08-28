#ifndef MACHINEGAMESELECT_H
#define MACHINEGAMESELECT_H

#include <QWidget>
#include<QSound>
#include<QMessageBox>
#include"MachineGame.h"
namespace Ui {
class MachineGameSelect;
}

class MachineGameSelect : public QWidget
{
    Q_OBJECT

public:
    explicit MachineGameSelect(QWidget *parent = nullptr);
    ~MachineGameSelect();
   //--------event-------
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    double gridWidth;
    double gridHeight;
    QSound *backGround1=new QSound(":/Music/BG1.wav",this);

signals:
     void new1();
     void new2();
     void new3();
public slots:
    void easySlot();
    void commonSlot();
    void difficultSlot();
private:


private:
    Ui::MachineGameSelect *ui;
};

#endif // MACHINEGAMESELECT_H
