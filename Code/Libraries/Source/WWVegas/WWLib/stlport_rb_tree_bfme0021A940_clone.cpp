// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?_M_clone_node@?$_Rb_tree@UBfmeStringRecord0021A940@@U1@U?$_Identity@UBfmeStringRecord0021A940@@@_STL@@U?$less@UBfmeStringRecord0021A940@@@3@V?$allocator@UBfmeStringRecord0021A940@@@3@@_STL@@IAEPAU?$_Rb_tree_node@UBfmeStringRecord0021A940@@@2@PAU32@@Z @0x0021D13B 30B via rowed create_node 0x0021C48E.
// Evidence: chain lane all callees rowed; value at source+0x10 color copy null links; same 30B shape as 0x001DD998.
#include <map>
struct BfmeStringRecord0021A940 {
	unsigned char m_data[20];
};
bool operator<(const BfmeStringRecord0021A940 &a, const BfmeStringRecord0021A940 &b);
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > BfmeStringRecord0021A940SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord0021A940>(BfmeStringRecord0021A940 *, const BfmeStringRecord0021A940 &);
}
template BfmeStringRecord0021A940SetTree::_Link_type BfmeStringRecord0021A940SetTree::_M_clone_node(BfmeStringRecord0021A940SetTree::_Link_type);
template BfmeStringRecord0021A940SetTree::_Link_type BfmeStringRecord0021A940SetTree::_M_copy(BfmeStringRecord0021A940SetTree::_Link_type, BfmeStringRecord0021A940SetTree::_Link_type);
