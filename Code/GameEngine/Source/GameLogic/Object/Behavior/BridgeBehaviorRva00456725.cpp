// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva00456725@Rva00456725@@QAE?AVAsciiString@@HH@Z @ 0x00456725 40B thiscall bridge string copy via StringBase copy
// Evidence: caller 0x00456B0C; rowed callee 0x000365F0 StringBase copy; sibling 0x00456774 UDT return O1 G7 EHsc.
#include "ascii_string.h"

class Rva00456725
{
public:
	char _pad[0xA4];
	AsciiString m_strings[80];
	AsciiString rva00456725(int a, int b);
};

AsciiString Rva00456725::rva00456725(int a, int b)
{
	int idx = a;
	idx *= 3;
	idx += b;
	return m_strings[idx];
}
