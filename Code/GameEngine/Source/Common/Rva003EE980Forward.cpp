// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva003EE980@Rva003EE980@@QAEXH@Z @0x003EE980 87B. Unlock lane: three-call
// forward with string g_Rva00E02E84 and triple-float struct from
// 0.95f; arg+0x44; caller at 0x004FF21E. Prev/next are the
// Rva003EE966/A1A family (// cl: /O1 /MD) plus /arch:SSE for movss.
#include <map>

typedef int Int;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, bool b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35FF
{
public:
	void rva004E35FF(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

// Matched DIR32 witness places this one-pointer AsciiString at VA 0x00E02E84
// in the zero-filled .data tail; the shared BFME2 header establishes its
// four-byte layout and the retail initial bytes are zero. Its retail dynamic
// initializer (0x007AF9BB) constructs it from "UnifiedEffect" through the
// out-of-line AsciiString(const char *) at 0x0000654A, as in
// Rva003EE900Forward.cpp.
#pragma inline_depth( 0 )
AsciiString g_Rva00E02E84("UnifiedEffect");
// P32 TEST-BRANCH-ONLY diagnostic: retail builds every effect-name string before 0x007AF9D6 fills the
// LivingWorldRegionEffects FieldParse entries; this image runs that fill earlier (bridged), so fill again here.
void initializeRegionEffectFields();
// ?<s_p32RegionEffectFieldsDiag> absent-from-retail
static int s_p32RegionEffectFieldsDiag = (initializeRegionEffectFields(), 0);
#pragma inline_depth()

class Rva003EE980
{
public:
	void rva003EE980(Int region);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE980::rva003EE980(Int region)
{
	char *p = (char *)region + 0x44;
	float f = 0.95f;
	float color[3];
	color[0] = f;
	color[1] = f;
	color[2] = f;
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E84, (Int)p, (Int)&color[0]);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E84, 1);
}

// ?disableUnifiedEffect@Rva003EE9D7@@QAEXH@Z @0x003EE9D7 26B. Clearing twin of the
// forward above, and skeleton twin of Rva003EE900 (Rva003EE900Forward.cpp):
// one rowed 0x004E35D5 call on the owner map at this+8 with string
// g_Rva00E02E84 and (arg+0x44, 0).
class Rva003EE9D7
{
public:
	void disableUnifiedEffect(Int region);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE9D7::disableUnifiedEffect(Int region)
{
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)((char *)region + 0x44), 0);
}
