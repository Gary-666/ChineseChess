#include "WinGame.h"

WinGame::WinGame(QWidget*parent) :QWidget(parent)
{

}
WinGame::WinGame(int i)
{
    this->resize(655,506);
    this->color=i;
}
void WinGame::paintEvent(QPaintEvent *event)
{
    QPainter *painter=new QPainter(this);
    if(this->color)
    {
        painter->setPen(Qt::red);
        this->setWindowTitle("红方胜出，黑方战败");
    }
    else
    {
        painter->setPen(Qt::black);
        this->setWindowTitle("黑方胜出，红方战败");
    }
    painter->setFont(QFont("华文行楷",100,200));
    QRect rect=QRect(QPoint(0,0),QPoint(this->width(),this->height()));
    painter->drawText(rect,"胜",QTextOption(Qt::AlignCenter));
    painter->end();
}
