#ifndef TCPSERVERWORK_H_INCLUDED
#define TCPSERVERWORK_H_INCLUDED

/*tcpserverwork.h*/

#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h> //для IPPROTO_TCP
#include <unistd.h> //для close дескрипторов сокетов

#include <cstring> //для memset
#include <cstdio> //для sscanf()

#include "InputCalcFn.h" //для работы в методе Work()

class tcpserver //абстрактный класс для запуска tcp сервера. Работает с единственным SlaveSoket-ом. Имеет чисто виртуальные методы SetBufLength и Work
{
private:
    int MasterSocket; //Сокет, принимающий соединения
    struct sockaddr_in SockAddr; //содержит адрес и номер порта, к которым биндится MasterSoket
protected:
    int BufLength; //сколько байт принимаем из сокета
public:
    tcpserver(uint32_t NAdr, uint16_t NPort); //Передаем адрес и номер порта, к которым будем биндиться
    void tcplisten();
    void AcceptAndWork();
    void ShutDownClose();
    void WorkOnSlaveSocket(int SlaveSocket); //Вызывается внутри AcceptAndWork()
    virtual void SetBufLength()=0; //Эти 2 чисто виртуальные функции будут определяться в классе-потомке. Таким образом, мы отделяем работу с полученными данными от работы сервера по их приему.
    virtual void Work(char *)=0;
};

class tcpserverwork: public tcpserver //класс, где реализованы методы по работе с данными.
{
public:
    tcpserverwork(uint32_t NAdr, uint16_t NPort);
    virtual void SetBufLength(); //Устанавливаем число байт, которые хотим принять
    virtual void Work(char *Buf);
};

#endif // TCPSERVERWORK_H_INCLUDED
