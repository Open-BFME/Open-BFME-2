// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport 4.5.3 set<BfmeRecord001DD3BC> _M_insert (retail 0x001DDE2A, 148B)
// and its less<> comparator (0x001DDACA, 18B), dedicated TU. The rest of
// the tree family (_M_create_node, _M_erase, clear, _M_copy, dtor) is
// already matched; the record copy ctor and _Construct live in
// StringContainerRecordCopyBFME2.cpp, whose layout (AsciiString at +0, an
// Rva0036CA00Str handle at +4) is reduced here to its footprint.
//
// Target evidence: _M_insert is the unowned retail caller of the tree's
// matched _M_create_node (0x001DD976); both bodies compare keys by passing
// the two records straight to the matched AsciiString operator< at
// 0x0005598C, which is what an inline record operator< on the leading
// AsciiString reproduces. _M_create_node is only declared here so its call
// resolves through that row.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

#include "ascii_string.h"
bool operator<(const AsciiString &, const AsciiString &);

struct BfmeRecord001DD3BC
{
	AsciiString a0;
	char a4[4];
	BfmeRecord001DD3BC(const BfmeRecord001DD3BC &);
	~BfmeRecord001DD3BC();
};
inline bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b) { return a.a0 < b.a0; }

typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > DD3BCTree;
template <> DD3BCTree::_Link_type DD3BCTree::_M_create_node(const BfmeRecord001DD3BC &);

template DD3BCTree::iterator DD3BCTree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, const BfmeRecord001DD3BC &, _STL::_Rb_tree_node_base *);
template bool _STL::less<BfmeRecord001DD3BC>::operator()(const BfmeRecord001DD3BC &, const BfmeRecord001DD3BC &) const;

// insert_unique(value) (retail 0x001DE4BF, 151B) is the unowned caller of the
// _M_insert above; /D_BFME_RETAIL_TREE_INSERT_LAYOUT selects the vendored
// STLport's retail insert_unique layout.
template _STL::pair<DD3BCTree::iterator, bool> DD3BCTree::insert_unique(const BfmeRecord001DD3BC &);

// set::insert(value) (retail 0x001DE7B5, 35B) forwards to the insert_unique above.
template _STL::pair<_STL::set<BfmeRecord001DD3BC>::iterator, bool> _STL::set<BfmeRecord001DD3BC>::insert(const BfmeRecord001DD3BC &);

class Rva001DD70F
{
public:
	~Rva001DD70F();
};

class Rva001DDADC
{
public:
	void rva001DDADC();
};

void Rva001DDADC::rva001DDADC()
{
	((Rva001DD70F *)this)->~Rva001DD70F();
}

class Rva001DDEBE
{
public:
	void rva001DDEBE();
};

void Rva001DDEBE::rva001DDEBE()
{
	((DD3BCTree *)this)->~DD3BCTree();
}

