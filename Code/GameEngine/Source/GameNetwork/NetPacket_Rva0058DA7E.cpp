// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva0058DA7E@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z @0x0058DA7E 207B.
// Static NetAckBoth factory reading word + byte + two dwords from data+offset.
// Evidence: sibling ?rva0058DB4D@NetPacket@@SAPAVNetCommandMsg@@PAEAAH@Z 207B
// in this dir plus new-0x28 plus rowed ??0NetAckBothCommandMsg@@QAE@XZ 0x004D568F
// plus triple memcpy plus word setter 0x004D59AC byte setter 0x004D576C
// plus direct stores to +0x20 +0x24 matching NetAckBoth layout.
class NetCommandMsg;
class NetAckBothCommandMsg
{
public:
	NetAckBothCommandMsg();
private:
	char m_pad[0x1C];
public:
	unsigned short m_1c;
	unsigned char m_1e;
	char m_pad1f;
	unsigned int m_20;
	unsigned int m_24;
};
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
void *__cdecl operator new(unsigned int size);
class Rva004D59ACWordSlot
{
public:
	void set(unsigned short value);
};
class Rva004D576CByteSlot
{
public:
	void set(unsigned char value);
};
class NetPacket
{
public:
	static NetCommandMsg *rva0058DA7E(unsigned char *data, int &readOffset);
};
NetCommandMsg *NetPacket::rva0058DA7E(unsigned char *data, int &readOffset)
{
	NetAckBothCommandMsg *msg = new NetAckBothCommandMsg();
	unsigned int v0 = 0;
	memcpy(&v0, data + readOffset, 2);
	readOffset += 2;
	((Rva004D59ACWordSlot *)msg)->set((unsigned short)v0);
	unsigned char v1 = 0;
	memcpy(&v1, data + readOffset, 1);
	readOffset += 1;
	((Rva004D576CByteSlot *)msg)->set(v1);
	unsigned int v2 = (unsigned int)-1;
	memcpy(&v2, data + readOffset, 4);
	readOffset += 4;
	msg->m_20 = v2;
	unsigned int v3 = (unsigned int)-1;
	memcpy(&v3, data + readOffset, 4);
	readOffset += 4;
	msg->m_24 = v3;
	return (NetCommandMsg *)msg;
}
