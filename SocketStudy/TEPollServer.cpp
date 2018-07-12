//
// Created by xsl on 18-7-8.
//

#include "TEPollServer.h"
#include <sys/epoll.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
    if (epfd < 0)
    {
        cout << "error in epoll_create:" << strerror(errno) << endl;
    }

    struct epoll_event event;
    memset(&event,0, sizeof(struct epoll_event));
    event.events = EPOLLIN | EPOLLET;
    event.data.fd = g_socket;
    if (-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, g_socket, &event))
    {
        cout << "error in epoll_ctl:" << strerror(errno) << endl;
    }
    int retNum;
    struct epoll_event events[10];
    struct sockaddr_in c_addr;
    char buffer[10];
    while (true)
    {
        switch ((retNum =epoll_wait(epfd, events, 10, 100)))
        {
            case -1:    //error
                perror("epoll_wait error");
                break;
            case 0:    //time out
                break;
            default:
                for (int i = 0; i < retNum; ++i)
                {
                    if (events[i].events & EPOLLIN)
                    {
                        if (events[i].data.fd == g_socket)
                        {
                            memset(&c_addr,0, sizeof(struct sockaddr_in));
                            socklen_t len = sizeof(struct sockaddr_in);
                            int currentSock = accept(g_socket,(struct sockaddr*)&c_addr,&len);
                            if (currentSock > 0)
                            {
                                memset(&event,0, sizeof(struct epoll_event));
                                event.events = EPOLLIN | EPOLLET;
                                event.data.fd = currentSock;
                                epoll_ctl(epfd, EPOLL_CTL_ADD, currentSock, &event);
                                cout << "an new client" << endl;
                            }

                        } else
                        {
                            memset(buffer, 0, sizeof(buffer));
                            int curfd = events[i].data.fd;
                            int readNum;
//                            while ((readNum =read(curfd, buffer, sizeof(buffer))) > 0 )   //阻塞读
                            while ((readNum = recv(curfd, buffer, sizeof(buffer), MSG_DONTWAIT)) > 0)   //非阻塞读
                            {
                                cout << "recv:" << buffer << endl;
                                memset(buffer, 0, sizeof(buffer));
                                if (readNum < sizeof(buffer))
                                {
                                    break;
                                }
                            }
//                            ssize_t readLen = read(curfd, buffer, sizeof(buffer));
//                            if (readLen > 0)
//                            {
//                                cout << "recv:" << buffer  << endl;
//                            }
//                            else if(readLen == -1)
//                            {
//                                epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
//                                cout << "some one leave" <<endl;
//                            }
                        }

                    }
                }
                break;
        }

    }
}
