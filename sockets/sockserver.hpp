#ifndef SOCKSERVER_H
#define SOCKSERVER_H

#include <string>

class SockServer
{
public:
    SockServer(std::string strServ,std::string strPort);
    virtual int bindDefAddr();
    virtual void close();
protected:
    virtual unsigned int startListen(void* pParam);
private:
    std::string m_strServ;
    std::string m_strPort;
    char *m_chServ;
    char *m_chPort;
};

#endif // SOCKSERVER_H
