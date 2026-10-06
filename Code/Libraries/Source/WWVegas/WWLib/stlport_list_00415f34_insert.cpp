// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?insert@?$list@UBfmeStringRecord00415F34@@V?$allocator@UBfmeStringRecord00415F34@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord00415F34@@U?$_Nonconst_traits@UBfmeStringRecord00415F34@@@_STL@@@2@U32@ABUBfmeStringRecord00415F34@@@Z @0x004168AE 37B
// list<BfmeStringRecord00415F34>::insert 37B calling rowed _M_create_node at
// 0x00416521 then list hook insertion; identical shape to list<BfmeStringRecord001EA478>::insert
// at 0x001EA958 and list<int>::insert at 0x005925E2; caller 0x0041691F.
#include <list>

struct BfmeStringRecord00415F34 { unsigned char m_data[24]; };

bool operator==(const BfmeStringRecord00415F34 &a, const BfmeStringRecord00415F34 &b);
bool operator<(const BfmeStringRecord00415F34 &a, const BfmeStringRecord00415F34 &b);

template class _STL::list<BfmeStringRecord00415F34, _STL::allocator<BfmeStringRecord00415F34> >;
