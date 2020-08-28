#include "Stone.h"

Stone::Stone()
{
    che.load(":/img/black_che.png");
    ma.load(":/img/black_ma.png");
    pao.load(":/img/black_pao.png");
    bing.load(":/img/black_bing.png");
    xiang.load(":/img/black_xiang.png");
    shi.load(":/img/black_shi.png");
    jiang.load(":/img/black_jiang.png");

    rche.load(":/img/red_che.png");
    rma.load(":/img/red_ma.png");
    rshi.load(":/img/red_shi.png");
    rjiang.load(":/img/red_jiang.png");
    rbing.load(":/img/red_bing.png");
    rpao.load(":/img/red_pao.png");
    rxiang.load(":/img/red_xiang.png");
}

void Stone::InitChessmanMessage(int i)
{
    struct
    {
        int row,col;
        Stone::TYPE type;
    }pos[16]={
        //黑方棋子
    {0,0,Stone::CHE},
    {1,0,Stone::MA},
    {2,0,Stone::XIANG},
    {3,0,Stone::SHI},
    {4,0,Stone::JIANG},
    {5,0,Stone::SHI},
    {6,0,Stone::XIANG},
    {7,0,Stone::MA},
    {8,0,Stone::CHE},

    {1,2,Stone::PAO},
    {7,2,Stone::PAO},
    {0,3,Stone::BING},
    {2,3,Stone::BING},
    {4,3,Stone::BING},
    {6,3,Stone::BING},
    {8,3,Stone::BING},

    };
    this->_id=i;//棋子的类型
    this->_dead=false;//棋子死亡与否
    this->_type=(_id>=16);  //大于16的默认为红色棋子
    if(_id<16)//16个黑色棋子
    {
        this->_row=pos[_id].row;
        this->_col=pos[_id].col;
        this->type=pos[_id].type;
    }
    else //16个红色棋子
    {
        _row=8-pos[_id-16].row;
        _col=9-pos[_id-16].col;
        this->type=pos[_id-16].type;

    }
}

void Stone::Rotate()
{
    _col=9-_col;
    _row=8-_row;
}

//获得棋子的类型
QPixmap Stone::GetChessmanType()
{
    switch (this->type) {
     case CHE:
        if(_id<16) return che;
        else return rche;
     case MA:
        if(_id<16)return ma;
        else return rma;
     case XIANG:
        if(_id<16)return xiang;
        else return rxiang;
     case SHI:
        if(_id<16)return shi;
        else return rshi;
     case JIANG:
        if(_id<16)return jiang;
        else return rjiang;
     case PAO:
        if(_id<16)return pao;
        else return rpao;
     case BING:
        if(_id<16)return bing;
        else return rbing;
    }
}
