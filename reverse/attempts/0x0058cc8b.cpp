// ?Rva0058CC8BWrite@@YAXPADPAVNetCommandRef@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058CC8BWrite@@YAXPADPAVNetCommandRef@@@Z @0x0058CC8B (103B).
// Tagged NetProgressCommand serializer: T<type>R<relay>S<timestamp>P<player>D<percent>.
// Evidence: same NetCommandMsg/Ref layout as sibling Rva0058CCF2Write
// (timestamp +4 player +0xc type +0x14 relay +0xc) plus import 0x006291A8
// plus rowed getPercentage at 0x004C54EC; caller unclaimed.
void __cdecl ji_006291a8();

class NetProgressCommandMsg
{
public:
	unsigned char getPercentage();

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

class NetCommandRef
{
public:
	NetProgressCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

// ?Rva0058CC8BWrite@@YAXPADPAVNetCommandRef@@@Z present-unmatched
void __cdecl Rva0058CC8BWrite(char *dst, NetCommandRef *ref)
{
	NetProgressCommandMsg *msg = ref->m_msg;
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
	dst[0xc] = msg->getPercentage();
}
