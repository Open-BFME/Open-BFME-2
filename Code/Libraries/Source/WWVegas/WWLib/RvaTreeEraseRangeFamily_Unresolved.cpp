// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Split from RvaTreeEraseRangeFamily.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// stlport
//
// Range and key erases of int-keyed pointer maps, copied from STLport's own
// _Rb_tree bodies. The range erase(first, last) has the rowed set<AsciiString>
// instance in stlport_asciistring_set_base.cpp as its template (68 bytes); the
// key erase(const int &) the rowed map<int, void *> one in stlport_map_int_ptr_o1.cpp
// (73 bytes). Each copy calls its own tree's rowed clear (a placeholder member)
// or its own range erase below, and otherwise the ICF-folded STLport bodies
// these trees share: map<int, void *>'s erase(iterator) and distance, and either
// map<int, void *>'s or map<int, int>'s equal_range. Owners are the classes of
// the rowed clears; names keep the addresses. The key erases over map<int, int>'s
// equal_range read its iterators as this tree's: both are the same node pointer,
// and casting each in place (not through a named reference, which stops the
// compiler inlining distance) gives retail's code.

#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef _STL::_Rb_tree<int, _STL::pair<const int, void *>, _STL::_Select1st<_STL::pair<const int, void *> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > IntPtrTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >,
	_STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > IntIntTree;

// The rowed equal_range 0x00362B5F: called, never emitted here with its bound helpers.
namespace _STL { template <> pair<IntPtrTree::iterator, IntPtrTree::iterator> IntPtrTree::equal_range(const int &); }

class Rva0007E971
{
public:
	void rva0007FAC1();
	void eraseRange(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva00082536(const int &key);
};


// 0x00082536 73B: erase(const int &) over rva0007FB07
unsigned int Rva0007E971::rva00082536(const int &key)
{
	_STL::pair<IntPtrTree::iterator, IntPtrTree::iterator> p = reinterpret_cast<IntPtrTree *>(this)->equal_range(key);
	unsigned int n = _STL::distance(p.first, p.second);
	eraseRange(p.first, p.second);
	return n;
}

class Rva000D20A9
{
public:
	void rva000D2294();
	void rva000D22BD(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva000D3BFD(const int &key);
};


// 0x000D3BFD 73B: erase(const int &) over rva000D22BD
unsigned int Rva000D20A9::rva000D3BFD(const int &key)
{
	_STL::pair<IntPtrTree::iterator, IntPtrTree::iterator> p = reinterpret_cast<IntPtrTree *>(this)->equal_range(key);
	unsigned int n = _STL::distance(p.first, p.second);
	rva000D22BD(p.first, p.second);
	return n;
}

class Rva00362AB5
{
public:
	void rva00362AB5();
	void rva00362ADE(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva00362B89(const int &key);
};


// 0x00362B89 73B: erase(const int &) over rva00362ADE
unsigned int Rva00362AB5::rva00362B89(const int &key)
{
	_STL::pair<IntPtrTree::iterator, IntPtrTree::iterator> p = reinterpret_cast<IntPtrTree *>(this)->equal_range(key);
	unsigned int n = _STL::distance(p.first, p.second);
	rva00362ADE(p.first, p.second);
	return n;
}
