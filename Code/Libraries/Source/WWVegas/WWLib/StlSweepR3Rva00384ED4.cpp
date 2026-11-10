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
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> bool less<int>::operator()(int const &,int const &)const ; }

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}



struct Rva00384ED4Record { char word;
// ?Rva00384ED4Record::operator< present-unmatched
bool operator<(const Rva00384ED4Record&b)const{return word<b.word;}
// ?Rva00384ED4Record::operator== present-unmatched
bool operator==(const Rva00384ED4Record&b)const{return word==b.word;}
};
namespace _STL {template<>struct __type_traits<Rva00384ED4Record>:__type_traits_aux<1>{};}


// Retail's range erase calls the rowed tree clear at 0x00384E8E and node erase at
// 0x00383F9C; suppress this TU's own copies and bind the template names to those rows.
namespace _STL {
template <> void _Rb_tree<int, pair<int const, Rva00384ED4Record>, _Select1st<pair<int const, Rva00384ED4Record> >, less<int>, allocator<pair<int const, Rva00384ED4Record> > >::clear();
template <> void _Rb_tree<int, pair<int const, Rva00384ED4Record>, _Select1st<pair<int const, Rva00384ED4Record> >, less<int>, allocator<pair<int const, Rva00384ED4Record> > >::erase(_Rb_tree<int, pair<int const, Rva00384ED4Record>, _Select1st<pair<int const, Rva00384ED4Record> >, less<int>, allocator<pair<int const, Rva00384ED4Record> > >::iterator);
}
#pragma comment(linker, "/alternatename:?clear@?$_Rb_tree@HU?$pair@$$CBHURva00384ED4Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00384ED4Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00384ED4Record@@@_STL@@@2@@_STL@@QAEXXZ=?rva00384E8E@Rva0038404A@@QAEXXZ")
#pragma comment(linker, "/alternatename:?erase@?$_Rb_tree@HU?$pair@$$CBHURva00384ED4Record@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva00384ED4Record@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva00384ED4Record@@@_STL@@@2@@_STL@@QAEXU?$_Rb_tree_iterator@U?$pair@$$CBHURva00384ED4Record@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva00384ED4Record@@@_STL@@@2@@2@@Z=?rva00383F9C@Rva00383F9C@@QAEXPAURva00383F9CNode@@@Z")

// Instantiate the recovered member; retain only its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva00384ED4Record>, _STL::_Select1st<_STL::pair<int const, Rva00384ED4Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00384ED4Record> > >::erase(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00384ED4Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00384ED4Record> > >, _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00384ED4Record>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00384ED4Record> > >);
// Key erase of the same tree at retail 0x00385CBA: equal_range, distance, then
// the range erase above (its native call target 0x00384ED4). Buddy and buddy
// request map consumers (0x003871F6, 0x00416C69, 0x004177D5) pass the profile.
template unsigned int _STL::_Rb_tree<int, _STL::pair<int const, Rva00384ED4Record>, _STL::_Select1st<_STL::pair<int const, Rva00384ED4Record> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00384ED4Record> > >::erase(int const &);

// Native 0x00385F24..0x00385F29 independently forwards the unchanged
// receiver, key-reference argument and count result to the rowed key erase
// at 0x00385CBA. Keep the existing opaque record/tree view; the wrapper's
// original name and containing application class are not established.
typedef _STL::_Rb_tree<int, _STL::pair<int const, Rva00384ED4Record>,
	_STL::_Select1st<_STL::pair<int const, Rva00384ED4Record> >,
	_STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00384ED4Record> > > Rva00385F24Tree;
class Rva00385F24 : public Rva00385F24Tree
{
public:
	unsigned int rva00385F24(const int &key);
};

unsigned int Rva00385F24::rva00385F24(const int &key)
{
	return erase(key);
}
