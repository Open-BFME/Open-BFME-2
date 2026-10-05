// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs-c- /G7
//
// ?Rva0058CBD9Write@@YAXPADPAVNetCommandRef@@@Z @0x0058CBD9 (178B).
// Tagged serializer: T<type>R<relay>S<timestamp>P<player>C<id>D<percent><dataLength>.
// Evidence: sibling Rva0058CB27Write layout (timestamp +4 player +0xc id +0x10
// type +0x14, NetCommandRef msg +0 relay +0xc) plus import 0x006291A8,
// getPercentage row 0x004C54EC and getDataLength row 0x0030D377 on the same msg.
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
	NetProgressCommandMsg *m_msg;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	unsigned char m_relay;
};

void __cdecl Rva0058CBD9Write(char *dst, NetCommandRef *ref)
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
	dst[0xb] = 'C';
	unsigned short id = msg->m_id;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xc, &id, 2);
	dst[0xe] = 'D';
	unsigned char pct = msg->getPercentage();
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst + 0xf, &pct, 1);
	unsigned int len = ((NetWrapperCommandMsg *)msg)->getDataLength();
	dst += 0x10;
	((void (__cdecl *)(void *, const void *, int))ji_006291a8)(dst, &len, 4);
}
