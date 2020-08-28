#ifndef STONE_H
#define STONE_H

#include<QImage>
#include<QDebug>
#include<QPixmap>
class Stone
{
public:
    Stone();
    //~Stone();

    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    //棋子的横纵坐标（棋盘位置
    int _row;
    int _col;
    //棋子的类型
    int _id;
    //棋子是否存活
    bool _dead;
    //判断棋子为哪一方
    bool _type;
    TYPE type;

    QPixmap ma;
    QPixmap pao;
    QPixmap xiang;
    QPixmap shi;
    QPixmap jiang;
    QPixmap bing;
    QPixmap che;

    QPixmap rma;
    QPixmap rche;
    QPixmap rpao;
    QPixmap rbing;
    QPixmap rxiang;
    QPixmap rshi;
    QPixmap rjiang;

    void InitChessmanMessage(int i);//获取棋子信息
    QPixmap GetChessmanType();//获取目前棋子的类型（红或黑）
    void Rotate();//翻转棋盘

};



#endif // STONE_H
