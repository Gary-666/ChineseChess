#include "Board.h"
#include<QPainter>
#include"OpenGame.h"
#include <QSound>
Board::Board(QWidget *parent)
    : QWidget(parent)
{
    bgFilename.clear();
    bgFilename=":/img/b02.jpg" ;
    lineColor=Qt::black;
    lineStyle=Qt::SolidLine;
    lineWidth=2;
    setWindowTitle("中国象棋");
    setMinimumSize(655,506);
//    BG2->setLoops(-1);
//    BG2->play();
 //   connect(this,&Board::KillStone,this,&Board::slotMove);
    //connect(aboutButton,SIGNAL(clicked(bool)),this,SLOT(aboutSLot));
    selectid=-1; //默认棋子未被选中
    beRedTurn=true;   //红棋先走
    Init(true);

}

/*Board::~Board()
{
}*/

//----------------events-----------------------------
void Board::paintEvent(QPaintEvent *){

    PaintChessBoard();
    //setButton();
    PaintRedOrBlack(beRedTurn);
    if(_stone[4]._dead||_stone[20]._dead)
    {
        this->close();
        WinGame *win=new WinGame(_stone[4]._dead?1:0);
        win->show();
    }
    for(int i=0;i<32;i++)
    {
        PaintChess(i);
    }


}
void Board::resizeEvent(QResizeEvent *event){
    gridWidth=event->size().width()/GRIDCOUNT2;
    gridHeight=event->size().height()/GRIDCOUNT1;
    startX=gridWidth;
    startY=gridHeight;
    r=gridWidth/2;
    d=gridHeight/2;
//    qDebug()<<"old:"<<event->oldSize();
//    qDebug()<<"new:"<<event->size();
}



void Board::mouseReleaseEvent(QMouseEvent *ev)
{
     int row=0, col=0; //判断这个行列值上面有没有棋子
    QPoint pt=ev->pos();//将PT转化为象棋的行列值
    bool bRet=GetRowCol(pt,row,col);
    if(bRet==false)
        return;
    int clickid=-1;
    clickid=PositionId(row,col);
    Click(clickid,row,col);
}



//-----------------end event-------------------------------



//----------------function---------------------------------------
//private----------
//void Board::setButton()
//{
//    aboutButton=new QPushButton(this);
//    QFont font("华文行楷");

//    //按钮样式
//    setStyleSheet("QPushButton"
//    "{"
//    "	color: black;"
//    "	background-color: #c0c1bb;"
//    "	border: none;"
//    "	border-radius: 10px;"
//    "}");
//    QString style="QPushButton:hover {"
//    "	color: black;"
//    "	background-color: #b99b7f;"
//    "	border: none;\n"
//    "	border-radius: 10px;"
//    "}";

//    aboutButton->setStyleSheet(style);
//    backButton->setStyleSheet(style);
//    returnButton->setStyleSheet(style);

//    aboutButton->setText("关于");
//    aboutButton->setGeometry(10*gridWidth,2*gridHeight,2*gridWidth,2*gridHeight);





//}
void Board::Init(bool beRedSide){

    InitStonePosition();
    if(!beRedSide)
    {
        for(int i=0;i<32;i++)
        {
            _stone[i].Rotate();
        }
    }
    beSide=beRedSide;  //根据此判断红旗在上还是在下
    update();
}




