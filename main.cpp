#include <sockets/socketservfct.hpp>
#include <iostream>
#include <stdio.h>

int main(int argc,char**argv){
    SockServer *serverS=nullptr;
    SocketServFct *servFactory=new SocketServFct();
//    std::cout<<argc<<" "<<argv<<std::endl;
//    printf("%s\n",argv[0]);
//    if(argc>=4){
//        serverS=servFactory->getSocketServ(argv[1],argv[2],argv[3]);
//    }else
        serverS=servFactory->getSocketServ("winserv","localhost","3033");
    if(serverS!=nullptr)
        return serverS->bindDefAddr();
    delete serverS;
    delete servFactory;
    return 1;
}
