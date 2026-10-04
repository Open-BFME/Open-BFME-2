// ?rva004D4EC6@Transport@@QAE_NPBURva004495A2Addr@@PBULANMessage@@H@Z
// partial score=0.96 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva004D4EC6@Transport@@QAE_NPBURva004495A2Addr@@PBULANMessage@@H@Z @0x004D4EC6 180B
// Transport packet queue: validates msg/len, finds empty slot among 128
// stride-0x40E buffers at +0x0 (len at +0x404), CRCs via rowed
// BFMEComputeCRC 0x003EC8F7, memcpy via thunk 0x006291A8, rolling-xor plus
// IAT htonl per dword. Evidence: retail empty-slot search plus CRC-memcpy
// plus xor-htonl loop; callers at 0x004495CA/0x0044961D/0x00449648 in
// LANAPIRva004495A2Send.cpp; neighbours Transport.cpp/TransportRva004D5046.cpp.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

struct Rva004495A2Addr
{
	UnsignedInt ip;
	UnsignedShort port;
};

struct LANMessage
{
	Int type;
	UnsignedByte bytes[0x1D4];
};

UnsignedInt BFMEComputeCRC(const UnsignedByte *data, UnsignedInt length, UnsignedInt crc);
void __cdecl ji_006291a8();
extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);

#pragma pack(push, 1)
struct TransportSlot
{
	UnsignedInt m_crc;
	UnsignedByte m_data[0x400];
	Int m_len;
	UnsignedInt m_ip;
	UnsignedShort m_port;
};
#pragma pack(pop)

class Transport
{
public:
	bool rva004D4EC6(const Rva004495A2Addr *to, const LANMessage *msg, Int len);
private:
	TransportSlot m_slots[128];
};

bool Transport::rva004D4EC6(const Rva004495A2Addr *to, const LANMessage *msg, Int len)
{
	if (msg == 0 || (UnsignedInt)len > 0x1DC)
		goto fail;
	Int i;
	for (i = 0; i < 0x80; ++i)
	{
		if (m_slots[i].m_len == 0)
			goto found;
	}
fail:
	return false;
found:
	const UnsignedByte *data = (const UnsignedByte *)msg;
	UnsignedInt ulen = (UnsignedInt)len;
	UnsignedInt crc = BFMEComputeCRC(data, ulen, 0);
	TransportSlot *slot = &m_slots[i];
	slot->m_ip = to->ip;
	slot->m_port = to->port;
	slot->m_len = len;
	((void (__cdecl *)(void *, const void *, UnsignedInt))ji_006291a8)(slot->m_data, msg, (UnsignedInt)len);
	slot->m_crc = crc;
	Int count = (len + 4) / 4;
	UnsignedInt *p = (UnsignedInt *)slot;
	UnsignedInt key = 0x38d9b7d4;
	for (Int n = count; n > 0; --n)
	{
		*p ^= key;
		*p = htonl(*p);
		++p;
		key -= 0x7f39c50e;
	}
	return true;
}
