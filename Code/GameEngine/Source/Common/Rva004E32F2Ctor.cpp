// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva004E32F2@@QAE@ABV0@@Z, retail 0x0052D477, 43 bytes.
// Copy ctor of Rva004E32F2: vptr store plus int at +4 plus byte at +8 plus tree copy at +0xC.
// Evidence: chain lane calls just-landed Rb_tree copy 0x0052D25D; vtable 0x00861F68 stored at [this] matches dtor 0x004E32F2 class; caller 0x0052D4BE.
// Tree member uses 24B private AsciiString so its copy call mangles to the landed Rb_tree<int AsciiString> row; size not in mangling.
#include <map>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
typedef _STL::_Rb_tree<int, _STL::pair<const int, AsciiString>, _STL::_Select1st<_STL::pair<const int, AsciiString> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, AsciiString> > > HAsciiStringMapTree;
class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &that);
	virtual ~Rva004E32F2();
private:
	int m_unk04;
	unsigned char m_unk08;
	HAsciiStringMapTree m_tree0C;
};
Rva004E32F2::Rva004E32F2(const Rva004E32F2 &that) : m_unk04(that.m_unk04), m_unk08(that.m_unk08), m_tree0C(that.m_tree0C)
{
}
