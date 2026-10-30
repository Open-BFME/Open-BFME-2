// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
// Retail compares this file's map<int, void *> keys unsigned: its own rowed
// int/void* erase(const int &) 0x004ABE65 calls equal_range 0x00362B5F, which
// calls _M_lower_bound 0x004FF3B6 / _M_upper_bound 0x004FF539, both `jb`/`jae`.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return (unsigned int)a < (unsigned int)b; }
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

// The map<int, int> tree's bounds are emitted COMDATs here only as a side
// effect of the other tree's instantiation; declare them out of line so this
// TU calls the rowed int/int bodies (0x00382A92 / 0x004FF471, `jl`/`jge`)
// instead of emitting the unsigned copies the comparator above now yields.
namespace _STL {
template <> _Rb_tree_node<pair<const int, int> > *
_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >,
         less<int>, allocator<pair<const int, int> > >::_M_lower_bound(const int &) const;
template <> _Rb_tree_node<pair<const int, int> > *
_Rb_tree<int, pair<const int, int>, _Select1st<pair<const int, int> >,
         less<int>, allocator<pair<const int, int> > >::_M_upper_bound(const int &) const;
}

class Rva0007E971
{
public:
	void rva0007FAC1();
	void rva0007FB07(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva00082536(const int &x);
};

// 0x0007FB07 68B: erase(first, last) over rva0007FAC1
void Rva0007E971::rva0007FB07(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva0007FAC1();
	else
		while (first != last)
			tree->erase(first++);
}


class Rva000D20A9
{
public:
	void rva000D2294();
	void rva000D22BD(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva000D3BFD(const int &x);
};

// 0x000D22BD 68B: erase(first, last) over rva000D2294
void Rva000D20A9::rva000D22BD(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva000D2294();
	else
		while (first != last)
			tree->erase(first++);
}


class Rva00388EAE
{
public:
	void rva00389129();
	void rva003891E8(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva00389913(const int &key);
};

// 0x003891E8 68B: erase(first, last) over rva00389129
void Rva00388EAE::rva003891E8(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva00389129();
	else
		while (first != last)
			tree->erase(first++);
}

// 0x00389913 73B: erase(const int &) over rva003891E8 and map<int, int>'s equal_range
unsigned int Rva00388EAE::rva00389913(const int &key)
{
	_STL::pair<IntIntTree::iterator, IntIntTree::iterator> q = reinterpret_cast<IntIntTree *>(this)->equal_range(key);
	unsigned int count = _STL::distance(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	rva003891E8(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	return count;
}

class Rva002EE9B7
{
public:
	void rva002EE9B7();
	void rva0046A967(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva0046EDEF(const int &key);
};

// 0x0046A967 68B: erase(first, last) over rva002EE9B7
void Rva002EE9B7::rva0046A967(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva002EE9B7();
	else
		while (first != last)
			tree->erase(first++);
}

// 0x0046EDEF 73B: erase(const int &) over rva0046A967 and map<int, int>'s equal_range
unsigned int Rva002EE9B7::rva0046EDEF(const int &key)
{
	_STL::pair<IntIntTree::iterator, IntIntTree::iterator> q = reinterpret_cast<IntIntTree *>(this)->equal_range(key);
	unsigned int count = _STL::distance(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	rva0046A967(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	return count;
}

class Rva004E7B13
{
public:
	void rva004E7BAF();
	void rva004E7BD8(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva004E7D29(const int &key);
};

// 0x004E7BD8 68B: erase(first, last) over rva004E7BAF
void Rva004E7B13::rva004E7BD8(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva004E7BAF();
	else
		while (first != last)
			tree->erase(first++);
}

// 0x004E7D29 73B: erase(const int &) over rva004E7BD8 and map<int, int>'s equal_range
unsigned int Rva004E7B13::rva004E7D29(const int &key)
{
	_STL::pair<IntIntTree::iterator, IntIntTree::iterator> q = reinterpret_cast<IntIntTree *>(this)->equal_range(key);
	unsigned int count = _STL::distance(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	rva004E7BD8(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	return count;
}

class Rva001E6731
{
public:
	void rva001E6731();
	void rva001E675A(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva001E71FA(const int &key);
};

// 0x001E675A 68B: erase(first, last) over rva001E6731
void Rva001E6731::rva001E675A(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva001E6731();
	else
		while (first != last)
			tree->erase(first++);
}

// 0x001E71FA 73B: erase(const int &) over rva001E675A and map<int, int>'s equal_range
unsigned int Rva001E6731::rva001E71FA(const int &key)
{
	_STL::pair<IntIntTree::iterator, IntIntTree::iterator> q = reinterpret_cast<IntIntTree *>(this)->equal_range(key);
	unsigned int count = _STL::distance(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	rva001E675A(reinterpret_cast<IntPtrTree::iterator &>(q.first), reinterpret_cast<IntPtrTree::iterator &>(q.second));
	return count;
}

class Rva00362AB5
{
public:
	void rva00362AB5();
	void rva00362ADE(IntPtrTree::iterator first, IntPtrTree::iterator last);
	unsigned int rva00362B89(const int &x);
};

// 0x00362ADE 68B: erase(first, last) over rva00362AB5
void Rva00362AB5::rva00362ADE(IntPtrTree::iterator first, IntPtrTree::iterator last)
{
	IntPtrTree *tree = reinterpret_cast<IntPtrTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva00362AB5();
	else
		while (first != last)
			tree->erase(first++);
}


// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?erase@Rva006DF050Slot@@QAEIABH@Z=?rva000D3BFD@Rva000D20A9@@QAEIABH@Z")

class Rva00082BE1
{
public:
	unsigned int rva00082BE1(const int &x);
};


class Rva000D3C46
{
public:
	unsigned int rva000D3C46(const int &x);
};


class Rva001E7E78
{
public:
	unsigned int rva001E7E78(const int &key);
};

unsigned int Rva001E7E78::rva001E7E78(const int &key)
{
	return reinterpret_cast<Rva001E6731 *>(this)->rva001E71FA(key);
}

class Rva00362C9A
{
public:
	unsigned int rva00362C9A(const int &x);
};


class Rva003899C4
{
public:
	unsigned int rva003899C4(const int &key);
};

unsigned int Rva003899C4::rva003899C4(const int &key)
{
	return reinterpret_cast<Rva00388EAE *>(this)->rva00389913(key);
}

class Rva0047003C
{
public:
	unsigned int rva0047003C(const int &key);
};

unsigned int Rva0047003C::rva0047003C(const int &key)
{
	return reinterpret_cast<Rva002EE9B7 *>(this)->rva0046EDEF(key);
}

class Rva004E7E19
{
public:
	unsigned int rva004E7E19(const int &key);
};

unsigned int Rva004E7E19::rva004E7E19(const int &key)
{
	return reinterpret_cast<Rva004E7B13 *>(this)->rva004E7D29(key);
}
