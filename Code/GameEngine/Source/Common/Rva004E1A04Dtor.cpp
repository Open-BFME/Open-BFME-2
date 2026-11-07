// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva004E1A04@@QAE@XZ, RVA 0x004E1A04, 47B: non-virtual dtor of the 16-byte
// element of the LivingWorld campaign act's +0x90 vector. Callers at
// 0x004E1A87/0x0052BBBE/0x0052CEE6 plus jmps. Owner unproven, so the name stays
// address-derived.
// Target facts: two calls to 0x00036410 on `this` (rowed both as ~StringBase and
// as its ICF twin releaseBuffer), the first under EH state 0 and the second
// under state -1. The element's copy, 0x0052BEC9 through the act's construct
// helper 0x0052C404, copies a string at +0 and three dwords at +4/+8/+0xC.
// Structural inference: a string member at +0 that the dtor body clears
// (AsciiString::clear calls 0x00036410), then the member's own destructor;
// the dwords' types are unknown.
#include "ascii_string.h"

class Rva004E1A04
{
public:
	~Rva004E1A04();
private:
	AsciiString m_00;
	int m_04;
	int m_08;
	int m_0C;
};

Rva004E1A04::~Rva004E1A04()
{
	m_00.clear();
}
