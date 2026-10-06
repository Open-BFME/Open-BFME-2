// cl: /Ob0

// The BFME1 donor baked its own vtable VA as a literal, which cannot
// transfer (same repair as Rva0081C2F0Set): the address of a sacrificial
// anchor stands in (mov-imm-DIR32, patched from retail).
static int Rva00161220VTableAnchor;

class Rva00161220
{
	void *m_vptr;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	char m_18;
	int m_1C;
	int m_20;
	int m_24;
	char m_28;
	char m_29;
	char m_2A;
	int m_2C;

public:
	Rva00161220();
};

Rva00161220::Rva00161220()
{
	m_vptr = (void *)&Rva00161220VTableAnchor;
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
	m_29 = 0;
	m_2A = 0;
	m_2C = 0;
}
