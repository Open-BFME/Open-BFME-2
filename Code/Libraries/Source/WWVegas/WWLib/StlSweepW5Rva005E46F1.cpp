// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Oi /EHsc /MD /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

// Preserve the native inline comparison and the verified external owner at 0x00626F90.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &left, const int &right) const
{ return left < right; }
}

struct Rva005E46F1Element { char bytes[1]; bool operator<(const Rva005E46F1Element&)const; bool operator==(const Rva005E46F1Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<int const, Rva005E46F1Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva005E46F1Element> > > _STL::_Rb_tree<int, _STL::pair<int const, Rva005E46F1Element>, _STL::_Select1st<_STL::pair<int const, Rva005E46F1Element> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva005E46F1Element> > >::insert_unique(_STL::_Rb_tree_iterator<_STL::pair<int const, Rva005E46F1Element>, _STL::_Nonconst_traits<_STL::pair<int const, Rva005E46F1Element> > >, _STL::pair<int const, Rva005E46F1Element> const &);
