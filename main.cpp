//
// Created by xsl on 7/6/18.
//

#include "TServer.h"


int main(int argc, char** argv)
{

    TTcpBase* tcpServer = new TServer();
    tcpServer->Start();
    delete (tcpServer);

    return 0;
}