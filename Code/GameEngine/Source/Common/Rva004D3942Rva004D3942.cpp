// cl: /DNDEBUG /MD /EHsc
//
// ?rva004D3942@Rva004D3942@@QAEXPAVConnectionManager@@@Z, retail 0x004d3942, 156 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Keepalive sender: if time-last >500 or last==-1 news NetDisconnectKeepAlive
// stamps playerID via rowed getLocalPlayerID gates commandID via rowed Does
// then rowed Generate plus pin sendLocalCommandDirect plus rowed detach.
// Evidence: timeGetTime import plus new 0x1c plus caller 0x004D48BE.
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

void *__cdecl operator new(unsigned int size);

enum NetCommandType
{
    NETCOMMANDTYPE_UNKNOWN = -1
};

class NetCommandMsg
{
public:
    NetCommandMsg();
    void detach();

    unsigned int m_timestamp;
    unsigned int m_executionFrame;
    unsigned int m_playerID;
    unsigned short m_id;
    NetCommandType m_commandType;
    int m_referenceCount;

protected:
    virtual ~NetCommandMsg();
};

class NetDisconnectKeepAliveCommandMsg : public NetCommandMsg
{
public:
    NetDisconnectKeepAliveCommandMsg();
};

class ConnectionManager;
unsigned short __cdecl GenerateNextCommandID(void);

class ConnectionManager
{
public:
    unsigned int getLocalPlayerID();
    void sendLocalCommandDirect(NetCommandMsg *msg, unsigned char mask);
};

bool DoesCommandRequireACommandID(NetCommandType type);

class Rva004D3942
{
public:
    void rva004D3942(ConnectionManager *mgr);

private:
    char m_pad[0x10];
    unsigned long m_10;
};

void Rva004D3942::rva004D3942(ConnectionManager *mgr)
{
    unsigned long now = timeGetTime();
    unsigned long last = m_10;
    if (now - last <= 500 && last != (unsigned long)-1)
        return;
    NetDisconnectKeepAliveCommandMsg *msg = new NetDisconnectKeepAliveCommandMsg;
    msg->m_playerID = mgr->getLocalPlayerID();
    if (DoesCommandRequireACommandID(msg->m_commandType) == 1)
        msg->m_id = GenerateNextCommandID();
    mgr->sendLocalCommandDirect(msg, (unsigned char)~(1u << msg->m_playerID));
    msg->detach();
    m_10 = now;
}
