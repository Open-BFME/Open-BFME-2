// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?insert_unique@?$_Rb_tree@UBfmeStringRecord004D05B8@@U1@U?$_Identity@UBfmeStringRecord004D05B8@@@_STL@@U?$less@UBfmeStringRecord004D05B8@@@3@V?$allocator@UBfmeStringRecord004D05B8@@@3@@_STL@@QAE?AU?$_Rb_tree_iterator@UBfmeStringRecord004D05B8@@U?$_Nonconst_traits@UBfmeStringRecord004D05B8@@@_STL@@@2@U342@ABUBfmeStringRecord004D05B8@@@Z @ 0x004D2209 310B: hint insert_unique for WORD-key set
// calls rowed 0x004D2050 _M_insert and rowed 0x004D20DA insert_unique plus rowed increment/decrement.
// Evidence: chain packet calls 0x004D2050 now resolved; same 310B size as hint 0x004D1F1A; ret 0xc hidden iterator.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct BfmeStringRecord004D05B8 { unsigned short m_key; unsigned char m_pad[6]; };
inline bool operator<(const BfmeStringRecord004D05B8 &x, const BfmeStringRecord004D05B8 &y) { return x.m_key < y.m_key; }
typedef _STL::_Rb_tree<BfmeStringRecord004D05B8, BfmeStringRecord004D05B8, _STL::_Identity<BfmeStringRecord004D05B8>, _STL::less<BfmeStringRecord004D05B8>, _STL::allocator<BfmeStringRecord004D05B8> > UBfmeStringRecord004D05B8SetTree;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
template UBfmeStringRecord004D05B8SetTree::iterator UBfmeStringRecord004D05B8SetTree::insert_unique(UBfmeStringRecord004D05B8SetTree::iterator, const UBfmeStringRecord004D05B8SetTree::value_type &);
