// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ?_M_erase@?$_Rb_tree@UBfmeRecord001DD3BC@@U1@U?$_Identity@UBfmeRecord001DD3BC@@@_STL@@U?$less@UBfmeRecord001DD3BC@@@3@V?$allocator@UBfmeRecord001DD3BC@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@UBfmeRecord001DD3BC@@@2@@Z @0x001DD894 53B recurse-right via +0xC walk-left via +0x8 destroy value at +0x10 via rowed dtor 0x001DD1FF free 0x00030830.
// Evidence: chain lane all callees rowed; next-row create_node proves UBfmeRecord001DD3BCSetTree identity; same 53B shape as 0x005C6A40.
#include <map>
struct BfmeRecord001DD3BC {
	~BfmeRecord001DD3BC();
	unsigned char m_data[8];
};
bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);
typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;
template void BfmeRecord001DD3BCSetTree::_M_erase(BfmeRecord001DD3BCSetTree::_Link_type);
template void BfmeRecord001DD3BCSetTree::clear();
