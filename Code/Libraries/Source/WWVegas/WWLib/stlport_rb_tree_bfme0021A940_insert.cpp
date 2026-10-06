// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
// ?_M_insert@?$_Rb_tree@UBfmeStringRecord0021A940@@U1@U?$_Identity@UBfmeStringRecord0021A940@@@_STL@@U?$less@UBfmeStringRecord0021A940@@@3@V?$allocator@UBfmeStringRecord0021A940@@@3@@_STL@@AAE?AU?$_Rb_tree_iterator@UBfmeStringRecord0021A940@@U?$_Nonconst_traits@UBfmeStringRecord0021A940@@@_STL@@@2@PAU_Rb_tree_node_base@2@0ABUBfmeStringRecord0021A940@@0@Z @0x0021C4B0 136B.
// Set _M_insert for BfmeStringRecord0021A940 via insert_unique instantiation.
// Same recipe as BfmeStringRecord00448113 insert.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
struct BfmeStringRecord0021A940 { public: int word0; unsigned char rest[16]; };
inline bool operator<(const BfmeStringRecord0021A940 &a, const BfmeStringRecord0021A940 &b) { return a.word0 < b.word0; }
typedef _STL::_Rb_tree<BfmeStringRecord0021A940, BfmeStringRecord0021A940, _STL::_Identity<BfmeStringRecord0021A940>, _STL::less<BfmeStringRecord0021A940>, _STL::allocator<BfmeStringRecord0021A940> > UBfmeStringRecord0021A940SetTree;
namespace _STL {
template <> void _Construct<BfmeStringRecord0021A940>(BfmeStringRecord0021A940 *, const BfmeStringRecord0021A940 &);
}
template _STL::pair<UBfmeStringRecord0021A940SetTree::iterator, bool> UBfmeStringRecord0021A940SetTree::insert_unique(const UBfmeStringRecord0021A940SetTree::value_type &);
template UBfmeStringRecord0021A940SetTree::iterator UBfmeStringRecord0021A940SetTree::insert_unique(UBfmeStringRecord0021A940SetTree::iterator, const UBfmeStringRecord0021A940SetTree::value_type &);
