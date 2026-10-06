// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva005E49E0Element { short words[1]; bool operator<(const Rva005E49E0Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva005E49E0Element&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Rb_tree_iterator<_STL::pair<Rva005E49E0Element const, int>, _STL::_Nonconst_traits<_STL::pair<Rva005E49E0Element const, int> > > _STL::map<Rva005E49E0Element, int, _STL::less<Rva005E49E0Element>, _STL::allocator<_STL::pair<Rva005E49E0Element const, int> > >::insert(_STL::_Rb_tree_iterator<_STL::pair<Rva005E49E0Element const, int>, _STL::_Nonconst_traits<_STL::pair<Rva005E49E0Element const, int> > >, _STL::pair<Rva005E49E0Element const, int> const &);
