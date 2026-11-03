// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// STLport 4.5.3 _M_insert for two AsciiString-keyed trees, dedicated TU:
// set<BfmeStringRecord002CF550> (retail 0x0033CBCA) and
// map<AsciiString, NoCaseTreeValue4, BfmeStringNoCaseLess> (0x0033CC5E),
// 148B each, plus that map's insert_unique(value) (0x0033D28A, 151B), the
// unowned caller of its _M_insert; /D_BFME_RETAIL_TREE_INSERT_LAYOUT selects
// the vendored STLport's retail insert_unique layout. Each tree's _M_create_node is matched (0x002CFA6C, 0x002CFA8E)
// and only declared here so the calls resolve through those rows.
//
// Target evidence: both bodies are the unowned retail callers of those
// _M_create_node rows and compare keys by calling the matched AsciiString
// operator< (0x0005598C) directly. Structural inference: that direct call is
// what an inline comparator reproduces - an inline record operator< on the
// leading AsciiString for the set, and an inline BfmeStringNoCaseLess for the
// map (stlport_rb_tree_copy_nocase4_002D0399.cpp declares it out of line for
// its own bodies, where retail calls it out of line).
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <set>
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);
struct BfmeStringRecord002CF550 { AsciiString key; char rest[8]; BfmeStringRecord002CF550(const BfmeStringRecord002CF550 &); ~BfmeStringRecord002CF550(); };
inline bool operator<(const BfmeStringRecord002CF550 &a, const BfmeStringRecord002CF550 &b) { return a.key < b.key; }
#include "../../../../GameEngine/Include/Common/NoCaseTreeValue4.h"
// The comparator only exists inline here (the bodies call operator< directly);
// imported force-inline, so this unit emits no copy of the rowed 0x0002C63C name.
struct BfmeStringNoCaseLess { __declspec(dllimport) __forceinline bool operator()(const AsciiString &a, const AsciiString &b) const { return a < b; } };
typedef _STL::_Rb_tree<BfmeStringRecord002CF550, BfmeStringRecord002CF550, _STL::_Identity<BfmeStringRecord002CF550>, _STL::less<BfmeStringRecord002CF550>, _STL::allocator<BfmeStringRecord002CF550> > TreeR;
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NCV;
typedef _STL::_Rb_tree<AsciiString, NCV, _STL::_Select1st<NCV>, BfmeStringNoCaseLess, _STL::allocator<NCV> > TreeN;
template <> TreeR::_Link_type TreeR::_M_create_node(const TreeR::value_type &);
template <> TreeN::_Link_type TreeN::_M_create_node(const TreeN::value_type &);
template TreeR::iterator TreeR::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const TreeR::value_type &, _STL::_Rb_tree_node_base *);
template TreeN::iterator TreeN::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const TreeN::value_type &, _STL::_Rb_tree_node_base *);
template _STL::pair<TreeN::iterator, bool> TreeN::insert_unique(const TreeN::value_type &);

// insert_unique(value) for the record set (retail 0x0033D1F3, 151B) is the
// unowned caller of its _M_insert above.
template _STL::pair<TreeR::iterator, bool> TreeR::insert_unique(const TreeR::value_type &);

// Retail 0x0033D52B (20B): a container member that returns this record tree's
// insert_unique result straight through the hidden pair pointer (the only
// callee is the insert_unique row above). STLport's set::insert rebuilds the
// pair (frame plus copy), so this is not set::insert; the owning class is
// unresolved and the view is address-named.
class Rva0033D52BRecords
{
public:
	_STL::pair<TreeR::iterator, bool> insert(const TreeR::value_type &v);
private:
	TreeR m_tree;
};

_STL::pair<TreeR::iterator, bool> Rva0033D52BRecords::insert(const TreeR::value_type &v)
{
	return m_tree.insert_unique(v);
}
