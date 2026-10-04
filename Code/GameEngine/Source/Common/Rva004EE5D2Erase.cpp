// cl: /O1 /MD
//
// ?rva004EE5D2@Rva004EE5D2@@QAEXXZ @0x004EE5D2 195B
// Removes 8 embedded entries via rowed ?rva002B7250@Rva002B7250@@QAEXPAVCreateAHeroData@@@Z:
// 4 from Rva002BA8F1Logic members, 3 from globals, 1 from member pointer.
// Evidence: packet disassembly order and offsets, callers 0x004EE695/0x004EE78A.

class CreateAHeroData
{
public:
	int m_x;
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;
Rva002B7250 g_00E04424;
extern Rva002B7250 g_00E02E88;
Rva002B7250 g_00E044F0;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

extern "C" __declspec(dllimport) long __cdecl time(long *t);

class Rva004EE5D2
{
public:
	void rva004EE5D2();
	void rva004EE695();
	void rva004EE78A();
private:
	int m_0;
	CreateAHeroData m_4;
	CreateAHeroData m_8;
	CreateAHeroData m_c;
	CreateAHeroData m_10;
	CreateAHeroData m_14;
	CreateAHeroData m_18;
	CreateAHeroData m_1c;
	CreateAHeroData m_20;
	Rva002B7250 *m_24;
	char m_pad28[0x48];
	int m_70;
	char m_pad74[0x84];
	unsigned char m_f8;
};

void Rva004EE5D2::rva004EE5D2()
{
	((Rva002B7250 *)((char *)g_009FEF10 + 0x1c))->rva002B7250(this ? &m_4 : (CreateAHeroData *)0);
	((Rva002B7250 *)((char *)g_009FEF10 + 0x2c))->rva002B7250(this ? &m_c : (CreateAHeroData *)0);
	((Rva002B7250 *)((char *)g_009FEF10 + 0x3c))->rva002B7250(this ? &m_10 : (CreateAHeroData *)0);
	((Rva002B7250 *)((char *)g_009FEF10 + 0x4c))->rva002B7250(this ? &m_1c : (CreateAHeroData *)0);
	g_00E04424.rva002B7250(this ? &m_8 : (CreateAHeroData *)0);
	g_00E02E88.rva002B7250(this ? &m_14 : (CreateAHeroData *)0);
	g_00E044F0.rva002B7250(this ? &m_20 : (CreateAHeroData *)0);
	m_24->rva002B7250(this ? &m_18 : (CreateAHeroData *)0);
}

void Rva004EE5D2::rva004EE695()
{
	if (g_009FEF10 != 0 && ((BfmeSelectionState *)g_009FEF10)->isSelectionLocked() != 0)
		m_70 = time(0);
	else
		m_70 = 0;
	if (m_f8 != 0)
		return rva004EE5D2();
}

void Rva004EE5D2::rva004EE78A()
{
	if (m_f8 != 0)
		return;
	m_f8 = 1;
	return rva004EE5D2();
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00E02E88@@3VRva002B7250@@A=?g_registryAtE02E88@@3VRva002B7250@@A")
