// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord002B4DC1@@U?$_Nonconst_traits@UBfmeStringRecord002B4DC1@@@_STL@@@2@U32@ABUBfmeStringRecord002B4DC1@@@Z retail 0x002B70DC 37B
// Evidence: identical 37B shape to list<int>::insert at 0x005925E2 calling rowed _M_create_node;
// here calls rowed 002B4DC1 _M_create_node at 0x002B60D7 then list hook insertion; callers 0x002B7120 and 0x002B8117.
#include <list>
// Suppress this TU's non-retail copy of ?_M_create_node@?$list@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeStringRecord002B4DC1;
namespace _STL { template <> _List_node<BfmeStringRecord002B4DC1> * list<BfmeStringRecord002B4DC1,allocator<BfmeStringRecord002B4DC1> >::_M_create_node(BfmeStringRecord002B4DC1 const &); }

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


#include "../../../../GameEngine/Include/Common/BfmeStringRecord002B4DC1.h"

bool operator==(const BfmeStringRecord002B4DC1 &a, const BfmeStringRecord002B4DC1 &b);
bool operator<(const BfmeStringRecord002B4DC1 &a, const BfmeStringRecord002B4DC1 &b);

// Retail's list(size_type) is rowed in stlport_list_002b8ff3_fill.cpp; keep this instantiation's
// differing copy out of the link.
namespace _STL { template <> list<BfmeStringRecord002B4DC1, allocator<BfmeStringRecord002B4DC1> >::list(unsigned int); }
// Instantiate the recovered insert workers without the unrelated comparisons.
namespace _STL {
typedef list<BfmeStringRecord002B4DC1, allocator<BfmeStringRecord002B4DC1> > RecordList;
template RecordList::iterator RecordList::insert(RecordList::iterator, const BfmeStringRecord002B4DC1 &);
template void RecordList::_M_fill_insert(RecordList::iterator, unsigned int, const BfmeStringRecord002B4DC1 &);
template void RecordList::insert(RecordList::iterator, unsigned int, const BfmeStringRecord002B4DC1 &);
}

// ?rva002B8106@Rva002B8106@@QAEXABUBfmeStringRecord002B4DC1@@@Z @ 0x002B8106 (26B).
// Frameless forward to the rowed list::insert above with begin() position.
// Callers 0x002B87E0 (+0xF0) and 0x002B8BFE. Evidence: callee rowed.
class Rva002B8106
{
public:
	typedef _STL::list<BfmeStringRecord002B4DC1> List;
	List m_list;
	void rva002B8106(const List::value_type &v);
};

void Rva002B8106::rva002B8106(const List::value_type &v)
{
	m_list.insert(m_list.end(), v);
}
