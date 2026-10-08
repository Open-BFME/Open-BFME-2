// cl: /MD /EHsc
// ??1Rva0043283C@@QAE@XZ, retail 0x0043283C, 28 bytes.
// Dtor stores derived vtable 0x00C3CA28, clears singleton 0x00E032C8 if it holds this, stores base vtable 0x00BDBA74. Evidence: caller 0x00432A1F deleting dtor, base vtable RVA 0x007DBA74 matches BfmeOwnVVD base, singleton matches g_Va00E032C8.
class Rva0043283CBase
{
public:
	Rva0043283CBase() { }
	~Rva0043283CBase() { }
	virtual void rva0043283CSlot0();
};

// The 0x18-byte entries the constructor builds through the vector constructor
// iterator; their constructor is 0x00432976 (rowed under the fold name
// Rva005A6560::reset): bit 0 of +0x14 and +0x00/+0x0C/+0x10 cleared.
struct Rva0043283CEntry
{
	Rva0043283CEntry();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_flag14 : 1;
};

class Rva0043283C : public Rva0043283CBase
{
public:
	Rva0043283C();
	~Rva0043283C();
private:
	int m_04;
	Rva0043283CEntry m_entries08[0x14];		// +0x08
	int m_1e8;
	bool m_1ec;
	int m_1f0;
	int m_1f4;
	int m_1f8;
	int m_1fc;
	int m_200;
};

extern int g_Va00E032C8;
extern "C" void *__cdecl memset(void *dst, int value, unsigned int count);

// ??0Rva0043283C@@QAE@XZ, retail 0x00432987..0x00432A1F (152 bytes, EH):
// WorldBuilder's AptTranslator::AptTranslator (AptTranslator.cpp, which asserts
// "This is a singleton, why are you creating more?"). The base (EH state 0),
// vtable 0x00C3CA28, twenty entries through the vector constructor iterator,
// the scalar fields, and -- only when no instance exists yet -- the singleton
// 0x00E032C8 takes this and +0x04 and the entries are zeroed.
Rva0043283C::Rva0043283C()
{
	m_1e8 = 0;
	m_1ec = false;
	m_1f0 = 2;
	m_1f4 = 0;
	m_1f8 = 0;
	m_1fc = 0;
	m_200 = 0;
	if (g_Va00E032C8 == 0)
	{
		g_Va00E032C8 = (int)this;
		memset(&m_04, 0, sizeof(m_04));
		memset(m_entries08, 0, sizeof(m_entries08));
	}
}

Rva0043283C::~Rva0043283C()
{
	if (g_Va00E032C8 == (int)this)
		g_Va00E032C8 = 0;
}
