// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_copy@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@UBfmeStringNoCaseLess@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@PAU32@0@Z @0x002D0399 115B.
// NoCase _M_copy: recursive copy through rowed _M_clone_node 0x002CFE27 with
// self recursion. Same 115B shape as OwnedRecord900 _M_copy 0x002D0326.
// Emitted via explicit instantiation of this one member; _M_clone_node stays
// an external call resolved by its ledger row. Callers at 0x002D03C2
// 0x002D03EF (self) and 0x002D089E unblocks 0x002D0867.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };
class AsciiString { public: void *m_data; };
struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const;
};
// Use the complete value-copy provider at retail 0x00466EA7.
// A trivial local AsciiString view must not supply the selected pair copy.
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCasePairCopy;
namespace _STL {
template <> NoCasePairCopy::pair(const NoCasePairCopy &);
}

typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::_Select1st<_STL::pair<const AsciiString, NoCaseTreeValue4> >, BfmeStringNoCaseLess, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > NoCaseTree4CF550;
template NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_copy(NoCaseTree4CF550::_Link_type, NoCaseTree4CF550::_Link_type);

// Whole-class instantiation of this tree. It reproduces operator= (retail 0x002D0867)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<AsciiString,_STL::pair<AsciiString const ,NoCaseTreeValue4>,_STL::_Select1st<_STL::pair<AsciiString const ,NoCaseTreeValue4> >,BfmeStringNoCaseLess,_STL::allocator<_STL::pair<AsciiString const ,NoCaseTreeValue4> > >;
