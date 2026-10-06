// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E20D@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E20D 202B.
// Static NetPacket factory for Rva004D58DE (0x2C): new via rowed ctor 0x004D58DE,
// dword at +0x1C via 4B memcpy, word at +0x20 via 2B memcpy, dword len via 4B
// memcpy then new[] buffer plus memcpy plus rowed SetData 0x004D5925.
// Evidence: neighbours 0x0058E0B0 and 0x0058E2D7 same NetPacket static factory
// shape PAEAAH plus same flags; same two free-function callers as family.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef unsigned char UnsignedByte;
enum NetCommandType
{
    NETCOMMANDTYPE_UNKNOWN = -1
};
class NetCommandMsg
{
public:
    NetCommandMsg();
    virtual ~NetCommandMsg();
protected:
    UnsignedInt m_timestamp;
    UnsignedInt m_executionFrame;
    UnsignedInt m_playerID;
    UnsignedShort m_id;
    NetCommandType m_commandType;
    Int m_referenceCount;
};
class Rva004D58DE : public NetCommandMsg
{
public:
    Rva004D58DE();
    void rva004D5925(unsigned char *data, unsigned int len);
    UnsignedInt m_1c;
    UnsignedShort m_20;
    unsigned char *m_24;
    UnsignedInt m_28;
};
void *__cdecl operator new(unsigned int size);
void *__cdecl operator new[](unsigned int size);
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
class NetPacket
{
public:
    static NetCommandMsg *rva0058E20D(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E20D(unsigned char *data, int &readOffset)
{
    Rva004D58DE *msg = new Rva004D58DE();
    UnsignedInt v0 = 0;
    memcpy(&v0, data + readOffset, 4);
    readOffset += 4;
    msg->m_1c = v0;
    UnsignedInt v1 = 0;
    memcpy(&v1, data + readOffset, 2);
    readOffset += 2;
    msg->m_20 = (UnsignedShort)v1;
    UnsignedInt len = 0;
    memcpy(&len, data + readOffset, 4);
    readOffset += 4;
    unsigned char *buf = new unsigned char[len];
    memcpy(buf, data + readOffset, len);
    readOffset += len;
    msg->rva004D5925(buf, len);
    return (NetCommandMsg *)msg;
}
