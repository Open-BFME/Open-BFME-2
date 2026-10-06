// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// _M_insert for map<int,BfmePod16> @0x004133CE (136B) plus insert_unique
// 134B @0x00256583 plus hint insert_unique 294B @0x002567FA via map subscript.
// Unlock via insert_unique instantiation; int key with pair<const int,BfmePod16>
// value (BfmePod16 = 16B POD); callees rowed _M_create_node 0x00413374 plus
// _Rebalance 0x00025490. Precedent stlport_rb_tree_BfmeStringRecord004D05B8_insert.cpp.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
struct BfmePod16 { int a[4]; };
typedef _STL::pair<const int, BfmePod16> Pod16MapValue;
typedef _STL::_Rb_tree<int, Pod16MapValue, _STL::_Select1st<Pod16MapValue>, _STL::less<int>, _STL::allocator<Pod16MapValue> > Pod16MapTree;
typedef _STL::map<int, BfmePod16, _STL::less<int>, _STL::allocator<Pod16MapValue> > Pod16Map;
namespace _STL {
template <> class allocator<char> {
public:
    static char *allocate(unsigned int bytes, const void *hint);
};
}
template _STL::pair<Pod16MapTree::iterator, bool> Pod16MapTree::insert_unique(const Pod16MapTree::value_type &);
template BfmePod16 &Pod16Map::operator[](const int &);
