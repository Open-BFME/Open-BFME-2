// flags: region default (reverse/retail_inventory/flag_regions.csv)
// NAT::setConnectionState, 0x005A688C, 119B (WorldBuilder name, its
// __FUNCTION__ string "NAT::setConnectionState"). Unlock wrapper that caches two (a,b) pairs at +0x94C/+0x950 and forwards 4/5->3/4 to Rva005DC3C1 at +0x28. Evidence: caller 0x005A6C90 passes [ecx+14]/[ecx+18]/[ecx+20]; callee row 0x005DC3C1; neighbours 0x005A687F/0x005A6A83.
class Rva005DC3C1
{
public:
	void rva005DC3C1(unsigned short a, unsigned short b, int expected, int newVal);
};
// A slot's address (+0x38 in each slot of the list at NAT +0x08).
struct Rva005A6A4CAddress
{
	unsigned int ip;
	unsigned int port;
};
struct Rva005A6A4CSlot
{
	char m_pad00[0x38];
	Rva005A6A4CAddress m_address;
};
class NAT
{
public:
	void setConnectionState(int a, int b, int expected, int val);
	void rva005A6C90(int val);
	void rva005A6A4C();
private:
	char m_pad00[0x8];
	Rva005A6A4CSlot **m_8;
	char m_pad0C[0x14 - 0xC];
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	Rva005DC3C1 m_28;
	char m_pad2C[0x90C - 0x2C];
	Rva005A6A4CAddress *m_90C[8];
	char m_pad92C[0x94C - 0x92C];
	int m_94C;
	int m_950;
};
void NAT::setConnectionState(int a, int b, int expected, int val)
{
	if (a == b)
		return;
	if (a < 0 || a >= 8 || b < 0 || b >= 8)
		return;
	if (a == m_14)
	{
		if (b == m_18)
		{
			if (expected != m_20)
				return;
			m_94C = val;
		}
		else
			goto checkSwap;
	}
	else
	{
checkSwap:
		if (a != m_18)
			goto notify;
		if (b != m_14)
			goto notify;
		if (expected != m_20)
			return;
		m_950 = val;
	}
notify:
	if (val == 5)
		m_28.rva005DC3C1((unsigned short)a, (unsigned short)b, expected, 4);
	else if (val == 4)
		m_28.rva005DC3C1((unsigned short)a, (unsigned short)b, expected, 3);
}
void NAT::rva005A6C90(int val)
{
	setConnectionState(m_14, m_18, m_20, val);
}

// NAT::rva005A6A4C @0x005A6A4C 55B (unnamed in WB): with a slot list (+0x08),
// every present slot takes its address (+0x38, 8 bytes) from the matching
// entry of the address pointers at +0x90C. GameSpyStagingRoom::launchGame
// (0x004FE126) and 0x004FED35 call it on TheNAT before attaching its transport.
void NAT::rva005A6A4C()
{
	if (m_8 != 0) {
		for (int i = 0; i < 8; ++i) {
			Rva005A6A4CSlot *slot = m_8[i];
			if (slot != 0)
				slot->m_address = *m_90C[i];
		}
	}
}
