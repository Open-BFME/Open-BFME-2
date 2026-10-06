// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058E367@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058E367 141B.
// Static NetCommandMsg factory reading leaving-player ID then leave frame.
// Evidence: BFME1 donor NetPacket_read.cpp readInformPlayerLeaveFrameMessage
// (same new plus setLeavingPlayerID plus setLeaveFrame order); neighbours
// 0x0058E047/0x0058E511 (same NetPacket static factory shape PAEAAH);
// Rva004D59D1 ctor row (type 8 plus vtable 0x860274); setLeaveFrame row.
// Retail defaults playerID to -1 where the donor uses 0 (or -1 proves it).
// The 10B setter at 0x00317B9B is rowed YAXXZ (TYPES wrong); declared as used.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
class NetCommandMsg;
class Rva004D59D1
{
public:
    Rva004D59D1();
private:
    char m_pad[0x24];
};
class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
    void setLeavingPlayerID(Int playerID);
    void setLeaveFrame(UnsignedInt frame);
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
    static NetCommandMsg *rva0058E367(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E367(unsigned char *data, int &readOffset)
{
    Rva004D59D1 *msg = new Rva004D59D1();
    Int playerID = -1;
    memcpy(&playerID, data + readOffset, 4);
    readOffset += 4;
    ((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(playerID);
    UnsignedInt leaveFrame = 0;
    memcpy(&leaveFrame, data + readOffset, 4);
    readOffset += 4;
    ((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeaveFrame(leaveFrame);
    return (NetCommandMsg *)msg;
}
