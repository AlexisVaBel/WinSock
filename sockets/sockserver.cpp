#include "sockserver.hpp"
#include <iostream>
#include <string.h>



using namespace std;

SockServer::SockServer(string strServ, string strPort):m_strServ(strServ),m_strPort(strPort){
    cout<<m_strServ<<endl;
    cout<<m_strPort<<endl;
    cout<<"made server"<<endl;
}

int SockServer::bindDefAddr(){
    return 0;
}

void SockServer::close(){

}

unsigned int SockServer::startListen(void *pParam){
    return 0;
}

