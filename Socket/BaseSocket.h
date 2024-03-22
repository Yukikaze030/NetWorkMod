#ifndef BASESOCKET_H
#define BASESOCKET_H

#include "TypeRename.h"
#include <iostream>
#include <thread>
#include <memory>
#include <mutex>
#include <functional>
#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#elif _WIN32 || _WIN64
#include<WinSock2.h>
#include<WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")
#endif

class BaseSocket
{
public:
    BaseSocket();

    virtual ~BaseSocket() = 0;
    virtual bool Socketbind(std::string&,uint16 = 0) = 0;
    virtual void conncetToHost(std::string&,uint16 = 0) = 0;
    virtual void disconnectFromHost() = 0;
    virtual std::string error() = 0;
    virtual char* localAddress() = 0;
    virtual uint16 localPort() = 0;
    virtual void SetWorkMode(E_WorkMode = E_WorkMode::E_ReadWrite) = 0;
protected:
    std::shared_ptr<SOCKET> p_socket=nullptr;
    std::shared_ptr<sockaddr_in> p_mLocalSocketAddr = nullptr;
    std::string m_StrLocalAddr = "";
    uint16 p_mUsPort = 0;
    std::string m_StrError="";
    E_WorkMode m_EWorkMode = E_WorkMode::E_ReadWrite;
private:

};

#endif // BASESOCKET_H
