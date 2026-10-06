// ?rva0056D983@Rva0056D983@@QAEHPAX@Z
// partial score=0.8 date=2026-10-06
// cl: /O1 /MD
//
// ?rva0056D983@Rva0056D983@@QAEXXZ @0x0056D983 62B (ret 4 with unused arg).
// Ensure-flag: invoke TheRva00DFEF18 slot-0x24 virtual with the +0xC/+0x10/
// +0x14/+0x18 members, advance to the +0x2A0 flag, enable the global panel
// via rowed 0x0043DB56 when set and flag clear, set flag, return true.
// Honest address-derived name.
class Rva00DFEF18Host
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20();
	virtual void rvaSlot24(int a, int b, int c, int d);
};

extern int g_Va00DFEF18;

class Rva0043DB56ByteOneSetter
{
public:
	void enable();
};

extern int g_Va00E0333C;

class Rva0056D983
{
public:
	int rva0056D983(void *unused);
private:
	char m_pad[0x0C];
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	char m_pad1C[0x2A0 - 0x1C];
	unsigned char m_flag;
};

int Rva0056D983::rva0056D983(void *unused)
{
	(void)unused;
	((Rva00DFEF18Host *)g_Va00DFEF18)->rvaSlot24(m_14, m_18, m_0C, m_10);
	if (m_flag != 0)
		return 1;
	if (g_Va00E0333C != 0)
		((Rva0043DB56ByteOneSetter *)g_Va00E0333C)->enable();
	m_flag = 1;
	return 1;
}
