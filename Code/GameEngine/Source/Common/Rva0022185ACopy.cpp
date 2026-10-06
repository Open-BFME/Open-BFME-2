// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD
// ??0Rva0022185A@@QAE@ABV0@@Z @0x0022185A 33B
// Copy ctor with AsciiString at +0 via StringBase copy 0x000365F0
// plus int at +4 and byte at +8. No vptrs.
// Evidence: retail bytes caller 0x00221A9E unblocks 0x00221A58.
#include "ascii_string.h"

class Rva0022185A
{
public:
	Rva0022185A(const Rva0022185A &other);
private:
	AsciiString m_str;
	int m_04;
	unsigned char m_08;
};

Rva0022185A::Rva0022185A(const Rva0022185A &other)
	: m_str(other.m_str)
	, m_04(other.m_04)
	, m_08(other.m_08)
{
}
