//
// Created by xsl on 18-7-8.
//

#ifndef HELLOWORLD_EPOOLSERVER_H
#define HELLOWORLD_EPOOLSERVER_H

#include "TTcpBase.h"

class TEPollServer : public TTcpBase
{
public:
    TEPollServer();
    TEPollServer(int fds, uint16_t port, char* addr);
    ~TEPollServer();
private:
public:
    void Start();
};


#endif //HELLOWORLD_EPOOLSERVER_H
