// ?rva0031912E@Rva0031912E@@QAEHXZ
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Rva0031912E::rva0031912E() at retail 0x0031912E (43B): an unlock-lane
// predicate. With the AsciiString at +0x18 non-empty (rowed
// StringBase<char>::isEmpty, 0x00001E2F) it tests whether the span of the
// begin/end dword pair at +0x40/+0x44 of the object at +0x78 is below 8
// (difference masked with ~7). Callers: 0x002B4CAF, 0x00319621, 0x003FDD30.
//
// Codegen: retail reads +0x44 first and then addresses +0x40 through an
// incremented base register; folding the pair into a small begin/end range
// struct (so the span is computed from the range's own members) reproduces
// that, where the two raw dword reads fold into one displacement.
#include "ascii_string.h"

struct Rva0031912ERange
{
	int m_begin;
	int m_end;
};

struct Rva0031912EInner
{
	char m_pad[0x40];
	Rva0031912ERange m_range;
};

class Rva0031912E
{
public:
	int rva0031912E();
	char m_pad00[0x18];
private:
	AsciiString m_str; // +0x18
	char m_pad1C[0x5C];
	Rva0031912EInner *m_78; // +0x78
};

int Rva0031912E::rva0031912E()
{
	if (((const StringBase<char> *)&m_str)->isEmpty() != 0) {
		const Rva0031912ERange &r = m_78->m_range;
		int v = r.m_end - r.m_begin;
		if ((v & 0xFFFFFFF8) == 0)
			return 1;
	}
	return 0;
}
