// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??4BfmeVectorRecord000BDF17@@QAEAAU0@ABU0@@Z at 0x000BDFAC (123B). Copy-assign the 64-byte record beside 0xBDF17.
// Evidence: same offsets as the rowed copy-ctor TU (names at +0, text0 at +0xC, text1 at +0x10, scalars to +0x3C);
// self-check plus text0/text1/vector-assign order read from retail; 0x40 stride at caller 0xC0D13.
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
#include "ascii_string.h"

namespace _STL
{
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &);
}

struct BfmeVectorRecord000BDF17 {
	_STL::vector<AsciiString> names;
	AsciiString text0;
	AsciiString text1;
	unsigned int word14;
	unsigned int word18;
	unsigned int word1C;
	unsigned int word20;
	unsigned int word24;
	unsigned int word28;
	unsigned char flag2C;
	unsigned char flag2D;
	unsigned int word30;
	unsigned int word34;
	unsigned int word38;
	unsigned char flag3C;
	BfmeVectorRecord000BDF17 &operator=(const BfmeVectorRecord000BDF17 &o);
};

BfmeVectorRecord000BDF17 &BfmeVectorRecord000BDF17::operator=(const BfmeVectorRecord000BDF17 &o)
{
	if (this == &o)
		return *this;
	text0 = o.text0;
	text1 = o.text1;
	names = o.names;
	word14 = o.word14;
	word18 = o.word18;
	word1C = o.word1C;
	word20 = o.word20;
	word24 = o.word24;
	word28 = o.word28;
	flag2C = o.flag2C;
	flag2D = o.flag2D;
	word30 = o.word30;
	word34 = o.word34;
	word38 = o.word38;
	flag3C = o.flag3C;
	return *this;
}