//public----------
void Board::ChangeBGImage(const QString filename){
    this->bgFilename=filename;
}
void Board::ChangeLine(const QColor color,
                       const Qt::PenStyle style, const int width)
{
  this->lineColor=color;
   this->lineStyle=style;
    this->lineWidth=width;
}
//初始化棋子
void Board::InitStonePosition()
{
    for(int i=0;i<32;i++)
    {
        _stone[i].InitChessmanMessage(i);
    }
}
void Board::PaintChessBoard()
{
        QPainter painter(this);
    //画背景
        QRect rec(QPoint(0,0),QPoint(this->width(),this->height()));
       // rec.setTopLeft(QPoint(0,0));
       // rec.setBottomRight(QPoint(this->width(),this->height()));
        QPixmap pix(bgFilename);
        //pix.load(":/img/b03.jpg" );
        painter.drawPixmap(rec,pix);
       // QRect r(QPoint(start))
    //画线
        QPen pen1;
        pen1.setColor(lineColor);
        pen1.setStyle(lineStyle);
        pen1.setWidth(lineWidth);

        QPen pen2;
        pen2.setColor(lineColor);
        pen2.setStyle(lineStyle);
        pen2.setWidth(5);




        //10条横线
        for(int i=0;i<10;i++)
           { if(i==0||i==9)
            {
                painter.setPen(pen2);
                painter.drawLine(startX,startY+i*gridHeight,9*gridWidth,startY+i*gridHeight);
            }
            else
               {
                 painter.setPen(pen1);
                painter.drawLine(startX,startY+i*gridHeight,9*gridWidth,startY+i*gridHeight);

            }}//9条竖线
        for(int i=0;i<9;i++)
         {   if(i==0||i==8)
             {
                painter.setPen(pen2);
                painter.drawLine(startX+i*gridWidth,startY,startX+i*gridWidth,startY+9*gridHeight);

            }
              else
             { painter.setPen(pen1);
               painter.drawLine(startX+i*gridWidth,startY,startX+i*gridWidth,startY+4*gridHeight);
               painter.drawLine(startX+i*gridWidth,startY+5*gridHeight,startX+i*gridWidth,startY+9*gridHeight);
             }
          }
        //九宫格
         painter.setPen(pen1);
         painter.drawLine(startX+3*gridWidth,startY,startX+5*gridWidth,startY+2*gridHeight);
         painter.drawLine(startX+5*gridWidth,startY,startX+3*gridWidth,startY+2*gridHeight);
         painter.drawLine(startX+5*gridWidth,startY+7*gridHeight,startX+3*gridWidth,startY+9*gridHeight);
         painter.drawLine(startX+3*gridWidth,startY+7*gridHeight,startX+5*gridWidth,startY+9*gridHeight);
         //楚河汉界
         painter.setFont(QFont("华文行楷",r,1000));
         QRect rect1(2*gridWidth,5*gridHeight,gridWidth,gridHeight);
         QRect rect2(3*gridWidth,5*gridHeight,gridWidth,gridHeight);
         QRect rect3(6*gridWidth,5*gridHeight,gridWidth,gridHeight);
         QRect rect4(7*gridWidth,5*gridHeight,gridWidth,gridHeight);
         painter.drawText(rect1,"楚",QTextOption(Qt::AlignCenter));
         painter.drawText(rect2,"河",QTextOption(Qt::AlignCenter));
         painter.drawText(rect3,"汉",QTextOption(Qt::AlignCenter));
         painter.drawText(rect4,"界",QTextOption(Qt::AlignCenter));
         //画点位
         PaintInitPosition(painter);
         painter.end();

}
void Board::PaintInitPosition(QPainter &painter, int row, int col)
{
    QPoint pt=CoordinateToPixel2(row,col);
    QPoint off=QPoint(r/6,d/6);

    int len1=r/3,len2=d/3;
    QPoint ptStart;
    QPoint ptEnd;

    if(row!=0)
    {
        //左上角
        ptStart=QPoint(pt.x()-off.x(),pt.y()-off.y());
        ptEnd=ptStart+QPoint(-len1,0);
        painter.drawLine(ptStart,ptEnd);
        ptEnd=ptStart+QPoint(0,-len2);
        painter.drawLine(ptStart,ptEnd);
        //左下角
        ptStart=QPoint(pt.x()-off.x(),pt.y()+off.y());
        ptEnd=ptStart+QPoint(-len1,0);
        painter.drawLine(ptStart,ptEnd);
        ptEnd=ptStart+QPoint(0,len2);
        painter.drawLine(ptStart,ptEnd);
    }
    if(row!=8)
    {
        //右上角
        ptStart=QPoint(pt.x()+off.x(),pt.y()-off.y());
        ptEnd=ptStart+QPoint(len1,0);
        painter.drawLine(ptStart,ptEnd);
        ptEnd=ptStart+QPoint(0,-len2);
        painter.drawLine(ptStart,ptEnd);
        //右下角
        ptStart=QPoint(pt.x()+off.x(),pt.y()+off.y());
        ptEnd=ptStart+QPoint(0,len2);
        painter.drawLine(ptStart,ptEnd);
        ptEnd=ptStart+QPoint(len1,0);
        painter.drawLine(ptStart,ptEnd);
    }
//    painter.end();
}

