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

TServer::TServer()
{
}

TServer::~TServer()
{

}

void TServer::Start()
{
    int sockfd;
    if (-1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)))
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

    if (-1 == bind(sockfd,(struct sockaddr*)&s_addr, len))
    {
        cout << "error in bind:" << strerror(errno) << endl;
    }

    if (-1 == listen(sockfd, 10))
    {
        cout << "error in listen:" << strerror(errno) << endl;
    }

    fd_set fdSet;
    struct timeval tv;
    char buf[10];

    vector<int> vec_fd;
    vector<int>::iterator fd_begin;
    int maxfd = sockfd;


    while (true)
    {
        FD_ZERO(&fdSet);
        FD_SET(sockfd,&fdSet);
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
                if (FD_ISSET(sockfd,&fdSet))
                {
                    memset(&c_addr,0, len);
                    socklen_t slen = len;
                    int currentfd = accept(sockfd, (struct sockaddr*)&c_addr, &slen);
                    if (-1!=currentfd)
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
                                } else if (readLen <= 0)
                                {
                                    FD_CLR(*fd_begin, &fdSet);
                                    vec_fd.erase(fd_begin);
                                    break;
                                }
                            }
                        }
                    }

                }

                break;

        }

    }

}
