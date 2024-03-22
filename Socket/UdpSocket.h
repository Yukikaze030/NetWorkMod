#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "BaseSocket.h"

class UdpSocket : public BaseSocket
{
public:
    UdpSocket();
    ~UdpSocket() override;

    // void StartReceiveThread();
    // void StartSendThread();
public:
    bool Socketbind(std::string&,uint16 = 0) override;
    void SendWorkThread();
    void ReceiveWorkThread();
private:


private:
    char m_chRecvClientBuf[1024*10]="";
    bool m_bSendWork = false;
    bool m_bReceiveWork = false;
    std::shared_ptr<std::thread> m_pthread_SendThread;
    std::shared_ptr<std::thread> m_pthread_ReceiveThread;
    
    SOCKADDR* m_pRemoteSocket = nullptr;
    std::mutex m_mutex_ChangWork;
};

#endif // UDPSOCKET_H
