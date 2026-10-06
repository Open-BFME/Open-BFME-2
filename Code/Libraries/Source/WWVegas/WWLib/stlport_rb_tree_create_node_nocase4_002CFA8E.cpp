// cl: /O1 /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@UBfmeStringNoCaseLess@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@Z @0x002CFA8E 34B.
// NoCase _M_create_node: allocates 0x18-byte node via rowed byte allocator
// 0x000307F0 then constructs the pair at +0x10 via rowed dup 0x002CF954
// (object-symbol _Construct<pair<AsciiString,NoCaseTreeValue4>>). Same shape
// as the less<AsciiString> sibling at 0x00221201 in
// stlport_rb_tree_create_nodes2.cpp; comparator here is BfmeStringNoCaseLess
// per stlport_rb_tree_insert_unique_nocase.cpp (declared only: _M_create_node
// never calls it). Caller at 0x002CFE30 clones through source+0x10.
#include <map>
#include <set>
#include <list>
#include <vector>
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};

// ?_M_create_node (NoCaseTree4, dup 0x002CF954)
typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::_Select1st<_STL::pair<const AsciiString, NoCaseTreeValue4> >, BfmeStringNoCaseLess, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > NoCaseTree4CF550;
void __cdecl dup_002CF954(void);
typedef void (__cdecl *NoCaseTree4CF550ConstructFn)(_STL::pair<const AsciiString, NoCaseTreeValue4> *, _STL::pair<const AsciiString, NoCaseTreeValue4> const &);
// ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@UBfmeStringNoCaseLess@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@@Z
template <>
NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_create_node(const NoCaseTree4CF550::value_type &value)
{
	_Link_type node = (_Link_type)_STL::allocator<char>::allocate(sizeof(_STL::_Rb_tree_node<NoCaseTree4CF550::value_type>), 0);
	((NoCaseTree4CF550ConstructFn)&dup_002CF954)(&node->_M_value_field, value);
	return node;
}
template NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_create_node(const NoCaseTree4CF550::value_type &);
