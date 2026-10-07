// cl: /Ireference/shims/bfme2_ascii /GX- /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva002C6EA4@Rva002C6EA4@@QAE_NABVAsciiString@@@Z @0x002C6EA4 31B
// Evidence: unlock lane prev stlport rb_tree next stlport map caller
// 0x002C7196 callee Rb_tree AsciiString pair _M_find row offsets 0x17c map
// member plus 0x17c header ret 4 one AsciiString arg returning bool.
// Identity: honest-address thiscall method with one const AsciiString arg.
#pragma optimize("t", on)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#pragma optimize("", on)
#include "ascii_string.h"

class Rva002C6EA4
{
public:
	bool rva002C6EA4(const AsciiString &key);

private:
	char m_pad[0x17C];
	_STL::map<AsciiString, AsciiString> m_map;
};

bool Rva002C6EA4::rva002C6EA4(const AsciiString &key)
{
	return m_map.find(key) != m_map.end();
}
