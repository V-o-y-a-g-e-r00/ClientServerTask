/* tcpclient.cpp*/
#include "tcpclient.h"

tcpclient::tcpclient(uint32_t NAdr, uint16_t NPort)
{
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_port=htons(NPort);
    SockAddr.sin_addr.s_addr=htonl(NAdr); //INADDR_LOOPBACK
}
void tcpclient::Reconnect()
{
    while(!IsConnected)
    {
        sleep(1);
     //   std::cout << "Client: Reconnect" << std::endl;
        shutdown(ClientSocket, SHUT_RDWR);
        close(ClientSocket);
        ClientSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        IsConnected=!(bool)connect(ClientSocket, (const sockaddr*)&SockAddr, sizeof(SockAddr));
    }
}
void tcpclient::Resend(char *NBuf, int len)
{
    while(!retrcv)
    {
        std::cout << "Client: sending to App2 failed! Resending..." << std::endl;
        shutdown(ClientSocket, SHUT_RDWR);
        close(ClientSocket);
        ClientSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        IsConnected=!(bool)connect(ClientSocket, (const sockaddr*)&SockAddr, sizeof(SockAddr));
	if(!IsConnected)
	{
        	Reconnect();
       		std::cout << "Client: the connection with App2 has been restored" << std::endl;
	}
        send(ClientSocket, NBuf, len, MSG_NOSIGNAL);
        retrcv=recv(ClientSocket, testBuf, 1, MSG_WAITALL); //проверяем доставку
        if(retrcv) std::cout << "Client: the data has been sent to App2" << std::endl;
    }
}
void tcpclient::SendBuf(char *NBuf, int len)
{
    if(!IsConnected)
    {
        ClientSocket=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        IsConnected=!(bool)connect(ClientSocket, (const sockaddr*)&SockAddr, sizeof(SockAddr));
        if(IsConnected) std::cout << "Client: connection established successfully!" << std::endl;
        else
	{
		std::cout << "Client: connection not established! Reconnecting..." << std::endl;
		Reconnect();
		std::cout << "Client: the connection with App2 has been restored" << std::endl;
	}
    }
    std::cout << "Client: sending to server" << std::endl;
    send(ClientSocket, NBuf, len, MSG_NOSIGNAL);
    retrcv=recv(ClientSocket, testBuf, 1, MSG_WAITALL); //проверяем доставку
    Resend(NBuf, len);
}
void tcpclient::tcpClose()
{
    shutdown(ClientSocket, SHUT_RDWR);
    close(ClientSocket);
}
