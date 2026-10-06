// cl: /DNDEBUG /MD
// ?rva005DB004@Rva005DB004@@QAEXXZ 0x005DB004 31B
// Copies +0x10->+8 +0x24->+0xC +0x20->+0xA8 into struct at +0x38.
// Evidence: callers 0x5DB06B 0x5DB0E9; unblocks 0x5DB023 0x5DB08F.
struct Target005DB004
{
	char m_pad[8];
	int m_8;
	int m_c;
	char m_pad2[0xA8 - 0x10];
	unsigned char m_a8;
};

class Rva005DB004
{
	char m_pad0[0x10];
	int m_10;
	char m_pad1[0x20 - 0x14];
	unsigned char m_20;
	char m_pad2[0x24 - 0x21];
	int m_24;
	char m_pad3[0x38 - 0x28];
	Target005DB004* m_38;
public:
	void rva005DB004();
};

void Rva005DB004::rva005DB004()
{
	m_38->m_8 = m_10;
	m_38->m_c = m_24;
	m_38->m_a8 = m_20;
}
