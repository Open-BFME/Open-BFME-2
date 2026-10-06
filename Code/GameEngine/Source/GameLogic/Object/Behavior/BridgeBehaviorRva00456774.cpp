// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva00456774@Rva00456774@@QAE?AVAsciiString@@HH@Z @ 0x00456774 39B thiscall bridge string copy via StringBase copy
// Evidence: caller 0x00456B99; rowed callee 0x000365F0 StringBase copy; sibling 0x0045674D frame recipe UDT return.
#include "ascii_string.h"

class Rva00456774
{
public:
	AsciiString m_strings[80];
	AsciiString rva00456774(int a, int b);
};

AsciiString Rva00456774::rva00456774(int a, int b)
{
	int idx = a + 23;
	idx *= 3;
	idx += b;
	return m_strings[idx];
}
