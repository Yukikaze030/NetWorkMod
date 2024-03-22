#ifndef TYPERENAME_H
#define TYPERENAME_H
#define uint16 unsigned short
#define uint32 unsigned int
#define uint8 unsigned char


enum E_WorkMode
{
    E_Read = 0x01,
    E_Write = 0x10,
    E_ReadWrite = 0x11
};

enum E_UdpDataPacketMode
{

};

struct UdpDataPacket
{

};
#endif // TYPERENAME_H
