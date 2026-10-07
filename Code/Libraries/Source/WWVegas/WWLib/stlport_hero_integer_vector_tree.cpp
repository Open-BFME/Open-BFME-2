// cl: /D_STLP_NO_EXCEPTIONS /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 copy family for CreateAHeroData member0x74.
// Retail insertion at0x21D203 uses signed key comparisons. Node0x21D159
// allocates32 bytes; value copy0x795C1 copies the int key then the established
// vector<unsigned int> copy0x2CFAB9. These calls anchor the complete family.
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
#include <vector>
typedef _STL::vector<unsigned int> HeroVector;
typedef _STL::pair<const int, HeroVector> HeroValue;
typedef _STL::_Rb_tree<int, HeroValue, _STL::_Select1st<HeroValue>, _STL::less<int>, _STL::allocator<HeroValue> > HeroTree;
template HeroTree::_Rb_tree(const HeroTree &);

// Retail21DD0E calls the held typed clear21DB91 and copy21DC9B.
template HeroTree &HeroTree::operator=(const HeroTree &);

// Whole-class instantiation of this tree. It reproduces _M_insert (retail 0x0021D17B)
// and the hinted insert_unique (retail 0x0021D6A9)
// byte for byte; their calls read the tree's matched STL helpers.
template class _STL::_Rb_tree<int,_STL::pair<int const ,_STL::vector<unsigned int,_STL::allocator<unsigned int> > >,_STL::_Select1st<_STL::pair<int const ,_STL::vector<unsigned int,_STL::allocator<unsigned int> > > >,_STL::less<int>,_STL::allocator<_STL::pair<int const ,_STL::vector<unsigned int,_STL::allocator<unsigned int> > > > >;
