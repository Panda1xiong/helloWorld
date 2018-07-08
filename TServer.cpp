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
    char buf[1024];

    vector<int> vec_fd;
    int maxfd = sockfd;

    while (true)
    {
        FD_ZERO(&fdSet);
        FD_SET(sockfd,&fdSet);
        for (auto& a:vec_fd)
        {
            FD_SET(a, &fdSet);
        }

        tv.tv_sec = 10;
        tv.tv_usec = 1000;

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
                    }

                } else
                {
                    for (auto& a:vec_fd)
                    {
                        if (FD_ISSET(a, &fdSet))
                        {
                            memset(buf, 0, sizeof(buf));
                            read(a, buf, sizeof(buf));
                            cout << "recv:" << buf << endl;
                        }
                    }

                }

                break;

        }

    }

}
