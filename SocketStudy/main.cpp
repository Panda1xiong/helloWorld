//
// Created by xsl on 7/6/18.
//

#include <cstdint>
#include "TServer.h"
#include "TEPollServer.h"


int main(int argc, char** argv)
{
//    TTcpBase* tcpServer = new TServer();
//    tcpServer->Start();
//    delete (tcpServer);

    TTcpBase* tcpEPServer = new TEPollServer();
    tcpEPServer->Start();
    delete (tcpEPServer);

    return 0;
}