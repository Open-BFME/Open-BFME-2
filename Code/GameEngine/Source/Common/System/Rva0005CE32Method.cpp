// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0005CE32@Rva0005CE32@@QAEXABVAsciiString@@@Z 0x0005CE32 65B evidence: erase 0x0005B5EA via AsciiString; float m_9c vs g_Va00BBB8D8; spaces fill 48B at +0x188; caller 0x0005E19F in 0x0005E168; prev XferUnicodeStringVector same flags
#include "ascii_string.h"
extern float g_Va00BBB8D8;
namespace _STL
{
// Declare the AsciiString set-tree erase owned by
// stlport_asciistring_set_base.cpp so this TU calls it without emitting
// its own copies of the _Rb_tree inline members.
template <class T> struct _Identity;
template <class T> struct less;
template <class T> class allocator;
template <class K, class V, class KoV, class Cmp, class Al> class _Rb_tree
{
	char _opaque[12];
public:
	unsigned int erase(const AsciiString &x);
};
}
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>, _STL::less<AsciiString>, _STL::allocator<AsciiString> > AsciiStringSetTree;
class Rva0005CE32
{
	char _pad[0x9c];
	float m_9c;
	AsciiStringSetTree m_a0;
	char _pad2[0x188 - 0xa0 - sizeof(AsciiStringSetTree)];
	char m_188[48];
public:
	void rva0005CE32(const AsciiString &s);
};
void Rva0005CE32::rva0005CE32(const AsciiString &s)
{
	if (m_a0.erase(s) <= 0)
		return;
	if (m_9c == g_Va00BBB8D8)
		return;
	for (int i = 0; i < 12; i++)
		((unsigned *)m_188)[i] = 0x2020202;
}
