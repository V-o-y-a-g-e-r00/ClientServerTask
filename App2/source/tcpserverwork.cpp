/*tcpserverwork.cpp*/
#include "tcpserverwork.h"

tcpserver::tcpserver(uint32_t NAdr, uint16_t NPort) //Передаем адрес и номер порта, к которым будем биндиться
{
    MasterSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //создаем сокет. IPPROTO_TCP - протокол. Можно вместо него 0 поставить
    int optval =1; //для установки опций MasterSoket
    setsockopt(MasterSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    std::memset(&SockAddr, 0, sizeof(SockAddr)); //зануляем, т.к. в конце структуры должны быть нули
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_port=htons(NPort); //номер порта. htons сетевой порядок байт
    SockAddr.sin_addr.s_addr=htonl(NAdr); //биндимся на все сетевые интерфесы какие у нас есть (в частности, на все сетевые карты). INADDR_ANY=0.0.0.0 INADDR_LOOPBACK=127.0.0.1

    bind(MasterSocket, (struct sockaddr *)&SockAddr, sizeof(SockAddr)); //связываем сокет с адресом и портом
}
void tcpserver::tcplisten()
{
    listen(MasterSocket, SOMAXCONN); //SOMAXCONN максимальное число одновременно пытающихся подключиться
    std::cout<<"Server: listen"<<std::endl;
}
void tcpserver::AcceptAndWork()
{
    while(1)
    {
        int SlaveSocket=accept(MasterSocket, 0, 0);
        std::cout<<"Server: connection accepted!"<<std::endl;

        WorkOnSlaveSocket(SlaveSocket);

        shutdown(SlaveSocket, SHUT_RDWR);
        close(SlaveSocket);
        std::cout<<"Server: Socket closed!"<<std::endl;
    }
}
void tcpserver::ShutDownClose()
{
    shutdown(MasterSocket, SHUT_RDWR); //закрываем соединение
    close(MasterSocket); //закрываем дескриптор
}
void tcpserver::WorkOnSlaveSocket(int SlaveSocket)
{
    //Работаем с сокетом
    SetBufLength(); //устанавливаем размер буфера, в который мы будем принимать, в классе потомке
    char Buf[BufLength]={};     //В получаемой сумме число цифр не превышает 64. Поэтому 65 байт нам хватит
    char testBuf[1]={};

    int retrecv=recv(SlaveSocket, Buf, BufLength, MSG_WAITALL); //Получаем данные
    while(retrecv)
    {
        Work(Buf); //Тут работаем с полученными данными

        send(SlaveSocket, testBuf, 1, MSG_NOSIGNAL);  //посылаем клиенту 1 байт, чтобы он мог знать, что соединение ещё есть.
        retrecv = recv(SlaveSocket, Buf, BufLength, MSG_NOSIGNAL); //MSG_NOSIGNAL
    }
}
/*tcpserverwork*/
tcpserverwork::tcpserverwork(uint32_t NAdr, uint16_t NPort):tcpserver(NAdr, NPort) {}
void tcpserverwork::SetBufLength() //Устанавливаем число байт, которые хотим принять
{
    BufLength=4; //Сумма не может состоять из более, чем 3 цифр. Один символ отводим под '\0'
}
void tcpserverwork::Work(char *Buf)
{
    //std::cout<<"Server: Buf="<< Buf <<std::endl;
    //Тут будем читать из буфера и делать всю работу
    InputCalcFn::MultiplicityCheck(Buf);
}
