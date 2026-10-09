// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Clean BFME 1 donor NAT_attachSlotList_BFME.cpp at 9cbfb551 supplies
// transport allocation, local-IP setup and starting-port calculation.
// WB 0x014DBB90 names attachSlotList and its five arguments;
// retail 0x005A6B14..0x005A6C90 includes the missing 20-byte prologue.
#include "unicode_string.h"
#include "../../Include/GameNetwork/Transport.h"
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

struct TransportAddress
{
    unsigned int ip;
    unsigned short port;
};
struct NetPacketAddress
{
    unsigned int ip;
    unsigned short port;
    unsigned short padding;
};
class GameSlot
{
public:
    bool isHuman() const;
    unsigned char m_prefix[0x30];
    UnicodeString m_name;
    unsigned char m_pad34[4];
    NetPacketAddress m_address;
};
class GameInfo
{
public:
    unsigned char m_prefix[0x18];
    GameSlot *m_slots[8];
};
class GlobalData
{
public:
    unsigned char m_prefix[0xA54];
    unsigned int m_forcedPort;
};
extern GlobalData *TheWritableGlobalData;
class PortNegotiationSchema
{
public:
    void attachSlotList(void *slotList, unsigned short localSlot);
};
class NAT
{
public:
    void processPlayerJoin(int slot);
    void attachSlotList(GameInfo *gameInfo, int localSlot, unsigned int localIP,
        unsigned int timeout, bool isHost);
protected:
    void generatePortNumbers(GameSlot **slotList, int localSlot);
private:
    unsigned int m_00;
    Transport *m_transport;
    GameSlot **m_slotList;
    int m_hostSlot;
    int m_10;
    int m_localSlot;
    int m_18;
    unsigned int m_localIP;
    unsigned char m_pad20[0x28 - 0x20];
    PortNegotiationSchema m_schema;
    unsigned char m_pad29[0x8E4 - 0x29];
    bool m_myConnections[8];
    unsigned int m_8ec;
    unsigned char m_pad8f0[0x90C - 0x8F0];
    NetPacketAddress *m_addresses[8];
    unsigned char m_pad92c[0x958 - 0x92C];
    unsigned short m_startingPortNumber;
    unsigned char m_pad95a[0x968 - 0x95A];
    unsigned int m_timeoutTime;
};

void NAT::attachSlotList(GameInfo *gameInfo, int localSlot, unsigned int localIP,
    unsigned int timeout, bool isHost)
{
    if (!gameInfo)
        return;
    m_slotList = gameInfo->m_slots;
    m_localIP = localIP;
    m_localSlot = localSlot;
    if (m_localSlot < 0 || m_localSlot >= 8)
        return;
    if (isHost)
        m_hostSlot = localSlot;
    else
        m_hostSlot = 8;
    m_transport = new Transport;
    if (TheWritableGlobalData->m_forcedPort > 0)
        m_startingPortNumber = (unsigned short)TheWritableGlobalData->m_forcedPort;
    else
        m_startingPortNumber = (unsigned short)(8088 + ((timeGetTime() / 1000) % 20000));
    generatePortNumbers(m_slotList, localSlot);
    if (TheWritableGlobalData->m_forcedPort != 0) {
        unsigned short port = (unsigned short)TheWritableGlobalData->m_forcedPort;
        unsigned int ip = m_localIP;
        TransportAddress address = {ip, port};
        m_transport->init(&address);
    } else {
        m_transport->rva004D53B5((void *)m_localIP);
    }
    m_schema.attachSlotList(m_slotList, (unsigned short)localSlot);
    if (m_slotList) {
        for (int i = 0; i < 8; ++i) {
            if (m_slotList[i] && m_slotList[i]->isHuman() && m_slotList[i]->m_name.getLength())
                processPlayerJoin(i);
            m_myConnections[i] = false;
            m_8ec = 0;
        }
    }
    m_myConnections[localSlot] = true;
    m_timeoutTime = timeGetTime() + timeout;
}

// BFME 1 NAT_generatePortNumbers.cpp at 9cbfb551 supplies port assignment;
// complete WB 0x014DB9D0 and native 0x005A678E add the two-word address cache.
void NAT::generatePortNumbers(GameSlot **slotList, int localSlot)
{
    for (int i = 0; i < 8; ++i) {
        if (slotList[i]) {
            if (i == localSlot && TheWritableGlobalData->m_forcedPort != 0) {
                NetPacketAddress address = slotList[i]->m_address;
                address.port = (unsigned short)TheWritableGlobalData->m_forcedPort;
                slotList[i]->m_address = address;
                if (!m_addresses[i])
                    m_addresses[i] = new NetPacketAddress(address);
                else
                    *m_addresses[i] = address;
            } else {
                NetPacketAddress address = slotList[i]->m_address;
                address.port = (unsigned short)(m_startingPortNumber + i);
                slotList[i]->m_address = address;
                if (!m_addresses[i])
                    m_addresses[i] = new NetPacketAddress(address);
                else
                    *m_addresses[i] = address;
            }
        }
    }
}
