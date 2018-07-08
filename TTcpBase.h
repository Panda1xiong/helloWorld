//
// Created by xsl on 18-7-8.
//

#ifndef HELLOWORLD_TTCPBASE_H
#define HELLOWORLD_TTCPBASE_H


class TTcpBase
{
public:
    TTcpBase();
    virtual ~TTcpBase();
private:
public:
    virtual void Start() = 0;
};


#endif //HELLOWORLD_TTCPBASE_H
