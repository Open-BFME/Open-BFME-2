// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058C80FWrite@@YAXPADPAVNetCommandRef@@@Z @0x0058C80F (213B).
// Tagged serializer: T<type>R<relay>P<player>S<timestamp>F<frame>C<id>D<w0><w1><w2>.
// Evidence: sibling Rva0058CEC5Write layout (timestamp +4 frame +8 player +0xc
// id +0x10 type +0x14, NetCommandRef msg +0 relay +0xc) plus import 0x006291A8;
// tail dwords at msg +0x1c +0x20 +0x24.
void __cdecl ji_006291a8();

class NetWrapperCommandMsg
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
	unsigned int m_w0;
	unsigned int m_w1;
	unsigned int m_w2;
};

class NetCommandRef
{
public:
	NetWrapperCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva0058C80FWrite(char *dst, NetCommandRef *ref)
{
	NetWrapperCommandMsg *msg = ref->m_msg;
	dst[0] = 'T';
	dst[1] = (char)msg->m_commandType;
	dst[2] = 'R';
	unsigned char relay = ref->m_relay;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 3, &relay, 1);
	dst[4] = 'P';
	dst[5] = (char)msg->m_playerID;
	dst[6] = 'S';
	unsigned int ts = msg->m_timestamp;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 7, &ts, 4);
	dst[0xb] = 'F';
	unsigned int fr = msg->m_executionFrame;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xc, &fr, 4);
	dst[0x10] = 'C';
	unsigned short id = msg->m_id;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0x11, &id, 2);
	dst[0x13] = 'D';
	unsigned int w0 = msg->m_w0;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0x14, &w0, 4);
	unsigned int w1 = msg->m_w1;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0x18, &w1, 4);
	unsigned int w2 = msg->m_w2;
	dst += 0x1c;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &w2, 4);
}
