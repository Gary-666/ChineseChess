#include "MachineGame.h"
#include<QTimer>
#include"Board.h"

MachineGame::MachineGame(int level)
{
//   this->_level=4;
    this->_level=level;
}

MachineGame::~MachineGame()
{

}

void MachineGame::Click(int id, int row, int col)
{
   if(!(this->beRedTurn))
     {  return ;}
   Board::Click(id,row,col);//此处一开始无交换
    if(!(this->beRedTurn))
    {
        //启动一个0.1秒定时器，防止主进程被阻塞......刷新完后电脑再思考
        QTimer::singleShot(100,this,SLOT(comMove()));
    }
}


void MachineGame::comMove()
{
    Step* step=getBestMove();
    MoveStone(step->_moveid,step->_killid,step->RowTo,step->ColTo);//此处有交换
    delete step;
     update();
}
//------------------待优化----------------------------
void MachineGame::judgeOver(int id, int &eachRowBegin, int &eachRowEnd, int &eachColBegin, int &eachColEnd)
{
    eachRowBegin=(eachRowBegin<0)?_stone[id]._row:eachRowBegin;
    eachRowEnd=(eachRowEnd>8)?_stone[id]._row:eachRowEnd;

    eachColBegin=(eachColBegin<0)?_stone[id]._col:eachColBegin;
    eachColEnd=(eachColEnd>9)?_stone[id]._col:eachColEnd;
}
//--------------------待优化----------------------------
void MachineGame::getAllPossibleMove(QVector<Step *> &steps)
{
    int min=0;
    int max=0;
    if(this->beRedTurn) //红棋
    {
        min=16;
        max=32;
    }
    else //黑棋
    {
        min=0;
        max=16;
    }
    //-----------------行走代码优化--------------------------

    for(int i=min;i<max;++i)
    {
        if(_stone[i]._dead) continue;
        int eachRowBegin=0,eachRowEnd=8,eachColBegin=0,eachColEnd=9;
        //士优化
        if(_stone[i].type==Stone::SHI)
        {
            eachRowBegin=_stone[i]._row-1;
            eachRowEnd=_stone[i]._row+1;
            eachColBegin=_stone[i]._col-1;
            eachColEnd=_stone[i]._col+1;

            judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);

        }
        //将优化
        else if(_stone[i].type==Stone::JIANG)
        {
            eachRowBegin=_stone[i]._row-1;
            eachRowEnd=_stone[i]._row+1;
            eachColBegin=_stone[i]._col-1;
            eachColEnd=_stone[i]._col+1;
            judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
            int killID=((i-16)>0)?(i-16):(i+16);
            if(!_stone[killID]._dead)
            {
                if(this->CanMove(i,_stone[killID]._row,_stone[killID]._col,killID))
                {
                    this->saveStep(i,killID,_stone[killID]._row,_stone[killID]._col,steps);
                }
            }
        }
           //兵优化
            else if(_stone[i].type==Stone::BING)
            {
                if(_stone[i]._type){
                    if(_stone[i]._col>4)
                    {
                        eachColEnd=eachColBegin=_stone[i]._col-1;
                        eachRowBegin=eachColBegin=_stone[i]._row;
                        judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
                    }
                    else{
                        eachColBegin=eachColEnd=_stone[i]._col-1;
                        eachRowEnd=_stone[i]._row-1;
                        eachRowEnd=_stone[i]._row+1;
                        judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
                    }
                }
                else{
                    if(_stone[i]._col<5){
                        eachColEnd=eachColBegin=_stone[i]._col+1;
                        eachRowBegin=eachRowEnd=_stone[i]._row ;
                        judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
                    }
                    else{
                        eachColBegin=eachColEnd=_stone[i]._col+1;
                        eachRowBegin=_stone[i]._row-1;
                        eachRowEnd=_stone[i]._row+1;
                        judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
                    }
                }
            }
           //象优化
            else if(_stone[i].type==Stone::XIANG)
            {
                if(_stone[i]._type)
                {
                    eachColBegin=5;
                    eachColEnd=9;
                    judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
                }else
                {
                    eachColBegin=0;
                    eachColEnd=4;
                    judgeOver(i,eachRowBegin,eachRowEnd,eachColBegin,eachColEnd);
                }
            }
        for(int row=eachRowBegin;row<=eachRowEnd;++row)
        {
            for(int col=eachColBegin;col<=eachColEnd;++col)
            {
                int killid=this->PositionId(row,col);
                if(sameColor(killid,i)&&killid!=-1) continue;

                if(CanMove(i,row,col,killid))
                {
                    saveStep(i,killid,row,col,steps);
                }
            }
        }
    }
}

