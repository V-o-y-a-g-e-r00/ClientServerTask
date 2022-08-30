/*main.cpp App2*/
#include <iostream>

#include "tcpserverwork.h"
int main()
{
    tcpserverwork server1(INADDR_ANY, 12345);
    server1.tcplisten();
    server1.AcceptAndWork();
    server1.ShutDownClose();

    return 0;
}
