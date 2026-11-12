// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ?_M_copy@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@UBfmeStringNoCaseLess@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@3@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@PAU32@0@Z @0x002D0399 115B.
// NoCase _M_copy: recursive copy through rowed _M_clone_node 0x002CFE27 with
// self recursion. Same 115B shape as OwnedRecord900 _M_copy 0x002D0326.
// Emitted via explicit instantiation of this one member; _M_clone_node stays
// an external call resolved by its ledger row. Callers at 0x002D03C2
// 0x002D03EF (self) and 0x002D089E unblocks 0x002D0867.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeStringNoCaseLess.h"
// Bind to the kept retail copies instead of emitting this unit's own.
namespace _STL { template <> _Rb_tree_iterator<pair<AsciiString const ,NoCaseTreeValue4>,_Nonconst_traits<pair<AsciiString const ,NoCaseTreeValue4> > > _Rb_tree<AsciiString,pair<AsciiString const ,NoCaseTreeValue4>,_Select1st<pair<AsciiString const ,NoCaseTreeValue4> >,BfmeStringNoCaseLess,allocator<pair<AsciiString const ,NoCaseTreeValue4> > >::_M_insert(_Rb_tree_node_base *,_Rb_tree_node_base *,pair<AsciiString const ,NoCaseTreeValue4> const &,_Rb_tree_node_base *); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<AsciiString const ,NoCaseTreeValue4>,_Nonconst_traits<pair<AsciiString const ,NoCaseTreeValue4> > >,bool> _Rb_tree<AsciiString,pair<AsciiString const ,NoCaseTreeValue4>,_Select1st<pair<AsciiString const ,NoCaseTreeValue4> >,BfmeStringNoCaseLess,allocator<pair<AsciiString const ,NoCaseTreeValue4> > >::insert_unique(pair<AsciiString const ,NoCaseTreeValue4> const &); }
// Use the complete value-copy provider at retail 0x00466EA7.
// A trivial local AsciiString view must not supply the selected pair copy.
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCasePairCopy;
namespace _STL {
template <> NoCasePairCopy::pair(const NoCasePairCopy &);
}

typedef _STL::_Rb_tree<AsciiString, _STL::pair<const AsciiString, NoCaseTreeValue4>, _STL::_Select1st<_STL::pair<const AsciiString, NoCaseTreeValue4> >, BfmeStringNoCaseLess, _STL::allocator<_STL::pair<const AsciiString, NoCaseTreeValue4> > > NoCaseTree4CF550;
// _M_create_node is the rowed 0x002CFA8E body (stlport_rb_tree_create_node_nocase4_002CFA8E.cpp):
// retail's copy calls the distinct placement copy 0x002CF954, not the
// _Construct<pair<..., NoCaseTreeValue4>> row 0x000A7849 the template would call.
template <> NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_create_node(const NoCaseTree4CF550::value_type &);
template NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_copy(NoCaseTree4CF550::_Link_type, NoCaseTree4CF550::_Link_type);

// Whole-class instantiation of this tree. It reproduces operator= (retail 0x002D0867)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<AsciiString,_STL::pair<AsciiString const ,NoCaseTreeValue4>,_STL::_Select1st<_STL::pair<AsciiString const ,NoCaseTreeValue4> >,BfmeStringNoCaseLess,_STL::allocator<_STL::pair<AsciiString const ,NoCaseTreeValue4> > >;

// map::operator= at retail 0x002D0B48 (18B, RET4): assigns the tree through
// its operator= 0x002D0867 above (the only callee) and returns this.
typedef _STL::map<AsciiString, NoCaseTreeValue4, BfmeStringNoCaseLess> NoCaseMap4CF550;
template NoCaseMap4CF550 &NoCaseMap4CF550::operator=(const NoCaseMap4CF550 &);
