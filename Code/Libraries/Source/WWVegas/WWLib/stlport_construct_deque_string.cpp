// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Fifth batch of STLport _Construct<T> placement-copy helpers, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own rowed copy ctor, and __EH_prolog resolves via its matched row.
// The nested deque reuses the established 4-byte BfmeWordValue4 model; the
// string pair uses the real STLport basic_string with an unsigned payload,
// matching the retail pair encoding exactly.

#include <memory>
#include <deque>
#include <string>

struct BfmeWordValue4
{
	unsigned int bits;
	BfmeWordValue4();
	~BfmeWordValue4() {}
};

typedef _STL::deque<BfmeWordValue4, _STL::allocator<BfmeWordValue4> > ConstructInnerDeque;
typedef _STL::deque<ConstructInnerDeque, _STL::allocator<ConstructInnerDeque> > ConstructOuterDeque;
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > ConstructStdString;
typedef _STL::pair<const ConstructStdString, unsigned int> ConstructPairSU;

template void _STL::_Construct<ConstructOuterDeque, ConstructOuterDeque>(ConstructOuterDeque *, const ConstructOuterDeque &);
template void _STL::_Construct<ConstructPairSU, ConstructPairSU>(ConstructPairSU *, const ConstructPairSU &);
