// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs-c-
//
// ?Rva0058CE23Write@@YAXPADPAVNetCommandRef@@@Z @0x0058CE23 (162B).
// Tagged NetWrapperCommand serializer: T<type>R<relay>S<timestamp>P<player>C<id>D<wrapped>W<dataLen>.
// Evidence: sibling Rva0058CCF2Write layout (timestamp +4 player +0xc id +0x10
// type +0x14, NetCommandRef msg +0 relay +0xc) plus import 0x006291A8,
// WordField +0x1c row 0x004D5767 and getDataLength row 0x0030D377 on the same msg.
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
	unsigned int getDataLength();
};

class NetCommandRef
{
public:
	NetWrapperCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

class Rva004D5767WordField
{
public:
	unsigned short get() const;
	char m_lead[0x1c];
	unsigned short m_value;
};

void __cdecl Rva0058CE23Write(char *dst, NetCommandRef *ref)
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
	unsigned short w = ((const Rva004D5767WordField *)msg)->get();
	dst += 0xf;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &w, 2);
	unsigned int len = msg->getDataLength();
	dst += 2;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &len, 4);
}
