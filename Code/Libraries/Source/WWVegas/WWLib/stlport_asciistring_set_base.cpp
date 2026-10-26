// cl: /DBFME_ASCII_DTOR_DECL /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 AsciiString set header allocation with BFME's byte allocator.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <set>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_node<AsciiString> * _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_copy(_Rb_tree_node<AsciiString> *, _Rb_tree_node<AsciiString> *); }
namespace _STL { template <> _Rb_tree_node<AsciiString> * _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::_M_create_node(AsciiString const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<AsciiString, _Nonconst_traits<AsciiString> >, bool> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::insert_unique(AsciiString const &); }
// bfme link decl-only end
bool operator<(const AsciiString &, const AsciiString &);
namespace _STL {
// The rowed ~_Rb_tree (MapMetaDataCopy.cpp, 0x589BE) is the kept copy; do not emit another.
template <> _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> >::~_Rb_tree();
}
template class _STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> >;

// ?rva00057DA0@Rva00056CF8@@QAEXU?$_Rb_tree_iterator@VAsciiString@@U?$_Nonconst_traits@VAsciiString@@@_STL@@@_STL@@0@Z @0x00057DA0 68B.
// Range erase for the AsciiString-set wrapper Rva00056CF8: full [begin end)
// clears via rowed rva00057B74, else erases one by one via the rowed
// _Rb_tree<AsciiString> erase(iterator) with _M_increment. Same pattern as
// Rva00388EAE::rva003891E8 in RvaTreeEraseRangeFamily.cpp. Evidence: callers
// at 0x0005B66F, callees rva00057B74 and rowed Rb_tree AsciiString erase,
// neighbours 0x00057D5C/0x00057DE4.
typedef _STL::_Rb_tree<AsciiString, AsciiString, _STL::_Identity<AsciiString>,
	_STL::less<AsciiString>, _STL::allocator<AsciiString> > AsciiStringSetTree;

class Rva00056CF8
{
public:
	void rva00057B74();
	void rva00057DA0(AsciiStringSetTree::iterator first, AsciiStringSetTree::iterator last);
	unsigned int rva0005B633(const AsciiString &x);
};

void Rva00056CF8::rva00057DA0(AsciiStringSetTree::iterator first, AsciiStringSetTree::iterator last)
{
	AsciiStringSetTree *tree = reinterpret_cast<AsciiStringSetTree *>(this);
	if (first == tree->begin() && last == tree->end())
		rva00057B74();
	else
		while (first != last)
			tree->erase(first++);
}

// ?rva0005B633@Rva00056CF8@@QAEIABVAsciiString@@@Z @0x0005B633 73B.
// Key erase for the AsciiString-set wrapper Rva00056CF8: equal_range via rowed
// 0x005C9F41, distance via rowed 0x000D20DB, range erase via rva00057DA0.
// Same 73B shape as RvaTreeEraseRangeFamily key erases. Evidence: callees
// 0x005C9F41 0x000D20DB 0x00057DA0, callers 0x0005E377 0x0005CC23 0x0005CE79.
unsigned int Rva00056CF8::rva0005B633(const AsciiString &x)
{
	_STL::pair<AsciiStringSetTree::iterator, AsciiStringSetTree::iterator> p = reinterpret_cast<AsciiStringSetTree *>(this)->equal_range(x);
	unsigned int n = _STL::distance(p.first, p.second);
	rva00057DA0(p.first, p.second);
	return n;
}
