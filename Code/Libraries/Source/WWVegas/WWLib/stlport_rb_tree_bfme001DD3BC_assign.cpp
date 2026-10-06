// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ??4?$_Rb_tree@UBfmeRecord001DD3BC@@U1@U?$_Identity@UBfmeRecord001DD3BC@@@_STL@@U?$less@UBfmeRecord001DD3BC@@@3@V?$allocator@UBfmeRecord001DD3BC@@@3@@_STL@@QAEAAV01@ABV01@@Z @0x001DDC52 115B operator= via rowed clear 0x001DD9F3 and copy 0x001DDA57.
// Evidence: chain lane every callee rowed; same 115B shape as 0x0021DD0E 0x0030200E 0x0052274D.
#include <map>
struct BfmeRecord001DD3BC {
	unsigned char m_data[8];
};
bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);
typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;
template BfmeRecord001DD3BCSetTree &BfmeRecord001DD3BCSetTree::operator=(const BfmeRecord001DD3BCSetTree &);
