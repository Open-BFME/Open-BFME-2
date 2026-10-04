// ?_M_insert@?$_Rb_tree@UBfmeStringRecord004D05B8@@U1@U?$_Identity@UBfmeStringRecord004D05B8@@@_STL@@U?$less@UBfmeStringRecord004D05B8@@@3@V?$allocator@UBfmeStringRecord004D05B8@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@UBfmeStringRecord004D05B8@@U?$_Nonconst_traits@UBfmeStringRecord004D05B8@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABUBfmeStringRecord004D05B8@@0@Z @ 0x004D2050 (138B).
// Unlock via insert_unique instantiation; WORD key at +0 gives mov cx cmp jb shape; callees rowed 0x004D1D0B 0x00025490.
// cl: /O1 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct BfmeStringRecord004D05B8 { unsigned short m_key; unsigned char m_pad[6]; };
inline bool operator<(const BfmeStringRecord004D05B8 &x, const BfmeStringRecord004D05B8 &y) { return x.m_key < y.m_key; }
typedef _STL::_Rb_tree<BfmeStringRecord004D05B8, BfmeStringRecord004D05B8, _STL::_Identity<BfmeStringRecord004D05B8>, _STL::less<BfmeStringRecord004D05B8>, _STL::allocator<BfmeStringRecord004D05B8> > UBfmeStringRecord004D05B8SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord004D05B8>(BfmeStringRecord004D05B8 *, const BfmeStringRecord004D05B8 &);
}
template <> UBfmeStringRecord004D05B8SetTree::_Link_type UBfmeStringRecord004D05B8SetTree::_M_create_node(const UBfmeStringRecord004D05B8SetTree::value_type &);
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
template _STL::pair<UBfmeStringRecord004D05B8SetTree::iterator, bool> UBfmeStringRecord004D05B8SetTree::insert_unique(const UBfmeStringRecord004D05B8SetTree::value_type &);
