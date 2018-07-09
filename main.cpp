//
// Created by xsl on 7/6/18.
//

#include <cstdint>
#include "TServer.h"
#include "TEPollServer.h"


int main(int argc, char** argv)
{
    char addr[] = "127.0.0.1";
    TTcpBase* tcpServer = new TServer(20, 7000, addr);
    tcpServer->Start();
    delete (tcpServer);
//
//    TTcpBase* tcpEPServer = new TEPollServer();
//    tcpEPServer->Start();
//    delete (tcpEPServer);

    return 0;
}