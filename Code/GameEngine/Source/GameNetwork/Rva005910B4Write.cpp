// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
// ?Rva005910B4Write@@YAXPADPAVNetCommandRef@@@Z @0x005910B4 188B. Tagged
// NetCommand serializer: T<type>R<relay>S<timestamp>P<player>D<len><wstr>.
// Evidence: NetCommandMsg layout from sibling NetPacket_rva0059188C
// (timestamp +4 player +0xc type +0x14 string +0x1c) plus NetCommandRef
// (msg +0 relay +0xc); rowed UnicodeString getter 0x004D6119 plus wide
// releaseBuffer 0x00036E70 plus import 0x006291A8; caller 0x00592B48.
#include "unicode_string.h"

void __cdecl ji_006291a8();

class NetCommandMsg
{
public:
	void *m_vptr;
	unsigned int m_timestamp;
	unsigned int m_executionFrame;
	unsigned int m_playerID;
	unsigned short m_id;
	char m_pad12[2];
	int m_commandType;
	int m_referenceCount;
};

class Rva004D6119 : public NetCommandMsg
{
public:
	UnicodeString rva004D6119() const;
private:
	UnicodeString m_str1c;
};

class NetCommandRef
{
public:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva005910B4Write(char *dst, NetCommandRef *ref)
{
	Rva004D6119 *msg = (Rva004D6119 *)ref->m_msg;
	dst[0] = 'T';
	dst[1] = (char)msg->m_commandType;
	dst[2] = 'R';
	unsigned char relay = ref->m_relay;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 3, &relay, 1);
	dst[4] = 'S';
	unsigned int ts = msg->m_timestamp;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 5, &ts, 4);
	dst[9] = 'P';
	dst[0xa] = (char)msg->m_playerID;
	dst[0xb] = 'D';
	UnicodeString tmp = msg->rva004D6119();
	unsigned char len = (unsigned char)tmp.getLength();
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xc, &len, 1);
	const unsigned short *s = tmp.str();
	int byteLen = len;
	byteLen += byteLen;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xd, s, byteLen);
}
