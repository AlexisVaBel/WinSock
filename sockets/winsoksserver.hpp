#ifndef WINSOKSSERVER_H
#define WINSOKSSERVER_H
#include "sockserver.hpp"
#include <vector>
#include <thread>

class WinSoksServer:public SockServer
{
public:    
    WinSoksServer(std::string strServ,std::string strPort);

    // SockServer interface
public:
    int bindDefAddr();
    void close();

    // SockServer interface
protected:
    unsigned int startListen(void* pParam);
    std::vector<std::thread> m_vctThr;

};

#endif // WINSOKSSERVER_H
