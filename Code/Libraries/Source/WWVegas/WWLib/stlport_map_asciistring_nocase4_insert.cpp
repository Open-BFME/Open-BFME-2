// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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

struct NoCaseTreeValue4 { public: unsigned char m_data[4]; };

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NoCaseValue;
typedef _STL::_Rb_tree<AsciiString, NoCaseValue, _STL::_Select1st<NoCaseValue>, _STL::less<AsciiString>, _STL::allocator<NoCaseValue> > NoCaseTree;
template <> NoCaseTree::_Link_type NoCaseTree::_M_create_node(const NoCaseValue &);

template NoCaseTree::iterator NoCaseTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const NoCaseValue &, _STL::_Rb_tree_node_base *);
template _STL::pair<NoCaseTree::iterator, bool> NoCaseTree::insert_unique(const NoCaseTree::value_type &);
