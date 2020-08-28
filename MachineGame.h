#ifndef MACHINEGAME_H
#define MACHINEGAME_H
#include"Board.h"
class MachineGame :public Board
{
    Q_OBJECT
public:
   MachineGame(int _level);
   ~MachineGame();
   virtual void Click(int id, int row, int col);
   Step* getBestMove();
   //用一个数组保存步数
   void judgeOver(int id,int &eachRowBegin,int &eachRowEnd,int &eachColBegin,int&eachColEnd);
   void getAllPossibleMove(QVector<Step*>& steps);

   void fakeMove(Step*step);
   void unfakeMove(Step*step);
   int calcScore();
   int GetMinScore(int level,int cutMaxScore);
   int GetMaxScore(int level,int cutMinScore);

   int _level;
//public slots:
//   void GetNew1();
//   void GetNew2();
//   void GetNew3();
public slots:
   void comMove();
};

#endif // MACHINEGAME_H
