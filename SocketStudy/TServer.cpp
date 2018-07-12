//
// Created by xsl on 7/6/18.
//

#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include "TServer.h"

using namespace std;


TServer::TServer() : TTcpBase()
{

}

TServer::TServer(int fds, uint16_t port, char* addr) : TTcpBase(fds, port, addr)
{
}

TServer::~TServer()
{

}

void TServer::Start()
{


    fd_set fdSet;
    struct timeval tv;
    char buf[10];

    vector<int> vec_fd;
    vector<int>::iterator fd_begin;
    int maxfd = g_socket;

    struct sockaddr_in c_addr;

    int len = sizeof(struct sockaddr_in);

    while (true)
    {
        FD_ZERO(&fdSet);
        FD_SET(g_socket,&fdSet);
        for (fd_begin = vec_fd.begin(); fd_begin != vec_fd.end(); fd_begin++)
        {
            FD_SET(*fd_begin, &fdSet);
        }

        tv.tv_sec = 0;
        tv.tv_usec = 0;

        switch ((select(maxfd + 1, &fdSet, NULL, NULL, &tv)))
        {
            case -1:
                cout << "error in select:" << strerror(errno)<<endl;
                break;
            case 0:     //Time out & Nothing happennd0
                break;
            default:
                if (FD_ISSET(g_socket,&fdSet))
                {
                    memset(&c_addr,0, len);
                    socklen_t slen = len;
                    int currentfd = accept(g_socket, (struct sockaddr*)&c_addr, &slen);
                    if (0 < currentfd)
                    {
//                        FD_SET(currentfd, &fdSet);
                        vec_fd.push_back(currentfd);
                        if (maxfd < currentfd)
                        {
                            maxfd = currentfd;
                        }
                        cout << "an new connection comes" << endl;
                        cout << vec_fd.size() << endl;
                    }

                } else
                {
                    if (vec_fd.size() > 0)
                    {

                        for (fd_begin = vec_fd.begin(); fd_begin != vec_fd.end(); fd_begin++)
                        {
                            if (FD_ISSET(*fd_begin, &fdSet))
                            {
                                memset(buf, 0, sizeof(buf));
                                ssize_t readLen = read(*fd_begin, buf, sizeof(buf));
                                if (readLen > 0)
                                {
                                    cout << "recv:" << buf << endl;
                                } else if(-1 == readLen)
                                {
                                    FD_CLR(*fd_begin, &fdSet);
                                    vec_fd.erase(fd_begin);
                                    cout << "one client leave" << endl;
                                }
                            }
                        }
                    }

                }

                break;

        }

    }

}
