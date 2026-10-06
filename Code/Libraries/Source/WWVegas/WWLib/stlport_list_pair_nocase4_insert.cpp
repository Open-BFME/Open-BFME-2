// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@QAE?AU?$_List_iterator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@2@U32@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@@Z @0x0020746B 37B
// Evidence: unlock lane 37B list insert calling rowed _M_create_node 0x00206ABE then list hook insertion
// identical shape to list<int>::insert at 0x005925E2 and BfmeStringRecord002B4DC1 insert at 0x002B70DC
// caller 0x00207B90. Honest free-function name from packet naming free function.
#include <list>
#include "ascii_string.h"

struct NoCaseTreeValue4 { unsigned char m_data[4]; };

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> PairNocase4;
typedef _STL::list<PairNocase4, _STL::allocator<PairNocase4> > ListNocase4;

// Explicit specialization already rowed at 0x00206ABE in stlport_list_create_nodes2.cpp.
// Declaring it suppresses implicit instantiation of the generic 94B _M_create_node here,
// so this TU emits only insert and calls the rowed version.
namespace _STL {
template <>
_List_node<PairNocase4> *list<PairNocase4, allocator<PairNocase4> >::_M_create_node(const PairNocase4 &);
}

template ListNocase4::iterator ListNocase4::insert(ListNocase4::iterator, const PairNocase4 &);

class Rva00207B90
{
public:
	ListNocase4 m_list;
	void rva00207B90(const PairNocase4 &x);
};

void Rva00207B90::rva00207B90(const PairNocase4 &x)
{
	m_list.insert(ListNocase4::iterator((ListNocase4::_Node *)*(void **)this), x);
}
