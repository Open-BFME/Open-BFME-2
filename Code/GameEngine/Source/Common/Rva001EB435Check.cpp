// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva001EB435@Rva001EB435@@QAE_NXZ @0x001EB435 33B: null-check wrapper over
// bounds-checked vector accessor 0x001EB3A6: if (m_C3!=0) return
// m_04->rva(m_0C)==0 else return m_04->rva(m_0C+1)==0; m_04 at +0x04 points
// to Rva001EB3A6 (vector at +0x18), index base at +0x0C, flag byte at +0xC3;
// tail-called from 0x001EB73C (null fast path) and calls 0x001EB3A6.
// No donor; honest Rva outer; early-return shape gives retail je fallthrough.
#include "ascii_string.h"
struct BfmeAssignRecord36
{
	AsciiString s;
	int a[8];
};
class Rva001EB3A6
{
public:
	BfmeAssignRecord36 *rva001EB3A6(int i);
};
class Rva001EB435
{
public:
	bool rva001EB435();
private:
	char m_00[4];
	Rva001EB3A6 *m_04;
	char m_08[4];
	int m_0C;
	char m_10[0xB3];
	unsigned char m_C3;
};
bool Rva001EB435::rva001EB435()
{
	if (m_C3 != 0)
		return m_04->rva001EB3A6(m_0C) == 0;
	return m_04->rva001EB3A6(m_0C + 1) == 0;
}
