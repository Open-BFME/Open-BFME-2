// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}



struct Rva00439609Record { char word;
// ?Rva00439609Record::operator< present-unmatched
bool operator<(const Rva00439609Record&b)const{return word<b.word;}
// ?Rva00439609Record::operator== present-unmatched
bool operator==(const Rva00439609Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva00439609Record>:__type_traits_aux<1>{};}


// Retail's range erase calls the rowed tree clear at 0x00240C60 and node erase at
// 0x00439325; suppress this TU's own copies and bind the template names to those rows.
namespace _STL {
template <> void _Rb_tree<int, pair<int const, Rva00439609Record>, _Select1st<pair<int const, Rva00439609Record> >, less<int>, allocator<pair<int const, Rva00439609Record> > >::clear();
template <> void _Rb_tree<int, pair<int const, Rva00439609Record>, _Select1st<pair<int const, Rva00439609Record> >, less<int>, allocator<pair<int const, Rva00439609Record> > >::erase(_Rb_tree<int, pair<int const, Rva00439609Record>, _Select1st<pair<int const, Rva00439609Record> >, less<int>, allocator<pair<int const, Rva00439609Record> > >::iterator);
}
#pragma comment(linker, "/alternatename:?clear@?$_Rb_tree@HU?$pair@$$CBHURva00439609Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00439609Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00439609Record@@@_STL@@@2@@_STL@@QAEXXZ=?rva00240C60@Rva00439325@@QAEXXZ")
#pragma comment(linker, "/alternatename:?erase@?$_Rb_tree@HU?$pair@$$CBHURva00439609Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00439609Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00439609Record@@@_STL@@@2@@_STL@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHURva00439609Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00439609Record@@@_STL@@@2@@2@@Z=?rva00439325@Rva00439325@@QAEXPAURva00439325Node@@@Z")

// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva00439609Record>, _STL::_Select1st<_STL::pair<int const, Rva00439609Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00439609Record> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00439609Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00439609Record> > >, _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00439609Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00439609Record> > >);
