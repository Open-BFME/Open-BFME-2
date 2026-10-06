// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??4BfmeVectorRecord000C0BEC@@QAEAAU0@ABU0@@Z at 0x000BDD21 (39B). Copy-assign the text/vector/word10 record.
// Evidence: same offsets as the rowed copy-ctor TU (text at +0, names at +0x04, word10 at +0x10);
// retail has no self-check; text then vector then word10 order read from retail.
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

namespace _STL
{
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &);
}

struct BfmeVectorRecord000C0BEC {
	AsciiString text;
	_STL::vector<AsciiString> names;
	unsigned int word10;
	BfmeVectorRecord000C0BEC &operator=(const BfmeVectorRecord000C0BEC &o);
};

BfmeVectorRecord000C0BEC &BfmeVectorRecord000C0BEC::operator=(const BfmeVectorRecord000C0BEC &o)
{
	text = o.text;
	names = o.names;
	word10 = o.word10;
	return *this;
}
