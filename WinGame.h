#ifndef WINGAME_H
#define WINGAME_H

#include <QWidget>
#include<QPainter>
class WinGame: public QWidget
{
    Q_OBJECT
public:
    WinGame(QWidget*parent=nullptr);
    WinGame(int i);
private:
    int color;
protected:
    void paintEvent(QPaintEvent *event) ;
};

#endif // WINGAME_H
