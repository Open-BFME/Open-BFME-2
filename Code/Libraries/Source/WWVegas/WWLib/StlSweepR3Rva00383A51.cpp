// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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



struct Rva00383A51Record { char word;
// ?Rva00383A51Record::operator< present-unmatched
bool operator<(const Rva00383A51Record&b)const{return word<b.word;}
// ?Rva00383A51Record::operator== present-unmatched
bool operator==(const Rva00383A51Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva00383A51Record>:__type_traits_aux<1>{};}


// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva00383A51Record>, _STL::_Select1st<_STL::pair<int const, Rva00383A51Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00383A51Record> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00383A51Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00383A51Record> > >, _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00383A51Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00383A51Record> > >);
