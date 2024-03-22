#include "UdpSocket.h"


UdpSocket::UdpSocket() : BaseSocket()
{
}

UdpSocket::~UdpSocket()
{
}

bool UdpSocket::Socketbind(std::string &strAddr, uint16 u16Port)
{
    if (p_socket.get() != nullptr)
    {
        closesocket(*p_socket.get());
    }
    p_socket = std::make_shared<SOCKET>(socket(AF_INET, SOCK_DGRAM, 0));
    if (*p_socket.get() < 0)
    {
        m_StrError = "udp creat socket error\n"; //<<std::endl;
        std::cout << m_StrError;
        return false;
    }
    else
    {
        std::cout << "udp creat socket success\n"
                  << std::endl;
    }

    /*本机Socket 绑定本机IP与监听端口号 创建套接字*/
    p_mLocalSocketAddr = std::make_shared<sockaddr_in>();
    if (m_StrLocalAddr.empty())
    {
        p_mLocalSocketAddr->sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    }
    else
    {
        p_mLocalSocketAddr->sin_addr.S_un.S_addr = inet_addr(m_StrLocalAddr.c_str());
    }
    p_mLocalSocketAddr->sin_family = AF_INET;
    p_mLocalSocketAddr->sin_port = htonl(p_mUsPort);

    /*绑定套接字*/
    int len = sizeof(SOCKADDR);
    int nRes = bind(*p_socket, (SOCKADDR *)p_mLocalSocketAddr.get(), len);
    if (nRes < 0)
    {
        m_StrError = "UDP Socket Bind IP Error!\n";
        std::cout << m_StrError;
        return false;
    }
    std::cout << "UDP Socket Bind Success\n";

    if (m_EWorkMode == E_WorkMode::E_ReadWrite || m_EWorkMode == E_WorkMode::E_Read)
    {
        if (m_pthread_ReceiveThread.get() != nullptr)
        {
            std::lock_guard<std::mutex> guard(m_mutex_ChangWork);
            m_bReceiveWork = false;
            m_pthread_ReceiveThread->join();
        }
        m_pthread_ReceiveThread= std::make_shared<std::thread>(std::bind(&UdpSocket::ReceiveWorkThread,this));
    }

    if (m_EWorkMode == E_WorkMode::E_ReadWrite || m_EWorkMode == E_WorkMode::E_Write)
    {
        if (m_pthread_SendThread.get() != nullptr)
        {
            std::lock_guard<std::mutex> guard(m_mutex_ChangWork);
            m_bSendWork = false;
            m_pthread_SendThread->join();
        }
        m_pthread_SendThread= std::make_shared<std::thread>(std::bind(&UdpSocket::SendWorkThread,this));
    }
    return true;
}

void UdpSocket::ReceiveWorkThread()
{
    int len = sizeof(SOCKADDR);
    char m_RemoteIP[20];
    while (m_bReceiveWork)
    {
        memset(m_chRecvClientBuf, 0, 1024 * 10);
        int nLen = recvfrom(*p_socket,m_chRecvClientBuf, 1024 * 10, 0, m_pRemoteSocket, &len);
        if(nLen <= 0)
        {
            std::cout << "UDP Client Connect close\n"; 
            break;
        }
        inet_ntop(AF_INET,(const void *)(&((SOCKADDR_IN*)m_pRemoteSocket)->sin_addr),m_RemoteIP,16);
        std::cout<<"Receive["<<m_RemoteIP<<"]: "<<m_chRecvClientBuf<<std::endl;
    }
}

void UdpSocket::SendWorkThread()
{
}
