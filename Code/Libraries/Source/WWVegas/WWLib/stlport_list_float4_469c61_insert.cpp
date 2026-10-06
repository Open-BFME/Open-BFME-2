// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?insert@?$list@UBfmeFloat4Record00469C61@@V?$allocator@UBfmeFloat4Record00469C61@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmeFloat4Record00469C61@@U?$_Nonconst_traits@UBfmeFloat4Record00469C61@@@_STL@@@2@U32@ABUBfmeFloat4Record00469C61@@@Z @0x001DD86F 37B single-node insert via rowed create_node 0x001DD6ED.
// Evidence: unlock lane every callee rowed; same 37B shape as 0x001EBD16 0x001FD72C 0x00280A68.
#include <list>
struct BfmeFloat4Record00469C61 { unsigned char m_data[16]; };
bool operator==(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
bool operator<(const BfmeFloat4Record00469C61 &, const BfmeFloat4Record00469C61 &);
template class _STL::list<BfmeFloat4Record00469C61, _STL::allocator<BfmeFloat4Record00469C61> >;
