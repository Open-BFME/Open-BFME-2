// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E511@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E511 106B.
// Static NetCommandMsg factory reading player index from data+offset.
// Evidence: unlock lane plus prev NetPacket_isRoomForFrameMessage plus
// new-0x20 plus Rva004D59B8 ctor plus memcpy plus Rva004D57AE setter.
typedef unsigned int UnsignedInt;
class NetCommandMsg;
class Rva004D59B8
{
public:
    Rva004D59B8();
private:
    char m_pad[0x20];
};
class Rva004D57AE
{
public:
    void setPlayerIndex(UnsignedInt value);
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058E511(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E511(unsigned char *data, int &readOffset)
{
    Rva004D59B8 *msg = new Rva004D59B8();
    UnsignedInt playerIndex = 0;
    memcpy(&playerIndex, data + readOffset, 4);
    readOffset += 4;
    ((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
    return (NetCommandMsg *)msg;
}
