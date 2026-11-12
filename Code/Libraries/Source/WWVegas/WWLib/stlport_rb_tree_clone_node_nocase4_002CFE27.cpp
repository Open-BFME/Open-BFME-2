// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// NoCase _M_clone_node @0x002CFE27 30B: clones the source node through the
// rowed _M_create_node 0x002CFA8E (value field at source+0x10), copies the
// color byte, nulls links +8/+0xc, ret 4. Same 30B shape as the landed
// sibling 0x002CFE09 in OwnedRecord900TreeCopy.cpp; the chain packet shows
// the call into 0x002CFA8E which this session landed. Emitted via explicit
// instantiation of this one member; _M_create_node stays an external call
// resolved by its ledger row.
#include <map>

#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../GameEngine/Include/Common/BfmeStringNoCaseLess.h"

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

template NoCaseTree4CF550::_Link_type NoCaseTree4CF550::_M_clone_node(NoCaseTree4CF550::_Link_type);
