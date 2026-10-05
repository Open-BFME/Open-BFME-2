// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058CD6AWrite@@YAXPADPAVNetCommandRef@@@Z @0x0058CD6A (185B).
// Tagged serializer: T<type>R<relay>S<timestamp>P<player>C<id>D<u1c><u20><len><data>.
// Evidence: sibling Rva0058CE23Write layout (timestamp +4 player +0xc id +0x10
// type +0x14, NetCommandRef msg +0 relay +0xc) plus import 0x006291A8;
// tail copies dword +0x1c word +0x20 dword +0x28 then variable bytes
// from pointer +0x24 with size +0x28.
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
	unsigned int m_unk1c;
	unsigned short m_unk20;
	char m_pad22[2];
	unsigned char *m_data;
	unsigned int m_dataLength;
};

class NetCommandRef
{
public:
	NetWrapperCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva0058CD6AWrite(char *dst, NetCommandRef *ref)
{
	NetWrapperCommandMsg *msg = ref->m_msg;
	dst[0] = 'T';
	dst[1] = (char)msg->m_commandType;
	dst[2] = 'R';
	dst[3] = (char)ref->m_relay;
	dst[4] = 'S';
	unsigned int ts = msg->m_timestamp;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 5, &ts, 4);
	dst[9] = 'P';
	dst[0xa] = (char)msg->m_playerID;
	dst[0xb] = 'C';
	unsigned short id = msg->m_id;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xc, &id, 2);
	dst[0xe] = 'D';
	unsigned int u1c = msg->m_unk1c;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xf, &u1c, 4);
	unsigned short u20 = msg->m_unk20;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0x13, &u20, 2);
	u1c = msg->m_dataLength;
	dst += 0x15;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &u1c, 4);
	dst += 4;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, msg->m_data, (int)msg->m_dataLength);
}
