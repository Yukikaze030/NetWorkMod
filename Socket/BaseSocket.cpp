#include "BaseSocket.h"

BaseSocket::BaseSocket()
{
    //声明调用不同的Winsock版本。例如MAKEWORD(2,2)就是调用2.2版，MAKEWORD(1,1)就是调用1.1版
    WORD sockVersion=MAKEWORD(2,2);
    WSADATA wsaData;//WSADATA结构体变量的地址值

    //int WSAStartup(WORD wVersionRequested, LPWSADATA lpWSAData);
    //成功时会返回0，失败时返回非零的错误代码值
    if(WSAStartup(sockVersion,&wsaData)!=0)
    {
        m_StrError = "WSAStartup() error!";
        std::cout<<m_StrError<<std::endl;
    }
}

BaseSocket::~BaseSocket()
{


}

std::string BaseSocket::error()
{
    return m_StrError;
}
