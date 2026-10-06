// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0Rva005C663C@@QAE@XZ @ 0x005C663C 108B
// Ctor storing vtable 0x00C74914, zeroing +4 and two floats, formatting the
// AsciiString at +8 with "Flash%d" and a global counter, then firing
// CreateButtonFlash and ShowButtonFlash. Evidence: vtable store at [this];
// counter global 0x00E065C0 with inc; string literal Flash%d; callees rowed
// (format 0x00038150, Create 0x003FECFE, Show 0x003FEDDB); caller 0x005C6F58;
// layout matches neighbour Rva005C6599 (+8 AsciiString, +C/+10 floats);
// owner class unproven (honest Rva name).
#include "ascii_string.h"

void __cdecl Rva003FECFECreateButtonFlash(void **pp);
void __cdecl Rva003FEDDBShowButtonFlash(void **pp);
extern int g_00E065C0;

class RvaBase
{
public:
	RvaBase() : m_4(0) {}
	~RvaBase();
	int m_4;
};

class Rva005C663C : public RvaBase
{
public:
	virtual ~Rva005C663C();
	Rva005C663C();
private:
	AsciiString m_8;
	float m_C;
	float m_10;
};

Rva005C663C::Rva005C663C() : m_C(0.0f), m_10(0.0f)
{
	int id = g_00E065C0++;
	m_8.format("Flash%d", id);
	Rva003FECFECreateButtonFlash((void **)&m_8);
	Rva003FEDDBShowButtonFlash((void **)&m_8);
}
