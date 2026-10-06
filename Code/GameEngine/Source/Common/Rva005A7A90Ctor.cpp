// cl: /Ob0

// The BFME1 donor baked its own vtable VA as a literal, which cannot
// transfer (same repair as Rva0081C2F0Set): the address of a sacrificial
// anchor stands in (mov-imm-DIR32, patched from retail).
static int Rva005A7A90VTableAnchor;

class Rva005A7A90
{
	void *m_vptr;
	int m_04;
	char m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	char m_2C;

public:
	Rva005A7A90();
};

Rva005A7A90::Rva005A7A90()
{
	m_vptr = (void *)&Rva005A7A90VTableAnchor;
	m_04 = 0;
	m_08 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}