void Board::PaintInitPosition(QPainter &painter)
{
    PaintInitPosition(painter,0,3);
    PaintInitPosition(painter,2,3);
    PaintInitPosition(painter,4,3);
    PaintInitPosition(painter,6,3);
    PaintInitPosition(painter,8,3);


    PaintInitPosition(painter,1,2);
    PaintInitPosition(painter,7,2);

    PaintInitPosition(painter,0,6);
    PaintInitPosition(painter,2,6);
    PaintInitPosition(painter,4,6);
    PaintInitPosition(painter,6,6);
    PaintInitPosition(painter,8,6);

    PaintInitPosition(painter,1,7);
    PaintInitPosition(painter,7,7);
}
//画棋子
void Board::PaintChess(int id)
{

    QPainter painter(this);
    if(_stone[id]._dead)
     {
         return;
     }
    painter.drawPixmap(CRow(_stone[id]._row),CCol(_stone[id]._col),gridWidth,gridHeight, _stone[id].GetChessmanType());
  //painter.drawImage(CoordinateToPixel(_stone[2]._row, _stone[2]._col),_stone[2].GetChessmanType());


    if(id==selectid)
    {
        QPen pen;
        pen.setColor(Qt::green);
        pen.setWidth(3);
        painter.setPen(pen);
        QPoint point1=CoordinateToPixel1(_stone[id]._row,_stone[id]._col);
        QPoint point2;
        point2.rx()=point1.x()+2*r;
        point2.ry()=point1.y()+2*d;
        painter.drawRect(QRect(point1,point2));
    }
    painter.end();
}
//判断轮到哪一方走棋？
void Board::PaintRedOrBlack(bool side)
{
    QPainter painter(this);
    painter.setFont(QFont("华文行楷",1.5*r,800));

    if(side)
     {
        //红棋走
//        QPen pen1;
//        pen1.setColor(lineColor);
//        pen1.setStyle(lineStyle);
//        pen1.setWidth(lineWidth);
//        painter.setPen(pen1);
//        painter.setBrush(Qt::red);
//        painter.drawEllipse(QPoint(12*gridWidth,3*gridHeight),gridWidth,gridHeight);
        painter.setPen("red");
          QRect rect(9*gridWidth,7*gridHeight,2*gridWidth,4*gridHeight);
        painter.drawText(rect,"红方",QTextOption(Qt::AlignCenter));
    }
    else
    {
        //黑棋走
        QRect rect(9*gridWidth,gridHeight,2*gridWidth,4*gridHeight);
          painter.drawText(rect,"黑方",QTextOption(Qt::AlignCenter));
//        painter.setBrush(Qt::black);
//        painter.drawEllipse(QPoint(12*gridWidth,3*gridHeight),gridWidth,gridHeight);
    }
    painter.end();
}
//将象棋坐标转化为像素坐标
QPoint Board::CoordinateToPixel1(int x, int y)
{
    QPoint c;
    c.rx()=startX-r+x*2*r;
    c.ry()=startY-d+y*2*d;
    return c;
}
QPoint Board::CoordinateToPixel2(int x, int y)
{
    QPoint c;
    c.rx()=(x+1)*r*2;
    c.ry()=(y+1)*d*2;
    return c;
}
//由于用到了QPixmap，分开求下~
int Board::CRow(int x)
{
    int row=startX-r+x*2*r;
    return row;
}
int Board::CCol(int y)
{
    int col=startY-d+y*2*d;
    return col;
}
//判断是否选中一枚棋子,将像素坐标转化为象棋坐标。
bool Board::GetRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<=8;row++)
    {
        for(col=0;col<=9;col++)
        {
            QPoint c=CoordinateToPixel2(row,col);
            int dx=c.x()-pt.x();
            int dy=c.y()-pt.y();
            int dist=dx*dx+dy*dy;
            if(dist<r*r)
                 return true;
        }
    }
    return false;
}
//返回一个位置上棋子的id，如果该位置上没有棋子，返回-1
int Board::PositionId(int row, int col)
{
    for(int i=0;i<32;i++)
    {
        if((_stone[i]._row==row)&&(_stone[i]._col==col)&&(!_stone[i]._dead))
        {
            return i;
        }

    }
    return -1;
}

