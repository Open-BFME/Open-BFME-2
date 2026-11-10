// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <map>



struct Rva00534743Record {  int word0;int word1;int word2; };
// Declared only: retail's element copy is the rowed body at this name's pinned
// address; this TU's copy is not retail's.
namespace _STL { template <> void _Construct<pair<const unsigned int, Rva00534743Record> , pair<const unsigned int, Rva00534743Record> >(pair<const unsigned int, Rva00534743Record>  *, const pair<const unsigned int, Rva00534743Record>  &); }


// Instantiate the recovered member; retain only its required template dependencies.
// The node's element copy is retail 0x005346D9, rowed as ?Rva005346D9Construct@@YAXPAURva005344C0@@ABU1@@Z; bind the
// call to that row instead of emitting this unit's own _Construct copy.
struct Rva005344C0;
void Rva005346D9Construct(Rva005344C0 *dest, const Rva005344C0 &source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(_STL::pair<unsigned int const, Rva00534743Record> *dest, const _STL::pair<unsigned int const, Rva00534743Record> &source)
{
	Rva005346D9Construct(reinterpret_cast<Rva005344C0 *>(dest), *reinterpret_cast<const Rva005344C0 *>(&source));
}
}
// The key is unsigned: this tree's _M_insert, retail 0x0053479F (136 B), compares
// keys with jb and is the only caller of this node creator (0x005347C7, 0x005347E0).
typedef _STL::pair<unsigned int const, Rva00534743Record> Rva00534743Value;
typedef _STL::_Rb_tree<unsigned int, Rva00534743Value, _STL::_Select1st<Rva00534743Value>, _STL::less<unsigned int>, _STL::allocator<Rva00534743Value> > Rva00534743Tree;
template _STL::_Rb_tree_node<Rva00534743Value> * Rva00534743Tree::_M_create_node(Rva00534743Value const &);
template Rva00534743Tree::iterator Rva00534743Tree::_M_insert(_STL::_Rb_tree_node_base *, _STL::_Rb_tree_node_base *, Rva00534743Value const &, _STL::_Rb_tree_node_base *);
