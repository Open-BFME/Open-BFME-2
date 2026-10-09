// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport 4.5.3 map<int, BfmePod24> / map<int, BfmePod52> tree members that
// retail compiled with the P4 scheduler, dedicated TU: insert_unique for both
// trees (retail 0x00417D57 and 0x00426116) and _M_copy for the BfmePod24
// tree (0x00417F09). The element and tree declarations are carried from
// stlport_rb_tree_create_nodes.cpp, which owns each tree's matched
// _M_create_node, _M_insert and _M_clone_node; here _M_create_node is only
// declared so every call resolves through those rows.
//
// Target evidence: the masked bodies are identical for both element sizes,
// so identity comes from the calls. insert_unique at 0x00417D57 calls the
// Pod24 _M_insert row (0x00417B9B) and the one at 0x00426116 calls the Pod52
// _M_insert row (0x00426016); _M_copy at 0x00417F09 calls the Pod24
// _M_clone_node row (0x00417DDD) and itself. /G7 is what reproduces retail's
// instruction schedule here; the owning TU's flags keep the blend schedule.
#include <map>

// Keep the STLport signed comparison inline; its retail external copy
// belongs to stlport_list_int.cpp at RVA0x00626F90.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
}
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}

struct BfmePod24 { int a[6]; };
struct BfmePod52 { int a[13]; };

typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod24>, _STL::_Select1st<_STL::pair<const int, BfmePod24> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod24> > > HUBfmePod24MapTree;
typedef _STL::_Rb_tree<int, _STL::pair<const int, BfmePod52>, _STL::_Select1st<_STL::pair<const int, BfmePod52> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, BfmePod52> > > HUBfmePod52MapTree;

template <> HUBfmePod24MapTree::_Link_type HUBfmePod24MapTree::_M_create_node(const HUBfmePod24MapTree::value_type &value);
template <> HUBfmePod52MapTree::_Link_type HUBfmePod52MapTree::_M_create_node(const HUBfmePod52MapTree::value_type &value);

template _STL::pair<HUBfmePod24MapTree::iterator, bool> HUBfmePod24MapTree::insert_unique(const HUBfmePod24MapTree::value_type &);
template _STL::pair<HUBfmePod52MapTree::iterator, bool> HUBfmePod52MapTree::insert_unique(const HUBfmePod52MapTree::value_type &);
template HUBfmePod24MapTree::_Link_type HUBfmePod24MapTree::_M_copy(HUBfmePod24MapTree::_Link_type, HUBfmePod24MapTree::_Link_type);
