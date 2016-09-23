#ifndef SOCKETSERVFCT_H
#define SOCKETSERVFCT_H

#include <string>
#include "sockserver.hpp"



class SocketServFct
{
public:
    SocketServFct();
    SockServer *getSocketServ(std::string strName,std::string strServ,std::string strPort);
};

#endif // SOCKETSERVFCT_H
