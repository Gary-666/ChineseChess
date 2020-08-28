#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include<QPainter>
#include<QMovie>
#include<QResizeEvent>
#include"Stone.h"
#include<QMouseEvent>
#include<QVector>
#include "Step.h"
#include <QPushButton>
#include <QMessageBox>
#include<QSound>
#include"WinGame.h"
//#include"OpenGame.h"
#define GRIDCOUNT1 11   //棋盘竖向均分
#define GRIDCOUNT2 14   //棋盘横向均分
class Board : public QWidget
{
    Q_OBJECT

public:
    Board(QWidget *parent = nullptr);
    //~Board();
    //按钮
//    QPushButton *backButton;  //悔棋
//    QPushButton *aboutButton;  //关于
//    QPushButton *returnButton;  //返回
//    void setButton();
    //------------------画基本背景-----------------
    //供给外界调用，改变内部背景图片
    void ChangeBGImage(const QString filename);
    //改变线的属性值
    void ChangeLine(const QColor color,const Qt::PenStyle style, const int width);
    void PaintChessBoard();
    void PaintInitPosition(QPainter &painter, int row, int col);
    void PaintInitPosition(QPainter &painter);
    //QPoint center(int row, int col);

    //-------------------绘制棋子----------------
    void PaintChess(int id);
    void PaintRedOrBlack(bool side); //绘制哪一方走棋
    //void mouseMoveEvent(QMouseEvent *e);

    void InitStonePosition();//初始化棋子的位子
    bool GetRowCol(QPoint pt, int &row, int &col);
    QPoint CoordinateToPixel1(int x, int y); //棋盘坐标转化为像素坐标(此为直接找到的矩形图像左上角点坐标）
    QPoint CoordinateToPixel2(int x,int y);  //棋盘坐标转化为像素坐标（此为图形所在中心点坐标）
    int CRow(int x);//棋盘横转换为横坐标
    int CCol(int y);//棋盘纵坐标转换为纵坐标
    void Init(bool beRedSide);//初始化棋子的方位,红黑方位
    //void init(bool beside);
    //bool isBottomSide(int moveid);  //判断谁在下方
    Stone _stone[32]; //棋盘共有32个棋子
    int r;  //棋子横向距离
    int d;  //棋子纵向距离
    int selectid;  //棋子是否被选中的标志，如果之前没有被选中，返回-1;
    bool beRedTurn;  //红黑双方交流
    bool beSide; //判断方位
    bool isBottomSide(int moveid);//判断棋子所在位置情况

    void Clear();//清空棋局

    //-----------------------走棋--------------------
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放时有效
    int PositionId(int row, int col);//返回一个位置上的棋子的ID， 如果该位置上没有棋子，返回-1
    void TrySelectedStone(int clicked);  //选择棋子
    void TryMoveStone(int clicked, int row, int col);  //试着移动
    virtual void Click(int id,int row, int col);     //点击棋子，获取其信息
    void MoveStone(int moveid,int row, int col);  //移动棋子
    void MoveStone(int moveid,int killid, int row, int col); //重载移动棋子
    int GetStoneCountAtLine(int row1,int col1,int row2,int col2);//判断两个象棋之间是否存在象棋;
    void KillStone(int killid);  //杀死棋子
    void ReliveStone(int reliveid); //复活棋子
    bool sameColor(int killid, int moveid); //判别棋子，避免自己吃自己

    bool BasicJiang(int moveid,int row, int col, int killid);
    bool CanMove(int target_id,int row, int col, int killid);
    bool CanMoveJiang(int target_id,int row, int col, int killid);
    bool CanMoveShi(int target_id,int row, int col, int killid);
    bool CanMoveXiang(int target_id,int row, int col, int killid);
    bool CanMoveMa(int target_id,int row, int col, int killid);
    bool CanMoveChe(int target_id,int row, int col, int killid);
    bool CanMovePao(int target_id,int row, int col, int killid);
    bool CanMoveBing(int target_id,int row, int col, int killid);

    //--------------悔棋-----------------------
        QVector<Step*> _step;
        void saveStep(int moveid,int killid, int row, int col, QVector<Step*>&steps);
        void Backone();
        void back(Step*step);
        virtual void back();
//-----------------音效-------------------
  //QSound *Move=new QSound(":/Music/Move.wav");//走棋



    //供给外界调用，改变内部象棋图片
    /*void ChangeBCImage(const QString che,const QString ma,const QString pao,const QString bing,const QString xiang,const QString shi,const QString jiang);
    void ChangeRCImage(const QString rche,const QString rma,const QString rpao, const QString rbing, const QString rxiang, const QString rshi,const QString rjiang);
    */
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent *);
private:
    QString bgFilename;
   /* QString che,ma,pao,bing,xiang,shi,jiang;
    QString rche,rma,rpao,rbing,rxiang,rshi,rjiang;
    */
    QColor lineColor;
    Qt::PenStyle lineStyle;
    int lineWidth;

    int gridWidth,gridHeight,startX,startY;//格子宽高，画线起始点
    QPixmap *pix;
public slots:
   // void slotBack();
//    void slotAbout();
//    void slotReturn();
    void slotBack();
    //void slotMove();
};
#endif // CHESS_H
