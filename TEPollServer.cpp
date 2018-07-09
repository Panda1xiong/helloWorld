//
// Created by xsl on 18-7-8.
//

#include "TEPollServer.h"
#include <sys/epoll.h>
#include <cstring>
#include <iostream>

using namespace std;

TEPollServer::TEPollServer() : TTcpBase()
{

}

TEPollServer::TEPollServer(int fds, uint16_t port, char* addr) : TTcpBase(fds, port, addr)
{

}

TEPollServer::~TEPollServer()
{

}

void TEPollServer::Start()
{
    int epfd = epoll_create(10);
    if (-1 == epfd)
    {
        cout << "error in epoll_create:" << strerror(errno) << endl;
    }



}
