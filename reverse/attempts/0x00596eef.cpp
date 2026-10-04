// ??0Rva00596F18@@QAE@PAX@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc
// ??0Rva00596F18@@QAE@PAX@Z @0x00596EEF 41B.
// Ctor of Rva00596F18 (vtable 0x00870B38): base Rva00573E7C via pin
// 0x00573E7C then zero +0x20/+0x64 bytes and +0x68/+0x6C dwords plus
// arg at +0x70. Evidence: vtable store plus pin base plus ret-4.
struct Rva00573E7C
{
	virtual ~Rva00573E7C();
	Rva00573E7C();

	char m_pad04[0x20 - 4];
	unsigned char m_20;
	char m_pad21[0x60 - 0x21];
};

struct Rva00596F18 : Rva00573E7C
{
	Rva00596F18(void *arg);
	virtual ~Rva00596F18();

	char m_pad60[0x64 - 0x60];
	unsigned char m_64;
	char m_pad65[3];
	int m_68;
	int m_6c;
	void *m_70;
};

// ??0Rva00596F18@@QAE@PAX@Z present-unmatched
Rva00596F18::Rva00596F18(void *arg) : Rva00573E7C()
{
	m_70 = arg;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_20 = 0;
}
