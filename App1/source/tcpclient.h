#ifndef TCPCLIENT_H_INCLUDED
#define TCPCLIENT_H_INCLUDED
/* tcpclient.h*/
#include <iostream>

#include <sys/socket.h>
#include <netdb.h> //для IPP
#include <cstring> //для chBuf
#include <unistd.h> //для close дескрипторов сокетов и функции sleep()   (Доступ к POSIX API)

class tcpclient
{
private:
    int ClientSocket;
    struct sockaddr_in SockAddr;
    int retrcv=1; //0 - был разрыв соединения между сокетами. 1 -разрыва не было.
    bool IsConnected=false;

    char testBuf[1]={}; //с помощью него будем подтверждать соединение после каждой отправки

public:
    tcpclient(uint32_t NAdr, uint16_t NPort);
    void Reconnect();
    void Resend(char *NBuf, int len);
    void SendBuf(char *NBuf, int len);
    void tcpClose();
};

#endif // TCPCLIENT_H_INCLUDED
