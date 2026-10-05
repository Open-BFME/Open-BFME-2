// ?Rva0058C8E4Write@@YAXPADPAVNetCommandRef@@@Z
// partial score=0.95 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058C8E4Write@@YAXPADPAVNetCommandRef@@@Z @0x0058C8E4 (136B).
// Tagged NetCommand serializer: T<type>R<relay>S<timestamp>P<player>C<id>D<8>.
// Evidence: same prefix as sibling Rva0058CCF2Write (timestamp +4 player +0xc
// id +0x10 type +0x14) plus NetCommandRef (msg +0 relay +0xc) plus import
// 0x006291A8; tail copies 8 spaced bytes at msg+0x1c stride 4 to dst+0xf.
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
	struct Quad
	{
		unsigned char v;
		char pad[3];
	};
	Quad m_q[8];
};

class NetCommandRef
{
public:
	NetCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva0058C8E4Write(char *dst, NetCommandRef *ref)
{
	NetCommandMsg *msg = ref->m_msg;
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
	dst[0xb] = 'C';
	unsigned short id = msg->m_id;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xc, &id, 2);
	dst[0xe] = 'D';
	for (int i = 0; i < 8; ++i)
		dst[0xf + i] = msg->m_q[i].v;
}
