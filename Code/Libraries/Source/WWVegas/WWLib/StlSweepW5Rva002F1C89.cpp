// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <map>

struct Rva002F1C89Element { short words[1]; bool operator<(const Rva002F1C89Element&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002F1C89Element&b)const {return words[0]==b.words[0];} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<Rva002F1C89Element const, int>, _STL::_Nonconst_traits<_STL::pair<Rva002F1C89Element const, int> > >, _STL::_Rb_tree_iterator<_STL::pair<Rva002F1C89Element const, int>, _STL::_Nonconst_traits<_STL::pair<Rva002F1C89Element const, int> > > > _STL::_Rb_tree<Rva002F1C89Element, _STL::pair<Rva002F1C89Element const, int>, _STL::_Select1st<_STL::pair<Rva002F1C89Element const, int> >, _STL::less<Rva002F1C89Element>, _STL::allocator<_STL::pair<Rva002F1C89Element const, int> > >::equal_range(Rva002F1C89Element const &);
