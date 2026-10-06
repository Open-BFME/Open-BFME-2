// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// BFME2 FirewallHelperClass empty-message scan, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameNetwork/FirewallHelper.cpp).
// Retail BFME2 keeps the same table: 8 packed 0x1E-byte entries at +0x8A with
// the length field at entry+0x14. The packing matches the Zero Hour donor
// (reference/.../GameEngine/Include/GameNetwork/FirewallHelper.h): despite
// its stale "size = 16 bytes" comment, the packed ManglerData is 20 bytes,
// so the packed message is 30 bytes and the stride falls out naturally.
// The spare-socket search (0x00594D77) was folded in from a split unit with
// these exact flags; its spareSockets[8] table sits at +0x14.

#pragma pack(push, 1)

struct ManglerData
{
	unsigned int m_crc;
	unsigned short m_magic;
	unsigned short m_packetID;
	unsigned short m_mangledPortNumber;
	unsigned short m_originalPortNumber;
	unsigned char m_mangledAddress[4];
	unsigned char m_netCommandType;
	unsigned char m_blitzMe;
	unsigned short m_padding;
};

struct ManglerMessage
{
	ManglerData m_data;	// 20 bytes
	int m_length;		// +0x14
	unsigned int m_ip;
	unsigned short m_port;
};	// 30 bytes packed

#pragma pack(pop)

struct SpareEntry
{
	void *udp;
	unsigned short port;
	char _pad[2];
};

class FirewallHelperClass
{
public:
	void *rva00594D77(unsigned short port);

private:
	ManglerMessage *findEmptyMessage();

private:
	char _pad00[0x14];
	SpareEntry m_spare[8];			// +0x14
	unsigned char m_pad54[0x8A - 0x54];
	ManglerMessage m_messages[8];	// +0x8A
};

// ?findEmptyMessage@FirewallHelperClass@@AAEPAUManglerMessage@@XZ
ManglerMessage *FirewallHelperClass::findEmptyMessage()
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_messages[i].m_length == 0)
		{
			return &(m_messages[i]);
		}
	}
	return 0;
}

// ?rva00594D77@FirewallHelperClass@@QAEPAXG@Z @0x00594D77 (37B): search
// spareSockets[8] at +0x14 by port at +0x18 stride 8; return entry or 0;
// layout from Rva00594CDDPermuted ctor; neighbours FirewallHelperClass ctor
// and findEmptyMessage.
void *FirewallHelperClass::rva00594D77(unsigned short port)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_spare[i].port == port)
			return &m_spare[i];
	}
	return 0;
}
