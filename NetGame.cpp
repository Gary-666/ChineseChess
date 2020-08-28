#include "NetGame.h"
#include <QDebug>
NetGame::NetGame(bool server)
{
  _server=NULL;
  _socket=NULL;

  if(server)
  {
      _server=new QTcpServer(this);
      _server->listen(QHostAddress::Any,9999);

      connect(_server,SIGNAL(newConnection()),this,SLOT(slotConnection()));
  }
  else
  {
      _socket=new QTcpSocket(this);
      _socket->connectToHost(QHostAddress("192.168.43.118"),9999);

      connect(_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
  }
}
void NetGame::Click(int id, int row, int col)
{
    if(selectid==-1&&id!=-1)
    {
        if(_stone[id]._type!=beSide)
        {
            return;
        }
    }
    Board::Click(id,row,col);

    //发送给对方
    char get[4];
    get[0]=2;
    get[1]=8-row;
    get[2]=9-col;
    get[3]=id;

    _socket->write(get,4);


}
NetGame::~NetGame()
{

}
void NetGame::slotRecv()
{
    QByteArray ba=_socket->readAll();
    char cmd=ba[0];
    if(cmd==1)
    {
        //初始化
       char data=ba[1];
       Init(data==1);
    }
    else if(cmd==2)
    {
        int row=ba[1];
        int col=ba[2];
        int id=ba[3];
        Board::Click(id,row,col);
    }
}

void NetGame::slotConnection()
{
    if(_socket) return;

    _socket=_server->nextPendingConnection();
    connect(_socket,SIGNAL(readyRead()),this,SLOT(slotRecv()));
    //给对方发数据
    char get[2];
    get[0]=1;
    get[1]=0;

    _socket->write(get,2);

    Init(get[1]==0);
    //qDebug()<<"connect";
}
