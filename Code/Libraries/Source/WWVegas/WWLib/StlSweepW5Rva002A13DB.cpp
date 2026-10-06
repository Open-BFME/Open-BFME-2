// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <map>

struct Rva002A13DBElement {Rva002A13DBElement();Rva002A13DBElement(const Rva002A13DBElement&);Rva002A13DBElement&operator=(const Rva002A13DBElement&);virtual void slot0();virtual void slot1();virtual ~Rva002A13DBElement();char bytes[4]; bool operator==(const Rva002A13DBElement&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Rb_tree<int, _STL::pair<int const, Rva002A13DBElement>, _STL::_Select1st<_STL::pair<int const, Rva002A13DBElement> >, _STL::less<int>, _STL::allocator<_STL::pair<int const, Rva002A13DBElement> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<int const, Rva002A13DBElement> > *);
