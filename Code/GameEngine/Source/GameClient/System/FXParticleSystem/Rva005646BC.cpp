// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
// ??0Rva005646BC@@QAE@IAAUSrc005646BC@@@Z, retail 0x005646BC, 135 bytes.
// Copy-from-template ctor twin of the 0x0056413D shape: base Rva003ADEBF via
// rowed uint ctor 0x005640EC, subobject defaults at +0x10/+0x14/+0x18/+0x1c,
// final vtables Rva003AE2CF_v0 / s_slot3E4first / Rva003AE2CF_v10, float via
// rowed GameClientRandomVariable::getValue 0x002341A1, FX via just-landed
// Rva0056468E::rva0056468E 0x0056468E, bytes from +0x1d/+0x34, flag at +0x20.
// Evidence: calls 0x0056468E at 0x00564719; caller at 0x003ACB36.

#include "ascii_string.h"

class FXList
{
};

class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

class Rva0056468E
{
public:
	const FXList *rva0056468E();
public:
	char m_pad0[4];
	AsciiString m_eventName;
	GameClientRandomVariable m_rand;
	bool m_b14;
	char m_pad15[3];
	const FXList *m_cached;
};

struct Src005646BC
{
	char m_pad0[0x1d];
	bool m_1d;
	char m_pad1e[2];
	Rva0056468E m_info;
};

class Rva003ADEBF
{
public:
	Rva003ADEBF(unsigned int a);
	~Rva003ADEBF();
public:
	void *m_v0;
	unsigned int m_arg4;
	void *m_v8;
	bool m_flagC;
};

// Rva003AE2CF_v0: matched references place it at VA 0xc1d3a0 (retail .rdata value 60).
extern "C" char Rva003AE2CF_v0 = 60;
extern "C" char s_slot3E4first;
// Rva003AE2CF_v10: matched references place it at VA 0xc1d390 (retail .rdata value -117).
extern "C" char Rva003AE2CF_v10 = -117;
extern char g_00C1D3B0;
// g_00C1D3B0: matched references place it at VA 0xc1d3b0 (retail .rdata value -3).
char g_00C1D3B0 = -3;

struct Rva005646BCSub
{
	Rva005646BCSub() : m_10((void *)&g_00C1D3B0), m_14(0.0f), m_18(0), m_1c(false) {}
	~Rva005646BCSub();
	void *m_10;
	float m_14;
	const FXList *m_18;
	bool m_1c;
};

class Rva005646BC : public Rva003ADEBF, public Rva005646BCSub
{
public:
	Rva005646BC(unsigned int a, struct Src005646BC &src);
	~Rva005646BC();
private:
	bool m_20;
};

Rva005646BC::Rva005646BC(unsigned int a, struct Src005646BC &src)
	: Rva003ADEBF(a), Rva005646BCSub()
{
	*(void **)this = (void *)&Rva003AE2CF_v0;
	*(void **)((char *)this + 8) = (void *)&s_slot3E4first;
	m_10 = (void *)&Rva003AE2CF_v10;
	float v = src.m_info.m_rand.getValue();
	m_14 = v;
	m_18 = src.m_info.rva0056468E();
	m_1c = src.m_info.m_b14;
	m_flagC = src.m_1d;
	m_20 = true;
}
// _s_slot3E4first: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_s_slot3E4first=?vftable_0112B89C@@3HA")
