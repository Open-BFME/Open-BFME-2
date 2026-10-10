// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// STLport 4.5.3 map<int, vector<unsigned int> > insert_unique(value) for the
// CreateAHeroData member tree (retail 0x0021D203, 134B), dedicated TU. The tree
// typedefs are carried from stlport_hero_integer_vector_tree.cpp, which owns
// the tree's matched _M_create_node (0x0021D159) and _M_insert (0x0021D17B);
// _M_create_node is only declared here so the call resolves through its row.
// Target evidence: the only caller left unowned is the hinted insert_unique at
// 0x0021D6A9, and this body's call reads the matched _M_insert.
// /D_BFME_RETAIL_TREE_INSERT_LAYOUT selects the vendored STLport's retail
// insert_unique layout (signed key compare); without it the owning TU's
// flags emit a 132-byte body, which is why this lives in its own TU.
#include <map>
#include <vector>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}
typedef _STL::vector<unsigned int> HeroVector;
typedef _STL::pair<const int, HeroVector> HeroValue;
typedef _STL::_Rb_tree<int, HeroValue, _STL::_Select1st<HeroValue>, _STL::less<int>, _STL::allocator<HeroValue> > HeroTree;

template <> HeroTree::_Link_type HeroTree::_M_create_node(const HeroTree::value_type &value);

template _STL::pair<HeroTree::iterator, bool> HeroTree::insert_unique(const HeroTree::value_type &);
