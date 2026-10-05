// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058C96CWrite@@YAXPADPAVNetCommandRef@@@Z @0x0058C96C (175B).
// Tagged NetProgressCommand serializer: T<type>R<relay>S<timestamp>F<frame>P<player>C<id>D<percent>.
// Evidence: sibling Rva0058CCF2Write layout (timestamp +4 frame +8 player +0xc
// id +0x10 type +0x14, NetCommandRef msg +0 relay +0xc) plus import 0x006291A8
// and getPercentage row 0x004C54EC on the same msg.
void __cdecl ji_006291a8();

class NetProgressCommandMsg
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
	unsigned char getPercentage();
};

class NetCommandRef
{
public:
	NetProgressCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva0058C96CWrite(char *dst, NetCommandRef *ref)
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
	dst[9] = 'F';
	unsigned int fr = msg->m_executionFrame;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xa, &fr, 4);
	dst[0xe] = 'P';
	dst[0xf] = (char)msg->m_playerID;
	dst[0x10] = 'C';
	unsigned short id = msg->m_id;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0x11, &id, 2);
	dst[0x13] = 'D';
	unsigned char pct = msg->getPercentage();
	dst += 0x14;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &pct, 1);
}
