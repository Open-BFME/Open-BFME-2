// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 FirewallHelperClass empty-message scan, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameNetwork/FirewallHelper.cpp).
// Retail BFME2 keeps the same table: 8 packed 0x1E-byte entries at +0x8A with
// the length field at entry+0x14. The packing matches the Zero Hour donor
// (reference/.../GameEngine/Include/GameNetwork/FirewallHelper.h): despite
// its stale "size = 16 bytes" comment, the packed ManglerData is 20 bytes,
// so the packed message is 30 bytes and the stride falls out naturally.

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

class FirewallHelperClass
{
private:
	ManglerMessage *findEmptyMessage();

private:
	unsigned char m_pre[0x8A];
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
