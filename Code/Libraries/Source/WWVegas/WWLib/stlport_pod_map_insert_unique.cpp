// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBHUBfmePod8@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUBfmePod8@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUBfmePod8@@@2@@Z 0x00422918 134B evidence: leaf insert_unique via rowed _M_insert 0x00422890 plus _M_decrement; caller 0x00422EAD; siblings Rva00064640Insert same recipe same flags
#include <map>
struct BfmePod8 { int a[2]; };
typedef _STL::pair<const int, BfmePod8> PodMapValue;
typedef _STL::_Rb_tree<int, PodMapValue, _STL::_Select1st<PodMapValue>, _STL::less<int>, _STL::allocator<PodMapValue> > PodMapTree;
template _STL::pair<PodMapTree::iterator, bool> PodMapTree::insert_unique(const PodMapValue &);
template PodMapTree::iterator PodMapTree::insert_unique(PodMapTree::iterator, const PodMapValue &);
