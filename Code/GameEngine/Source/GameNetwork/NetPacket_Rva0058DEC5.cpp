// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058DEC5@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DEC5 50B.
// Static NetCommandMsg factory constructing KeepAlive with no fields read.
// Evidence: unlock lane plus sibling 0x0058E047 plus new-0x1c plus
// NetKeepAliveCommandMsg ctor plus uniform factory signature.
class NetCommandMsg;
class NetKeepAliveCommandMsg
{
public:
    NetKeepAliveCommandMsg();
private:
    char m_pad[0x1C];
};
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058DEC5(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058DEC5(unsigned char *data, int &readOffset)
{
    (void)data;
    (void)readOffset;
    NetKeepAliveCommandMsg *msg = new NetKeepAliveCommandMsg();
    return (NetCommandMsg *)msg;
}