void Board::TryMoveStone(int clicked, int row, int col)
{
       if(CanMove(selectid,row,col,clicked))
       {if(clicked!=-1)
           {
               _stone[clicked]._dead=true;
           }
           else
           {
               TrySelectedStone(clicked);
           }
           MoveStone(selectid,clicked,row,col);  //此处有一次交换
            update();

           selectid=-1;

       }
}
//移动棋子
void Board::MoveStone(int moveid, int row, int col)
{
    _stone[moveid]._row=row;
    _stone[moveid]._col=col;
     //Move->play();
    beRedTurn=!beRedTurn;  //红黑方交换
}
void Board::MoveStone(int moveid,int killed, int row, int col)
{
    saveStep(moveid,killed,row,col,_step);
    KillStone(killed);
    MoveStone(moveid,row,col);
}
//选择棋子，出现框框~
void Board::TrySelectedStone(int clickid)
{

    if(clickid!=-1)
    {
        if(beRedTurn==_stone[clickid]._type)
        {selectid=clickid;
        update();}
    }
}

void Board::Click(int id, int row, int col)
{
    if(this->selectid==-1)
    {
        TrySelectedStone(id);
    }
    else
    {
        TryMoveStone(id,row,col);
    }
}
//击杀棋子， 输入要杀死的棋子的ID
void Board::KillStone(int killid)
{
    if(_stone[killid]._dead==true)
    {
        return ;
    }
    _stone[killid]._dead=true;
}

