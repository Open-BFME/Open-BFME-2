// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Integer-to-float map element access (shared subscript helper). The insert
// folds to the rowed integer-pair spelling (twin pin).
// ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHM@_STL@@U?$_Select1st@U?$pair@$$CBHM@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHM@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHM@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHM@_STL@@@2@@2@U32@ABU?$pair@$$CBHM@2@@Z @ 0x003590C9 (294B): _Rb_tree insert_unique with hint; same 294B shape as int_int 0x00422EC0; callees _M_insert 0x005C6A75 and insert_unique 0x005DFD8D plus _M_increment/_M_decrement.

#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

template float &_STL::map<int, float, _STL::less<int>, _STL::allocator<_STL::pair<const int, float> > >::operator[](const int &);

typedef _STL::pair<const int, float> IntFloatValue;
typedef _STL::_Rb_tree<int, IntFloatValue, _STL::_Select1st<IntFloatValue>, _STL::less<int>, _STL::allocator<IntFloatValue> > IntFloatTree;
template IntFloatTree::iterator IntFloatTree::insert_unique(IntFloatTree::iterator, const IntFloatValue &);

struct Rva00358FEERecord { char word; };
namespace _STL { template<> struct __type_traits<Rva00358FEERecord> : __type_traits_aux<1> {}; }

typedef _STL::_Rb_tree<int, _STL::pair<int const, Rva00358FEERecord>, _STL::_Select1st<_STL::pair<int const, Rva00358FEERecord> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00358FEERecord> > > Tree003591F4;

// Retail's call goes to the rowed node erase at 0x00358DC2; suppress this TU's own copy
// and bind the template name to that row.
namespace _STL {
template <> void _Rb_tree<int, pair<int const, Rva00358FEERecord>, _Select1st<pair<int const, Rva00358FEERecord> >, less<int>, allocator<pair<int const, Rva00358FEERecord> > >::erase(_Rb_tree<int, pair<int const, Rva00358FEERecord>, _Select1st<pair<int const, Rva00358FEERecord> >, less<int>, allocator<pair<int const, Rva00358FEERecord> > >::iterator);
}

struct Rva003591F4Arg
{
	Rva003591F4Arg(const Rva003591F4Arg &other) : m_id(other.m_id), m_flag(other.m_flag) {}
	int m_id;
	bool m_flag;
};

class Rva00E01E28Owner
{
public:
	void rva003591F4(Rva003591F4Arg arg);
};

void Rva00E01E28Owner::rva003591F4(Rva003591F4Arg arg)
{
	char *p = (char *)this;
	if (arg.m_flag != 0)
		p += 0x18;
	else
		p += 0x0C;
	Tree003591F4 *tree = (Tree003591F4 *)p;
	Tree003591F4::iterator it((Tree003591F4::iterator::_Link_type)arg.m_id);
	if (it != tree->end())
		tree->erase(it);
}

