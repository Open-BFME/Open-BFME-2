// cl: /O1 /G7
// ?rva005A6A83@Rva005A6A83@@QAEXXZ @0x005A6A83 145B. Firewall NAT probe:
// pre-check ++m_936==0 skips to open; loop two getNextTemporarySourcePort(0)
// until second==first+1; openSpareSocket(m_936); ++m_934; sendToMangler
// via rowed 0x0059517F (addr +0x944, ports +0x936/+0x934, dest 4321, false);
// stamp +0x938 with timeGetTime()+g_00DD35BC. Evidence: callers 0x005A8511
// 0x005A8614; callees rowed 0x0059539B/0x00595089/0x0059517F and IAT
// timeGetTime; globals g_a063b0 (Rva00A063B0Obj *) and g_00DD35BC.
typedef unsigned short UnsignedShort;
typedef int Int;
typedef bool Bool;
typedef unsigned long UnsignedLong;

struct Rva00A063B0Obj;
extern Rva00A063B0Obj *g_a063b0;
extern UnsignedLong g_00DD35BC;
extern "C" __declspec(dllimport) UnsignedLong __stdcall timeGetTime(void);

class FirewallHelperClass
{
public:
	UnsignedShort getNextTemporarySourcePort(Int skip);
	Bool openSpareSocket(UnsignedShort port);
};

class Rva0059517F
{
public:
	Bool rva0059517F(UnsignedLong address, UnsignedShort port, UnsignedShort packetID, UnsignedShort destPort, Bool blitzme);
};

class Rva005A6A83
{
public:
	void rva005A6A83();

private:
	unsigned char m_pad00[0x934];
	UnsignedShort m_port934;                // +0x934
	UnsignedShort m_port936;                // +0x936
	UnsignedLong m_time938;                 // +0x938
	unsigned char m_pad93C[0x944 - 0x93C];
	UnsignedLong m_addr944;                 // +0x944
};

void Rva005A6A83::rva005A6A83()
{
	unsigned int p = m_port936;
	++p;
	if (p == 0)
		goto open;
	while (true)
	{
		m_port936 = ((FirewallHelperClass *)g_a063b0)->getNextTemporarySourcePort(0);
		unsigned int second = ((FirewallHelperClass *)g_a063b0)->getNextTemporarySourcePort(0);
		unsigned int firstPlusOne = (unsigned int)m_port936 + 1u;
		if (second == firstPlusOne)
			break;
	}
open:
	((FirewallHelperClass *)g_a063b0)->openSpareSocket(m_port936);
	++m_port934;
	((Rva0059517F *)g_a063b0)->rva0059517F(m_addr944, m_port936, m_port934, 4321, false);
	m_time938 = timeGetTime() + g_00DD35BC;
}
