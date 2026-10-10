// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O2 /G7 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <map>

// Keep native signed comparisons inline without competing with the verified owner.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
// Typed iterator comparisons use the same node test as the reference base.
template <class T, class L, class R>
static inline bool operator==(const _Rb_tree_iterator<T, L> &a, const _Rb_tree_iterator<T, R> &b)
{ return a._M_node == b._M_node; }
template <class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T, L> &a, const _Rb_tree_iterator<T, R> &b)
{ return a._M_node != b._M_node; }
}



struct Rva00156FA0Record {  char bytes[1]; };
template class _STL::map<int,Rva00156FA0Record>;

// Existing address pin names this font-map cleanup; original spelling unknown.
typedef _STL::pair<const int,Rva00156FA0Record> Rva00157380Pair;
typedef _STL::_Rb_tree<int,Rva00157380Pair,_STL::_Select1st<Rva00157380Pair>,_STL::less<int>,_STL::allocator<Rva00157380Pair> > Rva00157380Tree;
struct FontCharsMapNode;
class FontCharDataTree {
public:
    ~FontCharDataTree() throw();
    FontCharsMapNode *m_header;
    unsigned int m_count;
    unsigned int m_padding;
};
FontCharDataTree::~FontCharDataTree() throw()
{
    reinterpret_cast<Rva00157380Tree *>(this)->~Rva00157380Tree();
}
