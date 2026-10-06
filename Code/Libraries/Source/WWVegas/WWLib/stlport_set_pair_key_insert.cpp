// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport 4.5.3 _M_insert for three sets whose elements lead with a
// pair<AsciiString, AsciiString> key, dedicated TU: set<Rva00204B12> (retail
// 0x00207187), set<Rva0033A4F0> (0x0020721B) and set<BfmeStringRecord002049D6>
// (0x002073D7), 148B each. Element sizes (16, 12, 12) are carried from
// stlport_rb_tree_create_nodes.cpp, which owns each tree's matched
// _M_create_node; here _M_create_node is only declared so its call resolves
// through that row, and each element is reduced to its key plus footprint.
//
// Target evidence: each body is the unowned retail caller of its tree's
// matched _M_create_node, and all three compare by passing the elements to the
// matched pair<AsciiString, AsciiString> operator< at 0x00206BCF, which an
// inline element operator< on the leading pair reproduces.
#define _STLP_NO_EXCEPTIONS 1
#include <set>
class AsciiString { void *m_data; public: AsciiString(const AsciiString &); ~AsciiString(); };
bool operator<(const _STL::pair<AsciiString, AsciiString> &, const _STL::pair<AsciiString, AsciiString> &);
struct Rva00204B12 { _STL::pair<AsciiString, AsciiString> key; char rest[8]; Rva00204B12(const Rva00204B12 &); ~Rva00204B12(); };
class Rva0033A4F0 { public: _STL::pair<AsciiString, AsciiString> key; char rest[4]; Rva0033A4F0(const Rva0033A4F0 &); ~Rva0033A4F0(); };
struct BfmeStringRecord002049D6 { _STL::pair<AsciiString, AsciiString> key; char rest[4]; BfmeStringRecord002049D6(const BfmeStringRecord002049D6 &); ~BfmeStringRecord002049D6(); };
inline bool operator<(const Rva00204B12 &a, const Rva00204B12 &b) { return a.key < b.key; }
inline bool operator<(const Rva0033A4F0 &a, const Rva0033A4F0 &b) { return a.key < b.key; }
inline bool operator<(const BfmeStringRecord002049D6 &a, const BfmeStringRecord002049D6 &b) { return a.key < b.key; }
#define SET_TREE(T) _STL::_Rb_tree<T, T, _STL::_Identity<T>, _STL::less<T>, _STL::allocator<T> >
typedef SET_TREE(Rva00204B12) TreeA;
typedef SET_TREE(Rva0033A4F0) TreeB;
typedef SET_TREE(BfmeStringRecord002049D6) TreeC;
template <> TreeA::_Link_type TreeA::_M_create_node(const Rva00204B12 &);
template <> TreeB::_Link_type TreeB::_M_create_node(const Rva0033A4F0 &);
template <> TreeC::_Link_type TreeC::_M_create_node(const BfmeStringRecord002049D6 &);
template TreeA::iterator TreeA::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const Rva00204B12 &, _STL::_Rb_tree_node_base *);
template TreeB::iterator TreeB::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const Rva0033A4F0 &, _STL::_Rb_tree_node_base *);
template TreeC::iterator TreeC::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const BfmeStringRecord002049D6 &, _STL::_Rb_tree_node_base *);

// insert_unique(value) for the same three sets (retail 0x0020783F, 0x002078D6,
// 0x00207A9B, 151B each) are the unowned callers of the _M_insert bodies
// above; /D_BFME_RETAIL_TREE_INSERT_LAYOUT selects the vendored STLport's
// retail insert_unique layout.
template _STL::pair<TreeA::iterator, bool> TreeA::insert_unique(const Rva00204B12 &);
template _STL::pair<TreeB::iterator, bool> TreeB::insert_unique(const Rva0033A4F0 &);
template _STL::pair<TreeC::iterator, bool> TreeC::insert_unique(const BfmeStringRecord002049D6 &);
