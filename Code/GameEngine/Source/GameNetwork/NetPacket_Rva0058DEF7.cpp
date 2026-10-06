// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058DEF7@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DEF7 50B.
// Static NetCommandMsg factory constructing DisconnectKeepAlive with no fields read.
// Evidence: unlock lane plus sibling 0x0058DEC5 plus new-0x1c plus
// NetDisconnectKeepAliveCommandMsg ctor plus uniform factory signature.
class NetCommandMsg;
class NetDisconnectKeepAliveCommandMsg
{
public:
    NetDisconnectKeepAliveCommandMsg();
private:
    char m_pad[0x1C];
};
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058DEF7(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058DEF7(unsigned char *data, int &readOffset)
{
    (void)data;
    (void)readOffset;
    NetDisconnectKeepAliveCommandMsg *msg = new NetDisconnectKeepAliveCommandMsg();
    return (NetCommandMsg *)msg;
}
