// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??4?$_Rb_tree@UBfmeStringRecord0021A940@@U1@U?$_Identity@UBfmeStringRecord0021A940@@@_STL@@U?$less@UBfmeStringRecord0021A940@@@3@V?$allocator@UBfmeStringRecord0021A940@@@3@@_STL@@QAEAAV01@ABV01@@Z @0x0021D842 115B operator= via rowed clear 0x0021CFD1 and copy 0x0021D7CF.
// Evidence: chain lane every callee rowed; same 115B shape as 0x001DDC52.
#include <map>
struct BfmeStringRecord0021A940 {
	unsigned char m_data[20];
};
bool operator<(const BfmeStringRecord0021A940 &a, const BfmeStringRecord0021A940 &b);
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > BfmeStringRecord0021A940SetTree;
template BfmeStringRecord0021A940SetTree &BfmeStringRecord0021A940SetTree::operator=(const BfmeStringRecord0021A940SetTree &);
