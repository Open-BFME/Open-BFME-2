// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmealloc
// stlport

// _Rb_tree<Gen_p12pod, pair<const Gen_p12pod, int>>::_M_insert
// (retail 0x0016DBC0, 182 bytes), backing the landed Gen_p12pod map
// insert_unique at 0x0016DC80. Same recipe as the ScoreKeeper tree unit
// (/G6 there) except for the scheduling flag: this tree's retail head
// compares the hint argument in memory form, which /G7 reproduces, while
// /G6 loads it first. The ushort-key _M_insert keeps the memory form under
// /G7 and the pointer-key one wants /G6, so the flag is per-instantiation
// pressure, not per-family; when porting a tree body, try the sibling
// flag first if the head check comes out load-vs-memory flipped.
// The bfmealloc include routes node allocation through the pinned narrow
// byte allocator. The comparator and tree spelling are reused verbatim
// from the landed RvaTreeInsertUniqueGenP12pod00927CF0 unit (its flags
// stay untouched). _M_insert is protected, so no explicit instantiation
// names it; the member-only insert_unique below odr-uses it into emission,
// and only _M_insert carries a ledger row. Callee pinned in the same
// commit: Gen_p12pod pair _Construct at 0x0016CC80, read out of this
// body's REL32 displacements (_Rebalance resolves through its matched
// row, less<Gen_p12pod> through the landed unit).

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator==(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node == b._M_node; }
}

struct Gen_p12pod
{
	int a[3];
};

inline bool compare_tail(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a1 = a.a[1];
	return b.a[1] > a1
		|| (!(b.a[1] < a1) && a.a[2] < b.a[2]);
}

inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
	const int a0 = a.a[0];
	return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}

typedef _STL::pair<const Gen_p12pod, int> GenP12Pair;
typedef _STL::_Rb_tree<Gen_p12pod, GenP12Pair,
	_STL::_Select1st<GenP12Pair>, _STL::less<Gen_p12pod>,
	_STL::allocator<GenP12Pair> > GenP12Tree;

template _STL::pair<GenP12Tree::iterator, bool>
GenP12Tree::insert_unique(const GenP12Pair &);
