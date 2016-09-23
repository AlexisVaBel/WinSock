#include "socketservfct.hpp"
#include "winsoksserver.hpp"

using namespace std;
string BASE_SERVER("sserv");
string WIN_SERVER("winserv");
string LIN_SERVER("linserv");


SocketServFct::SocketServFct(){

}

SockServer *SocketServFct::getSocketServ(string strName,string strServ,string strPort){
    if(strName.compare(WIN_SERVER)==0)return new WinSoksServer(strServ,strPort);
    return nullptr;
}

