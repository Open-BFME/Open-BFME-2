// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Oi /EHsc /MD /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

struct Rva005C6AFDElement { char bytes[1]; bool operator<(const Rva005C6AFDElement&)const; bool operator==(const Rva005C6AFDElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<int const, Rva005C6AFDElement>, _STL::_Nonconst_traits<_STL::pair<int const, Rva005C6AFDElement> > >, bool> _STL::_Rb_tree<int, _STL::pair<int const, Rva005C6AFDElement>, _STL::_Select1st<_STL::pair<int const, Rva005C6AFDElement> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva005C6AFDElement> > >::insert_unique(_STL::pair<int const, Rva005C6AFDElement> const &);
