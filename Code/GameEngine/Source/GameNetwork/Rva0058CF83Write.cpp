// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058CF83Write@@YAXPADPAVNetCommandRef@@@Z @0x0058CF83 (190B).
// Tagged serializer: T<type>S<timestamp>F<frame>R<relay>P<player>C<id>D<dataPtr><len>.
// Evidence: sibling Rva0058CEC5Write layout (timestamp +4 frame +8 player +0xc
// id +0x10 type +0x14, NetCommandRef msg +0 relay +0xc) plus import 0x006291A8;
// tail uses getData row 0x0030F2C7 then getDataLength row 0x0030D377.
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
	unsigned int getDataLength();
	unsigned char *getData();
};

class NetCommandRef
{
public:
	NetWrapperCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva0058CF83Write(char *dst, NetCommandRef *ref)
{
	NetWrapperCommandMsg *msg = ref->m_msg;
	dst[0] = 'T';
	dst[1] = (char)msg->m_commandType;
	dst[2] = 'S';
	unsigned int ts = msg->m_timestamp;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 3, &ts, 4);
	dst[7] = 'F';
	unsigned int fr = msg->m_executionFrame;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 8, &fr, 4);
	dst[0xc] = 'R';
	dst[0xd] = (char)ref->m_relay;
	dst[0xe] = 'P';
	dst[0xf] = (char)msg->m_playerID;
	dst[0x10] = 'C';
	unsigned short id = msg->m_id;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0x11, &id, 2);
	dst[0x13] = 'D';
	unsigned char *data = msg->getData();
	dst += 0x14;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &data, 4);
	unsigned int len = msg->getDataLength();
	dst += 4;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &len, 4);
}
