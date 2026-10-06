// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E481@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E481 144B.
// Static NetCommandMsg factory reading player index then second dword.
// Evidence: neighbours 0x0058E367 and 0x0058E511 same NetPacket static factory
// shape PAEAAH plus same flags; new-0x24 plus Rva004D5A30 ctor row type 9
// vtable 0x860294; memcpy plus Rva004D57AE setter row at plus-0x1C; second
// setter at 0x00317B9B writes plus-0x20.
// The 10B setter at 0x00317B9B is rowed YAXXZ (TYPES wrong); declared as used.
typedef unsigned int UnsignedInt;
typedef int Int;
class NetCommandMsg;
class Rva004D5A30
{
public:
    Rva004D5A30();
private:
    char m_pad[0x24];
};
class Rva004D57AE
{
public:
    void setPlayerIndex(UnsignedInt value);
};
class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
    void setLeavingPlayerID(Int value);
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058E481(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E481(unsigned char *data, int &readOffset)
{
    Rva004D5A30 *msg = new Rva004D5A30();
    UnsignedInt playerIndex = 0;
    memcpy(&playerIndex, data + readOffset, 4);
    readOffset += 4;
    ((Rva004D57AE *)msg)->setPlayerIndex(playerIndex);
    Int field20 = 0;
    memcpy(&field20, data + readOffset, 4);
    readOffset += 4;
    ((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(field20);
    return (NetCommandMsg *)msg;
}
