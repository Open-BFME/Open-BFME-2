// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?rva0045674D@Rva0045674D@@QAE?AVAsciiString@@HH@Z @ 0x0045674D 39B thiscall bridge string copy via StringBase copy
// Evidence: caller 0x00456B52; rowed callee 0x000365F0 StringBase copy; finish from stash 0.94 plus sibling G7 recipe.
#include "ascii_string.h"

class Rva0045674D
{
public:
	AsciiString m_strings[80];
	AsciiString rva0045674D(int a, int b);
};

AsciiString Rva0045674D::rva0045674D(int a, int b)
{
	int idx = a + 19;
	idx *= 3;
	idx += b;
	return m_strings[idx];
}
