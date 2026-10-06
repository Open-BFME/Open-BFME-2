// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?rva0058E2D7@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z, retail 0x0058E2D7, 144 bytes.
// Static NetPacket factory reading word then dword: new Rva004D598E (0x24)
// via rowed ctor 0x004D598E, memcpy 2B into v0 then WordSlot set at +0x1C
// via rowed 0x004D59AC, memcpy 4B into v1 then setLeavingPlayerID at +0x20
// via rowed 0x00317B9B. Same shape and flags as siblings 0x0058E367
// (dword plus dword) and 0x0058DC1C (word plus byte plus dword plus dword).
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
class NetCommandMsg;
class Rva004D598E
{
public:
	Rva004D598E();
private:
	char m_pad[0x24];
};
class Rva004D59ACWordSlot
{
public:
	void set(unsigned short value);
};
class BFMENetInformPlayerLeaveFrameCommandMsg
{
public:
	void setLeavingPlayerID(Int playerID);
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class NetPacket
{
public:
	static NetCommandMsg *rva0058E2D7(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058E2D7(unsigned char *data, int &readOffset)
{
	Rva004D598E *msg = new Rva004D598E();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	Int v1 = 0;
	memcpy(&v1, data + readOffset, 4);
	readOffset += 4;
	((BFMENetInformPlayerLeaveFrameCommandMsg *)msg)->setLeavingPlayerID(v1);
	return (NetCommandMsg *)msg;
}
