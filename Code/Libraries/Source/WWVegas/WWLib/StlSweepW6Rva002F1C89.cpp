// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
#include <memory>

struct Rva002F1C89Element { unsigned prefix[2];int key;bool operator<(const Rva002F1C89Element&b)const {return key<b.key;}bool operator==(const Rva002F1C89Element&b)const {return key==b.key;} };

// Instantiate the recovered operation and its required template dependencies.
template _STL::pair<_STL::_Rb_tree_iterator<Rva002F1C89Element, _STL::_Nonconst_traits<Rva002F1C89Element> >, _STL::_Rb_tree_iterator<Rva002F1C89Element, _STL::_Nonconst_traits<Rva002F1C89Element> > > _STL::_Rb_tree<Rva002F1C89Element, Rva002F1C89Element, _STL::_Identity<Rva002F1C89Element>, _STL::less<Rva002F1C89Element>, _STL::allocator<Rva002F1C89Element> >::equal_range(Rva002F1C89Element const &);
