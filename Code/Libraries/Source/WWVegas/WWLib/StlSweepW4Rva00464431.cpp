// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

struct Rva00464431Element {Rva00464431Element();Rva00464431Element(const Rva00464431Element&);Rva00464431Element&operator=(const Rva00464431Element&);virtual void slot0();virtual void slot1();virtual ~Rva00464431Element();char bytes[4]; bool operator==(const Rva00464431Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<int const, Rva00464431Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00464431Element> > > _STL::map<int, Rva00464431Element, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva00464431Element> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva00464431Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva00464431Element> > >, _STL::pair<int const, Rva00464431Element> const &);
