// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?insert@?$list@UBfmeStringRecord00239B46@@V?$allocator@UBfmeStringRecord00239B46@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeStringRecord00239B46@@U?$_Nonconst_traits@UBfmeStringRecord00239B46@@@_STL@@@2@U32@ABUBfmeStringRecord00239B46@@@Z retail 0x00239E80 37B
// Evidence: calls rowed _M_create_node at 0x00239D27 then list hook insertion; caller 0x0023A025; same 37B shape as list TreeKey insert 0x002A1BC6.
#include <list>
struct BfmeStringRecord00239B46 {
    unsigned char m_data[8];
};
bool operator==(const BfmeStringRecord00239B46 &a, const BfmeStringRecord00239B46 &b);
bool operator<(const BfmeStringRecord00239B46 &a, const BfmeStringRecord00239B46 &b);
template class _STL::list<BfmeStringRecord00239B46, _STL::allocator<BfmeStringRecord00239B46> >;
