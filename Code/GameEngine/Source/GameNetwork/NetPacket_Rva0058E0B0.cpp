// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E0B0@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E0B0 50B.
// Static NetCommandMsg factory allocating base message only.
// Evidence: neighbours 0x0058E047 and 0x0058E367 same NetPacket static factory
// shape PAEAAH plus same flags; new-0x1C plus NetCommandMsg base ctor row;
// same two free-function callers as 0x0058E481 family; no payload reads.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
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
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058E0B0(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E0B0(unsigned char *data, int &readOffset)
{
    return new NetCommandMsg();
}
