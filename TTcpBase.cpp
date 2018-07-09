//
// Created by xsl on 18-7-8.
//

#include <sys/socket.h>
#include <cstring>
#include <netinet/in.h>

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

#include "TTcpBase.h"
using namespace std;

TTcpBase::TTcpBase()
{
    if (-1 == (g_socket = socket(AF_INET, SOCK_STREAM, 0)))
    {
        cout << "error in socket:" << strerror(errno) << endl;
    }


    struct sockaddr_in s_addr,c_addr;
    memset(&s_addr,0, sizeof(struct sockaddr_in));

    int len = sizeof(struct sockaddr_in);


//    s_addr.sin_addr.s_addr = inet_addr("192.168.3.14");
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(6000);

    if (-1 == bind(g_socket,(struct sockaddr*)&s_addr, len))
    {
        cout << "error in bind:" << strerror(errno) << endl;
    }

    if (-1 == listen(g_socket, 10))
    {
        cout << "error in listen:" << strerror(errno) << endl;
    }
}

TTcpBase::TTcpBase(int fds, uint16_t port, char* addr)
{
    if (-1 == (g_socket = socket(AF_INET, SOCK_STREAM, 0)))
    {
        cout << "error in socket:" << strerror(errno) << endl;
    }


    struct sockaddr_in s_addr;
    memset(&s_addr,0, sizeof(struct sockaddr_in));

    int len = sizeof(struct sockaddr_in);


    s_addr.sin_addr.s_addr = inet_addr(addr);
//    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);

    if (-1 == bind(g_socket,(struct sockaddr*)&s_addr, len))
    {
        cout << "error in bind:" << strerror(errno) << endl;
    }

    if (-1 == listen(g_socket, fds))
    {
        cout << "error in listen:" << strerror(errno) << endl;
    }

}

TTcpBase::~TTcpBase()
{
    close(g_socket);
}

void TTcpBase::Start()
{

}
