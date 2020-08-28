#ifndef STEP_H
#define STEP_H

#include<QObject>
class Step:public QObject
{
public:
    explicit Step(QObject *parent =0);
    ~Step();

    int _moveid;  //移动ID
    int _killid;  //目标ID
    int RowFrom;
    int ColFrom;
    int RowTo;
    int ColTo;
signals:

public slots:
};

#endif // STEP_H
