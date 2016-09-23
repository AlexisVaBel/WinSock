#include "winsoksserver.hpp"
#include <globals.h>


#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

WinSoksServer::WinSoksServer(string strServ, string strPort):SockServer(strServ,strPort){

}



int WinSoksServer::bindDefAddr(){
    cout<<"wsa"<<endl;
    WSADATA wsaData;
    int iResult;
    SOCKET ListenSocket=INVALID_SOCKET;
    SOCKET ClientSocket=INVALID_SOCKET;

    struct addrinfo *result=nullptr;
    struct addrinfo hints;

    //init socket
    cout<<"wsa startup"<<endl;
    iResult=WSAStartup(MAKEWORD(2,2),&wsaData);
    if(iResult!=0){
        std::cout<<"failed wsastartup "<<iResult<<std::endl;
        return 1;
    }
    ZeroMemory(&hints,sizeof(hints));   //clean struct, why?

    hints.ai_family     =AF_INET;
    hints.ai_socktype   =SOCK_STREAM;
    hints.ai_protocol   =IPPROTO_TCP;
    hints.ai_flags      =AI_PASSIVE;

    cout<<"get addr"<<endl;
    iResult=getaddrinfo(DEFAULT_TCPSERV,DEFAULT_TCPPORT,&hints,&result);

    if(iResult!=0){
        std::cout<<"getaddrinfo failed with error : "<<iResult<<std::endl;
        WSACleanup();
        return 1;
    }
    //create socket
    cout<<"make socket"<<endl;
    ListenSocket=socket(result->ai_family,result->ai_socktype,result->ai_protocol);
    if(ListenSocket==INVALID_SOCKET){
        std::cout<<"socket failed "<<WSAGetLastError()<<std::endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    //listen sokcet
    cout<<"bind socket"<<endl;
    iResult=bind(ListenSocket,result->ai_addr,(int)result->ai_addrlen);
    if(iResult==SOCKET_ERROR){
        std::cout<<"bind failed "<<iResult<<std::endl;
        return 1;
    }
    cout<<"listen socket"<<endl;
    freeaddrinfo(result);
    iResult=listen(ListenSocket,SOMAXCONN);
    if(iResult==SOCKET_ERROR){
        std::cout<<"listne failed withe error "<<iResult<<std::endl;
        closesocket(ListenSocket);
        WSACleanup();
    };
    //accept client
    cout<<"accept client socket"<<endl;    
    while(true){
        ClientSocket=accept(ListenSocket,nullptr,nullptr);

        if(ClientSocket==INVALID_SOCKET){
            std::cout<<"accept failed "<<WSAGetLastError();
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
        //*************************************************//
        //here will be threads, if i find how they are made((
        m_vctThr.push_back(thread(&WinSoksServer::startListen,this,&ClientSocket));
        //*************************************************//
    }
    //going away
    closesocket(ListenSocket);
    for(auto &t:m_vctThr){
        if(t.joinable()) t.join();
    }
    WSACleanup();
    return 0;
}

void WinSoksServer::close(){
}


unsigned int WinSoksServer::startListen(void *pParam){
    int iResult;
    int iSendResult;
    char sndbuf[DEFAULT_BUF_LEN];
    char recvbuf[DEFAULT_BUF_LEN];
    int recvbuflen=DEFAULT_BUF_LEN;
    SOCKET ClientSocket=*((SOCKET*)pParam);
    if(!ClientSocket)return -1;
    cout<<"receiving data"<<ClientSocket<<endl;
    //receive data
    do{
        sndbuf[0]='O';
        sndbuf[1]='U';
        sndbuf[2]='T';
        iResult=recv(ClientSocket,recvbuf,recvbuflen,0);
        if(iResult>0){
            std::cout<<"got bytes "<<iResult<<" "<<recvbuf<<std::endl;
            memcpy((sndbuf+3),recvbuf,iResult);
            iSendResult=send(ClientSocket,sndbuf,iResult+3,0);
            if(iSendResult==SOCKET_ERROR){
                std::cout<<"socket error "<<WSAGetLastError();
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            std::cout<<"Bytes send "<<iSendResult<<std::endl;
        }
        else
            if(iResult==0){
                std::cout<<"connection closing "<<std::endl;
            }
            else{
                std::cout<<"recv failed with err "<<WSAGetLastError()<<std::cout;
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
    }while(iResult>0);
    iResult=shutdown(ClientSocket,SD_SEND);
    if(iResult==SOCKET_ERROR){
        std::cout<<"shutdown failed "<<WSAGetLastError()<<std::endl;
        closesocket(ClientSocket);
        return 1;
    }
    return 0;
}
