// cl: /Ob0

// The BFME1 donor baked its own vtable VA as a literal, which cannot
// transfer (same repair as Rva0081C2F0Set): the address of a sacrificial
// anchor stands in (mov-imm-DIR32, patched from retail).
static int Rva005B1A00VTableAnchor;

class Rva005B1A00
{
	void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	char m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
	int m_34;
	int m_38;

public:
	Rva005B1A00();
};

Rva005B1A00::Rva005B1A00()
{
	m_vptr = (void *)&Rva005B1A00VTableAnchor;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
}
