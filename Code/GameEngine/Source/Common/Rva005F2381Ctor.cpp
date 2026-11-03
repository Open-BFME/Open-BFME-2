// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005F2381@@QAE@XZ, retail 0x005F2381, 49 bytes.
// Evidence: unlock lane; member Rva00330757Member ctor rowed 0x00330757 at +0 plus set<AsciiString> ctor rowed 0x000D3A71 at +0x10; callers at 0x005E6285 0x005E633A 0x005E6589 0x005F52FA 0x005F536B 0x005FB029.
#include <set>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL {
template <> struct less<AsciiString> {
	bool operator()(const AsciiString &left, const AsciiString &right) const {
		return left < right;
	}
};
}

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}

#include "../../Include/Common/Rva00330757Member.h"

class Rva005F2381
{
public:
	Rva005F2381();
private:
	Rva00330757Member m_head00;
	_STL::set<AsciiString> m_set10;
};

Rva005F2381::Rva005F2381() : m_head00(), m_set10()
{
}