//复活棋子，输入符合的棋子ID
void Board::ReliveStone(int reliveid)
{
    if(_stone[reliveid]._dead==false)
    {
        return;
    }
    _stone[reliveid]._dead=false;
}
//判断棋子的颜色
bool Board::sameColor(int killid, int moveid)
{
    if(killid==-1)
    {
        return false;
    }
    if(_stone[killid]._type==_stone[moveid]._type)
    {
        //颜色相同
        return true;
    }
    else
    {
        //颜色不同
        return false;
    }
}
bool Board::CanMove(int moveid, int row, int col, int killid)
{
    if(killid==-1)
    {}
    else
    {if(_stone[moveid]._type==_stone[killid]._type)
        {
            //换选择
            selectid=killid;
            update();
            return false;
        }
    }
    switch (_stone[moveid].type) {
    case Stone::JIANG:
        return CanMoveJiang(moveid,row,col,killid);
        break;
    case Stone::SHI:
        return CanMoveShi(moveid,row,col,killid);
        break;
    case Stone::XIANG:
        return CanMoveXiang(moveid,row,col,killid);
        break;
    case Stone::MA:
        return CanMoveMa(moveid,row,col,killid);
        break;
    case Stone::CHE:
        return CanMoveChe(moveid,row,col,killid);
        break;
    case Stone::PAO:
        return CanMovePao(moveid,row,col,killid);
        break;
    case Stone::BING:
        return CanMoveBing(moveid,row,col,killid);
        break;
    }
    return true;
}
bool Board::CanMoveJiang(int moveid, int row, int col, int killid)
{
    int row1=_stone[moveid]._row;
    int col1=_stone[moveid]._col;
    int minCol=_stone[4]._col;
    int maxCol=_stone[20]._col;
    int sum=0;//位置和
    for(int i=minCol+1;i<maxCol;i++)
    {
       if( PositionId(row,i)!=-1)
          sum++;
    };

    //else return BasicJiang(moveid,row,col,killid);
    if(_stone[4]._row==_stone[20]._row)
    {int r=GetStoneCountAtLine(row1,col1,row,col);
        if(r==0&&killid!=-1&&sum==0&&row1==row)
        {
            return true;
        }
        else
        {
          return  BasicJiang(moveid,row,col,killid);
        }
    }
    else
    {
       return BasicJiang(moveid,row,col,killid);
    }
}
bool Board::BasicJiang(int moveid, int row, int col, int killid)
{
    //首先，目标必须在九宫格  其次移动的步长在一格之内
    if(isBottomSide(moveid)) //下方棋子
    {
        if(col<7)
        {
            return false;
        }
    }
    else //上方棋子
    {
        if(col>2)
        {
            return false;
        }
    }
    if(row<3||row>5)
    {
        return false;
    }
    int dr=_stone[moveid]._row-row;
    int dc=_stone[moveid]._col-col;

    int jiang_d=abs(dr)*10+abs(dc);
    if(jiang_d==1||jiang_d==10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::CanMoveShi(int moveid, int row, int col, int killid)
{
    //士只能在九宫格内
    if(isBottomSide(moveid))//下方棋子
    {
        if(col<7)
        {
            return false;
        }
    }
    else  //上方棋子
    {
        if(col>2)
        {
            return false;
        }
    }
    if(row<3||row>5)
    {
        return false;
    }
    //士只能走对角线
    int dr=_stone[moveid]._row-row;
    int dc=_stone[moveid]._col-col;

    int shi_d=abs(dr)*10+abs(dc);
    if(shi_d==11)
    {
        return true;
    }
    return false;
}
bool Board::CanMoveXiang(int moveid, int row, int col, int killid)
{
    //象走田，同时需要考虑象眼是否被卡
    //获取当前棋子的行列值
    int rowl=_stone[moveid]._row;
    int coll=_stone[moveid]._col;
    //获取关系值 象的差值为22
    int dr=_stone[moveid]._row-row;
    int dc=_stone[moveid]._col-col;

    int xiang_d=abs(dr)*10+abs(dc);
    if(xiang_d!=22)
    {
        return false;
    }
    //处理象眼
    int r_eye=(row+rowl)/2;
    int c_eye=(col+coll)/2;
    if(PositionId(r_eye,c_eye)!=-1)
    {
        //象眼位置上有棋子
        return false;
    }
    //判断象是否在期盼的下方，或上方，
    if(isBottomSide(moveid))  //下方棋子
    {
        if(col<5)
        {
            return false;
        }
    }
    else  //上方棋子
    {
        if(col>4)
        {
            return false;
        }
    }
   return true;
}
bool Board::CanMoveMa(int moveid, int row, int col, int killid)
{
    //马走日
    //马的马腿是否被压
    int rowl=_stone[moveid]._row;
    int coll=_stone[moveid]._col;

    int dr=_stone[moveid]._row-row;
    int dc=_stone[moveid]._col-col;
    int ma_d=abs(dr)*10+abs(dc);
    if(ma_d!=12&&ma_d!=21)
    {
        return false;
    }
    if(ma_d==12)
    {
        if(PositionId(rowl,(col+coll)/2)!=-1)
        {
            return false;
        }
    }
    else
    {
        if(PositionId((row+rowl)/2,coll)!=-1)
        {
            return false;
        }
    }

   return true;
}
bool Board::CanMovePao(int moveid, int row, int col, int killid)
{
    int rowl=_stone[moveid]._row;
    int coll=_stone[moveid]._col;
    int ret=GetStoneCountAtLine(row,col,rowl,coll);
    if(killid!=-1) //炮本次执行的是吃棋子
    {
        if(ret==1) return true;  //吃棋成功
    }
    else //不吃棋
    {
        if(ret==0) return true; //炮不吃子
    }
   return false;
}
bool Board::CanMoveBing(int moveid, int row, int col, int killid)
{
    //过河/不过河
    int rowl=_stone[moveid]._row;
    int coll=_stone[moveid]._col;
    int dr=_stone[moveid]._row-row;
    int dc=_stone[moveid]._col-col;
    int bing_d=abs(dr)*10+abs(dc);
    if(bing_d!=1&&bing_d!=10)
    {
        return false;
    }
    if(isBottomSide(moveid)) //下方棋子
    {
        if(col>coll)
        {
            return false; //不可后退
        }
        if(coll>=5&&col==coll)
        {
            return false;
        }
    }
    else//上方棋子
    {
        if(col<coll)
        {
            return false;
        }
        if(coll<=4&&coll==col)
        {
            return false;
        }
    }
    return true;
   return true;
}
bool Board::CanMoveChe(int moveid, int row, int col, int killid)
{
    //返回两点之间的象棋个数
    //若两点之间的象棋个数为0，则返回true,否则，返回false
    int rowl=_stone[moveid]._row;
    int coll=_stone[moveid]._col;
    int count=GetStoneCountAtLine(rowl,coll,row,col);
    if(count==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//判断位置上下方~
bool Board::isBottomSide(int moveid)
{
    if(beSide)  //黑上 红下的情况
    {
        if(_stone[moveid]._type==true)
        return true;
        else
        {
            return false;
        }
    }
    else  //黑下红上的情况
    {
       if(_stone[moveid]._type==true)
       {
           return  false;
       }
       else
       {
           return true;
       }
    }
}
//获取行列值
int Board::GetStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret=0;
    if(row1!=row2&&col1!=col2)
    {
        return -1;//不在一条直线上
    }
    if(row1==row2&&col1==col2)
    {
        return -1;   //本身就算一个点
    }
    if(row1==row2)
    {
        int min=col1<col2?col1:col2;
        int max=col1<col2?col2:col1;
        for(int col=min+1;col<max;++col)
        {
            if(PositionId(row1,col)!=-1)
            {
                ++ret;
            }
        }
    }
    else
    {
        int min=row1<row2?row1:row2;
        int max=row1<row2?row2:row1;
        for(int row=min+1;row<max;++row)
        {
            if(PositionId(row,col1)!=-1)
            {
                ++ret;
            }
        }
    }
    return ret;
}

void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step *> &steps)
{
    int row1=_stone[moveid]._row;
    int col1=_stone[moveid]._col;

    Step*step=new Step;
    step->ColFrom=col1;
    step->ColTo=col;
    step->RowTo=row;
    step->RowFrom=row1;
    step->_moveid=moveid;
    step->_killid=killid;

    steps.append(step);
}
void Board::Backone()
{
    if(this->_step.size()==0) return;

    Step*step=this->_step.last();
    _step.removeLast();
    back(step);

    update();
    delete step;
}
void Board::back(Step *step)
{
    ReliveStone(step->_killid);

   MoveStone(step->_moveid,step->RowFrom,step->ColFrom);
}
void Board::back()
{
    Backone();
}

//void Board::slotBack()
//{
//    back();
//}
//void Board::slotAbout()
//{
//    QMessageBox::information(this,"关于","     作者:  GaryMa    马嘉锐     \n"
//                                         "     学校： 华南理工大学 \n"
//                                         "     院系： 软件学院\n"
//                                          "    班级： 19级3班\n"
//                                          " 联系方式： QQ：1095012892\n"
//                                       "     Github： https://github.com/Gary-666");
//}
//void Board::slotReturn()
//{
//    int ret=QMessageBox::warning(this,"返回","确定要放弃当前棋局返回主界面？",
//                                 QMessageBox::No|QMessageBox::Yes);
//    if(ret==QMessageBox::Yes)
//    {
//        OpenGame *w=new OpenGame;
//        w->show();
//        this->close();
//    }
//}
/**void Board::ChangeBCImage(const QString che, const QString ma, const QString pao, const QString bing, const QString xiang, const QString shi, const QString jiang)
{
    this->che=che;
    this->ma=ma;
    this->pao=pao;
    this->bing=bing;
    this->shi=shi;
    this->jiang=jiang;
    this->xiang=xiang;
}
void Board::ChangeRCImage(const QString rche, const QString rma, const QString rpao, const QString rbing, const QString rxiang, const QString rshi, const QString rjiang)
{
    this->rche=rche;
    this->rma=rma;
    this->rpao=rpao;
    this->rbing=rbing;
    this->rshi=rshi;
    this->rjiang=rjiang;
    this->rxiang=rxiang;
}**/


//-----------------end function----------------------------------



//----------------slots--------------------------

void Board::slotBack()
{
    back();
}
//void Board::slotMove()
//{
//      QSound *Move=new QSound("./Music/Move.mav");
//     Move->play();
//}

//-----------------end slots---------------------
