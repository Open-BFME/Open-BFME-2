// ?rva0040A5CF@Rva0040A5CFRange@@QAEPAXABVAsciiString@@@Z
// partial score=0.9 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ?rva0040A5CF@Rva0040A5CFRange@@QAEPAXABVAsciiString@@@Z @0x0040A5CF 52B.
// Thiscall lookup over the [first,last) pair at +0/+4: passes both bounds and
// a copy of the key to the unrowed cdecl 0x0040A54C (pinned by its REL32 at
// 0x0040A5EB), returns the stored word at the match, or null when the match is
// the end. Evidence: target only; the names are address-derived.
#include "ascii_string.h"

void *rva0040A54C(void *first, void *last, AsciiString key);

class Rva0040A5CFRange
{
public:
	void *rva0040A5CF(const AsciiString &key);

private:
	void *m_first;
	void *m_last;
};

void *Rva0040A5CFRange::rva0040A5CF(const AsciiString &key)
{
	void *found = rva0040A54C(m_first, m_last, key);
	if (found == m_last)
		return 0;
	return *(void **)found;
}
