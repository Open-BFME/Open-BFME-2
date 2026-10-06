// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /DNDEBUG
// stlport
// ??0BfmeNarrowRecord00079C23@@QAE@XZ @0x000797C4 87B. Unlock lane: default ctor
// over 3 narrow strings + 2 ints; first two strings from empty literal at
// 0x007BAC1C third default ints zeroed. Evidence: caller 0x000C3C59 builds it
// on stack then copies via rowed ??4BfmeNarrowRecord00079C23 and destroys via
// rowed 0x00079554; callees rowed string cstr+default ctors 0x00009100/0x00007850.
// Prev 0x0007975E next 0x0007981B stlport TUs.
#include <string>

struct BfmeNarrowRecord00079C23
{
	BfmeNarrowRecord00079C23();
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_00;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_0C;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_18;
	int m_24;
	int m_28;
};
BfmeNarrowRecord00079C23::BfmeNarrowRecord00079C23()
	: m_00(""), m_0C(""), m_18(), m_24(0), m_28(0)
{
}
