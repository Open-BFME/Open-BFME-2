// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /arch:SSE
// ?rva0058BD4F@Connection@@QAEPAVNetCommandRef@@PAX@Z @0x0058BD4F 44B Connection ack forward: forwards packet +0x20/+0x24 plus byte/word field gets to ack retire 0x0058B9CA; evidence: unlock lane callees rowed ByteField 0x004543C6 WordField 0x004D5767 retire 0x0058B9CA callers 0x0058BD88 0x0058BD94 unblocks 0x0058BD7B neighbours ConnectionInit/ConnectionCtor
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
class NetCommandRef;
class Rva004543C6ByteField
{
public:
	unsigned char get() const;
};
class Rva004D5767WordField
{
public:
	unsigned short get() const;
};
struct Rva0058BD4FPkt
{
	unsigned char pad[0x20];
	UnsignedInt field20;
	UnsignedInt field24;
};
class Connection
{
public:
	NetCommandRef *processAck(UnsignedShort commandID, UnsignedByte playerID, UnsignedInt timestamp, UnsignedInt executionFrame);
	NetCommandRef *rva0058BD4F(void *msg);
};
NetCommandRef *Connection::rva0058BD4F(void *msg)
{
	Rva0058BD4FPkt *pkt = (Rva0058BD4FPkt *)msg;
	return processAck(((Rva004D5767WordField *)msg)->get(), ((Rva004543C6ByteField *)msg)->get(), pkt->field20, pkt->field24);
}
