#include "Board.h"

#include <QApplication>
#include <QString>
#include <QtCore>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include "MachineGame.h"
#include "NetGame.h"
#include<QMessageBox>
#include "OpenGame.h"
#include "GameScene.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   OpenGame w;
    w.show();
     qDebug()<<QDir::currentPath();
    return a.exec();
}
