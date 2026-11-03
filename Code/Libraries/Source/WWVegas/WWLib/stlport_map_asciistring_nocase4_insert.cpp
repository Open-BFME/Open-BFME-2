// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// STLport 4.5.3 map<AsciiString, NoCaseTreeValue4> _M_insert (retail
// 0x0022125D, 148B) and insert_unique(value) (0x00221329, 151B), dedicated TU. The tree typedef and the 4-byte value are
// carried from stlport_rb_tree_create_nodes2.cpp, which owns the tree's
// matched _M_create_node (0x00221201); it is only declared here so the call
// resolves through that row.
//
// Target evidence: this body is the unowned retail caller of that
// _M_create_node, and its key compare is the less<AsciiString> call into the
// matched AsciiString operator< at 0x0005598C. insert_unique is the unowned
// caller of that _M_insert; /D_BFME_RETAIL_TREE_INSERT_LAYOUT selects the
// vendored STLport's retail insert_unique layout.
#define _STLP_NO_EXCEPTIONS 1
#include <map>

#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);

#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCaseValue;
typedef _STL::_Rb_tree<AsciiString, NoCaseValue, _STL::_Select1st<NoCaseValue>, _STL::less<AsciiString>, _STL::allocator<NoCaseValue> > NoCaseTree;
template <> NoCaseTree::_Link_type NoCaseTree::_M_create_node(const NoCaseValue &);

template NoCaseTree::iterator NoCaseTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const NoCaseValue &, _STL::_Rb_tree_node_base *);
template _STL::pair<NoCaseTree::iterator, bool> NoCaseTree::insert_unique(const NoCaseTree::value_type &);

// map::insert(const value_type &) at retail 0x002213C5 (20B): the inline
// forwarder to insert_unique above, its only callee there; the hidden pair
// result pointer and the value are passed straight through.
typedef _STL::map<AsciiString, NoCaseTreeValue4> NoCaseMap;
template _STL::pair<NoCaseMap::iterator, bool> NoCaseMap::insert(const NoCaseMap::value_type &);
