// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// BFME2 record layouts recovered from complete retail copy constructors.
// These use STLport basic_string<char> (12 bytes), copied by 0x9170.
// Application names and scalar meanings remain unknown. Padding is not copied.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <memory>
#include <string>

// Complete retail record copy at 0x00079C23.
struct BfmeNarrowRecord00079C23 {
    _STL::basic_string<char> text0, text1, text2; unsigned int word0, word1;
    BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23 &o);
};
BfmeNarrowRecord00079C23::BfmeNarrowRecord00079C23(const BfmeNarrowRecord00079C23 &o) : text0(o.text0), text1(o.text1), text2(o.text2), word0(o.word0), word1(o.word1) {}
template void _STL::_Construct<BfmeNarrowRecord00079C23,BfmeNarrowRecord00079C23>(BfmeNarrowRecord00079C23*,const BfmeNarrowRecord00079C23&);

// Complete retail record copy at 0x000BFDC7.
struct BfmeNarrowRecord000BFDC7 {
    unsigned int word0; _STL::basic_string<char> text; unsigned int word1, word2, word3, word4;
    BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7 &o);
};
BfmeNarrowRecord000BFDC7::BfmeNarrowRecord000BFDC7(const BfmeNarrowRecord000BFDC7 &o) : word0(o.word0), text(o.text), word1(o.word1), word2(o.word2), word3(o.word3), word4(o.word4) {}
template void _STL::_Construct<BfmeNarrowRecord000BFDC7,BfmeNarrowRecord000BFDC7>(BfmeNarrowRecord000BFDC7*,const BfmeNarrowRecord000BFDC7&);

// Complete retail record copy at 0x0041A5D2.
#include "BfmeNarrowRecord0041A5D2.h"
BfmeNarrowRecord0041A5D2::BfmeNarrowRecord0041A5D2(const BfmeNarrowRecord0041A5D2 &o) : text0(o.text0), short0(o.short0), text1(o.text1) {}
BfmeNarrowRecord0041A5D2::BfmeNarrowRecord0041A5D2() {}
BfmeNarrowRecord0041A5D2 &BfmeNarrowRecord0041A5D2::operator=(const BfmeNarrowRecord0041A5D2 &o)
{
	text0.assign(o.text0);
	short0 = o.short0;
	text1.assign(o.text1);
	return *this;
}
template void _STL::_Construct<BfmeNarrowRecord0041A5D2,BfmeNarrowRecord0041A5D2>(BfmeNarrowRecord0041A5D2*,const BfmeNarrowRecord0041A5D2&);

// Complete retail record copy at 0x0041A617.
#include "BfmeNarrowRecord0041A617.h"
BfmeNarrowRecord0041A617::BfmeNarrowRecord0041A617(const BfmeNarrowRecord0041A617 &o) : text(o.text), short0(o.short0), flag(o.flag) {}
BfmeNarrowRecord0041A617 &BfmeNarrowRecord0041A617::operator=(const BfmeNarrowRecord0041A617 &o)
{
	text.assign(o.text);
	short0 = o.short0;
	flag = o.flag;
	return *this;
}
template void _STL::_Construct<BfmeNarrowRecord0041A617,BfmeNarrowRecord0041A617>(BfmeNarrowRecord0041A617*,const BfmeNarrowRecord0041A617&);

// Complete retail record copy at 0x00427F75.
struct BfmeNarrowRecord00427F75 {
    _STL::basic_string<char> text0, text1;
    BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &o);
};
BfmeNarrowRecord00427F75::BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &o) : text0(o.text0), text1(o.text1) {}
template void _STL::_Construct<BfmeNarrowRecord00427F75,BfmeNarrowRecord00427F75>(BfmeNarrowRecord00427F75*,const BfmeNarrowRecord00427F75&);

// Complete retail record copy at 0x0054FEF1.
struct BfmeNarrowRecord0054FEF1 {
    _STL::basic_string<char> text; unsigned int word0, word1;
    BfmeNarrowRecord0054FEF1(const BfmeNarrowRecord0054FEF1 &o);
    BfmeNarrowRecord0054FEF1 &operator=(const BfmeNarrowRecord0054FEF1 &o);
};
BfmeNarrowRecord0054FEF1::BfmeNarrowRecord0054FEF1(const BfmeNarrowRecord0054FEF1 &o) : text(o.text), word0(o.word0), word1(o.word1) {}
BfmeNarrowRecord0054FEF1 &BfmeNarrowRecord0054FEF1::operator=(const BfmeNarrowRecord0054FEF1 &o)
{
	text.assign(o.text);
	word0 = o.word0;
	word1 = o.word1;
	return *this;
}
template void _STL::_Construct<BfmeNarrowRecord0054FEF1,BfmeNarrowRecord0054FEF1>(BfmeNarrowRecord0054FEF1*,const BfmeNarrowRecord0054FEF1&);

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:??0Pivot24@@QAE@ABU0@@Z=??0BfmeNarrowRecord00427F75@@QAE@ABU0@@Z")
#pragma comment(linker, "/alternatename:??0VersionBlockEntry@@QAE@ABU0@@Z=??0BfmeNarrowRecord00427F75@@QAE@ABU0@@Z")

#include <deque>

struct BfmePod16
{
	BfmePod16(const BfmePod16 &);
	~BfmePod16();
};

class Rva0041A63A
{
public:
	void rva0041A63A();
};

void Rva0041A63A::rva0041A63A()
{
	((_STL::deque<BfmeNarrowRecord0041A5D2> *)this)->~deque();
}

class Rva0041A63F
{
public:
	void rva0041A63F();
};

void Rva0041A63F::rva0041A63F()
{
	((_STL::deque<BfmeNarrowRecord0041A617> *)this)->~deque();
}

class Rva0054FF9B
{
public:
	void rva0054FF9B();
};

void Rva0054FF9B::rva0054FF9B()
{
	((_STL::deque<BfmePod16> *)this)->~deque();
}

class Rva0054FFA0
{
public:
	void rva0054FFA0();
};

void Rva0054FFA0::rva0054FFA0()
{
	((_STL::deque<BfmePod16> *)this)->~deque();
}

