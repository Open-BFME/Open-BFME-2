// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ??1Rva0057C04F@@QAE@XZ @0x0057C04F 69B: dtor destroying AsciiString at +8 and Rva0052413E at +0xC.
// Stores vtable 0x0086F2D4 then s_first0C 0x0086FFFC (folded CategoryModuleClass FXParticleSystem).
// Evidence: reverse member destruction order (+0xC then +8) with EH states 1 then 0 proves dtor;
// callees Rva dtor and StringBase releaseBuffer are rowed; unblocks 3 callees; neighbours share FX shard.
//
// ?rva0057C094@Rva0057C04F@@QAEXH@Z @0x0057C094 190B: vslot 1 of vtable 0x0086F2D4 TurnNumber setter.
// Formats APT:_level%u.%s_TurnNumber from +4 level and +8 prefix str then Unicode int format then bfmeSetText false
// then AptCall Go then flag at +0x18. Evidence: same literals and globals as free Rva0057A51CSet plus Go plus slot 1.
#include "ascii_string.h"
#include "unicode_string.h"
#pragma comment(linker, "/alternatename:??_7Base00@@6B@=_s_first0C")
#pragma comment(linker, "/alternatename:?g_Va007C9260@@3QBGB=??_C@_15KNBIKKIN@?$AA?$CF?$AAd?$AA?$AA@")

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12]; // +0x0C size 12 so +0x18 flag follows
};
extern "C" int s_first0C;

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const unsigned short g_Va007C9260[];
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);
struct Base00
{
	virtual void dummy();
	~Base00() {}
};
class Rva0057C04F : public Base00
{
public:
	~Rva0057C04F();
	virtual void dummy();
	void rva0057C094(int turn);
private:
	int m_level04;
	AsciiString m_08; // +0x08
	Rva0052413E m_0C; // +0x0C
	unsigned char m_flag18; // +0x18
};

Rva0057C04F::~Rva0057C04F()
{
}

void Rva0057C04F::rva0057C094(int turn)
{
	AsciiString key;
	key.format("APT:_level%u.%s_TurnNumber", m_level04, m_08.str());
	UnicodeString value;
	value.format(g_Va007C9260, turn);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, false);
	Rva00524EF4AptCall(TheRva00222A8BTarget, (void *)m_level04, m_08.str(), "Go");
	m_flag18 = 1;
}