void MachineGame::fakeMove(Step*step)
{
      //step->_killid;
      KillStone(step->_killid);
      MoveStone(step->_moveid,step->RowTo,step->ColTo);
}

void MachineGame::unfakeMove(Step*step)
{
    ReliveStone(step->_killid);
    MoveStone(step->_moveid,step->RowFrom,step->ColFrom);
}
//评价局面分
int MachineGame::calcScore()
{
    int redTotalScore=0;
    int blackTotalScore=0;
    //enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    static int chessScore[]={1000,100,50,60,20,15,15};
    //黑棋分的总数-红棋分的总数
    for(int i=0;i<16;++i)
    {
        if(_stone[i]._dead)continue;
        blackTotalScore+=chessScore[_stone[i].type];
    }
    for(int i=16;i<32;++i)
    {
        if(_stone[i]._dead)continue;
        redTotalScore+=chessScore[_stone[i].type];
    }

    return (blackTotalScore-redTotalScore);
}
int MachineGame::GetMaxScore(int level,int cutMinScore)
{   if(level==0) return calcScore();
    //if(level==0)return calcScore();
    //看看有哪些步骤可以走，
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxScore=-100000;
    while(steps.count())
    //for(QVector<Step*>::iterator it=steps.begin();it!=steps.end();++it)
    {
        //Step* step=*it;
        Step*step=steps.back();
        steps.removeLast();   //从后往前删除
        fakeMove(step);
        int score=GetMinScore(level-1,maxScore);
        unfakeMove(step);

        if(score>=cutMinScore)
        {
            while(steps.count())
            {
                Step*step =steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if(score>maxScore)
        {
            maxScore=score;
        }
        //delete step;
    }
    return maxScore;
}
int MachineGame::GetMinScore(int level,int cutMaxScore)
{
    if(level==0) return calcScore();
    //if(level==0)return calcScore();
    //看看有哪些步骤可以走，
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int minScore=100000;
    while(steps.count())
    //for(QVector<Step*>::iterator it=steps.begin();it!=steps.end();++it)
    {
        //Step* step=*it;
        Step*step=steps.back();
        steps.removeLast();   //从后往前删除
        fakeMove(step);
        int score=GetMaxScore(level-1,minScore);
        unfakeMove(step);

        delete step;
        if(score<=cutMaxScore)
        {   while(steps.count())
            {
                Step*step =steps.back();
                steps.removeLast();
                delete step;
            }
            return  score;}
        if(score<minScore)
        {
            minScore=score;
        }
        //delete step;

    }
    return minScore;
}
Step* MachineGame::getBestMove()
{
    //看看有哪些步骤可以走，
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    //试着走一下，
    int maxScore=-100000;
    Step*ret=NULL;
    while(steps.count())
    //for(QVector<Step*>::iterator it=steps.begin();it!=steps.end();++it)
    {
        //Step* step=*it;
        Step*step=steps.back();
        steps.removeLast();   //从后往前删除
        fakeMove(step);
        int score=GetMinScore(_level-1,maxScore);
        unfakeMove(step);

        if(score>maxScore)
        {
            maxScore=score;
            if(ret) delete ret;
            ret=step;
        }
        else
        {
            delete step;
        }
    }
    // 评估走的结果， 取局面分最好的结果
    return ret;
}


/*oid MachineGame::GetNew1()
{
//    this->_level=2;
//    Init();
}*/
//void MachineGame::GetNew2()
//{
//    this->_level=3;
//}
//void MachineGame::GetNew3()
//{
//    this->_level=4;
//}

