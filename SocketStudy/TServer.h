//
// Created by xsl on 7/6/18.
//

#ifndef HELLOWORLD_TSERVER_H
#define HELLOWORLD_TSERVER_H

#include "TTcpBase.h"

class TServer : public TTcpBase
{
public:
    TServer();
    TServer(int fds, uint16_t port, char* addr);
    ~TServer();
private:
public:
    void Start();
};


#endif //HELLOWORLD_TSERVER_H
