//
// Created by xsl on 18-7-8.
//

#ifndef HELLOWORLD_TTCPBASE_H
#define HELLOWORLD_TTCPBASE_H

#include <cstdint>

class TTcpBase
{
public:
    TTcpBase();
    TTcpBase(int fds, uint16_t port, char* addr);
    virtual ~TTcpBase();

protected:
    int g_socket;
public:
    virtual void Start() = 0;
};


#endif //HELLOWORLD_TTCPBASE_H
